
#include "..\headers\gameview.h"
#include <iostream>

static SDL_Texture* plantGuy;

GameView::GameView(GameModel* gm){
	model = gm;

	SDL_CreateWindowAndRenderer(
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		0, 
		&gameWindow, 
		&gameRenderer);
	SDL_SetWindowTitle(gameWindow, "Beware The Demon");
	Resource::registerRenderer(gameRenderer);
	state = GAME_BEGIN;
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);
	SDL_RenderPresent(gameRenderer);

	SDL_Color color = {199,0,0};

	//note: loadText creates a new ttftext
	Resource* r = Resource::getInstance();
	this->newGame = r->loadText(BE_STILL_FONT, "New Game", 16, color, NEW_GAME_TEXT_X, TEXT_Y);
	this->loadGame = r->loadText(BE_STILL_FONT, "Load Game", 16, color, LOAD_GAME_TEXT_X, TEXT_Y);
	this->options = r->loadText(BE_STILL_FONT, "Options", 16, color, OPTIONS_TEXT_X, TEXT_Y);
	this->quit = r->loadText(BE_STILL_FONT, "Quit", 16, color, QUIT_TEXT_X, TEXT_Y);
}

GameView::~GameView(){
	delete newGame;
	delete loadGame;
	delete options;
	delete quit;

	SDL_DestroyTexture(backGround);
	
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	model = NULL;
}

void GameView::initialize(){
	state = GAME_BEGIN;
	backGround = Resource::getInstance()->loadImage( MAINMENU_BACKGROUND );
	plantGuy = Resource::getInstance()->loadImage(PLANT_SPRITE);


}

void GameView::stateChange(GameState newState){
	//Compare the state transition to determine which 
	//	action to take
	GameState oldState = state;
	//Update the local state value
	state = newState;
	Resource* r = Resource::getInstance();
	SpriteSheet* s = NULL;
	switch(state){
	case GAME_BEGIN:
		//Initialize things
		//r->loadBackGround( MAINMENU_BACKGROUND );
		//backGround =r->getBackground();
		break;
	case GAME_TOWN:
		switch(oldState){
		case GAME_BEGIN:
			//Load things
			backGround = r->loadImage( TOWN_BACKGROUND );
			break;
		default:
			break;
		}
		break;
	case GAME_DUNGEON:
		switch(oldState){
		case GAME_BEGIN:
		case GAME_TOWN:
			//Free background
			r->freeImage(MAINMENU_BACKGROUND);

			//Load tiles and player
			s = SpriteSheet::loadSpriteSheet(TILE_SPRITE_MAP.c_str());
			tileSpriteSheet = s->spriteSheet;
			tileClipList = s->clips;
			break;

		default:
			break;
		}
	case GAME_WIN:
		switch(oldState){
		case GAME_DUNGEON:
			//TODO: r->freeTiles();

			backGround = r->loadImage( TOWN_BACKGROUND );
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void GameView::update(){
	 //Fill the screen blue
 	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0xFF, 0x00);
	SDL_RenderClear(gameRenderer);

	switch(state){
	case GAME_BEGIN:
		updateBegin();
		break;
	case GAME_TOWN:
		updateTown();
		break;
	case GAME_DUNGEON:
		updateDungeon();
		break;
	case GAME_WIN:
		updateWin();
	case GAME_OVER:
		break;
	default:
		break;
	}
	
	SDL_RenderPresent( gameRenderer );

}

void GameView::updateBegin(){
	SDL_RenderCopy(gameRenderer, backGround, NULL, NULL);

	SDL_Rect* c = model->getCursor();
	SDL_Texture* cursorSprite = Resource::getInstance()->loadImage( MAINMENU_CURSOR );
	SDL_RenderCopy(gameRenderer, cursorSprite, NULL, c);
	
	SDL_RenderCopy(gameRenderer, newGame->text, NULL, newGame->rect);
	SDL_RenderCopy(gameRenderer, loadGame->text, NULL, loadGame->rect);
	SDL_RenderCopy(gameRenderer, options->text, NULL, options->rect);
	SDL_RenderCopy(gameRenderer, quit->text, NULL, quit->rect);
	
}

void GameView::updateTown(){
	SDL_Texture* playerSprite = Resource::getInstance()->loadImage( PLAYER_SPRITE );
	Player* p = model->getPlayer();
	SDL_Rect player(*(p->getCollisionRect()));
	player.x = p->pos()->x;
	player.y = p->pos()->y;

	SDL_RenderCopy(gameRenderer, backGround, NULL, NULL);
	SDL_RenderCopy(gameRenderer, playerSprite, NULL, &player);
}

void GameView::updateDungeon(){
	Map* map = model->getMap();
	Tile** mapArray = map->getMapArray();
	SDL_Rect* camera = model->getCamera();

	//Diamond map algorithm
	int tempX;
	int tempY;
	int offsetX = (map->getMapWidth()-1)*TILE_WIDTH/2;
	int offsetY = 0;
	SDL_Rect* tempPoint = new SDL_Rect();{
		tempPoint->w = TILE_WIDTH;
		tempPoint->h = TILE_HEIGHT;
	}

	//Top to center
	for(int j=0; j<map->getMapHeight(); j++){
		tempY=j;tempX=0;
		for(; tempY>=0; ){
			
			int x = offsetX + (tempX-tempY)*TILE_WIDTH/2 - camera->x;
			int y = (tempX+tempY) * TILE_HEIGHT/2 - camera->y;
			int pos = tempX * map->getMapHeight() + tempY;
			tempPoint->x = x;
			tempPoint->y = y;

			
			if( pos >= map->getMapSize() || pos < 0 ){ break; }
			TileType t = mapArray[pos]->getType();
			if( t == TILE_NULL ){ continue; }
			SDL_RenderCopy( gameRenderer, tileSpriteSheet, tileClipList[t], tempPoint); 
			std::list<ImageObject*>* myList = mapArray[pos]->images;
			if(myList != NULL && !myList->empty()){
				std::list<ImageObject*>::reverse_iterator rit;
				for ( rit=myList->rbegin() ; rit != myList->rend(); ++rit ){
					//TODO: apply_surface( x, y-myList->front()->image->h+30,myList->front()->image, gameScreen, NULL );
				}
			}
			tempY--; tempX++;
		}
	}
	//Center+1 to bottom
	for(int i=1; i<map->getMapWidth(); i++){
		tempY=map->getMapHeight()-1;tempX=i;
		for(; tempX<map->getMapWidth(); 0){

			int x = offsetX + (tempX-tempY)*TILE_WIDTH/2 - camera->x;
			int y = (tempX+tempY) * TILE_HEIGHT/2 - camera->y;
			int pos = tempX * map->getMapHeight() + tempY;
			tempPoint->x = x;
			tempPoint->y = y;

			if( pos >= map->getMapSize() || pos < 0 ) break;
			TileType t = mapArray[pos]->getType();
			if( t==TILE_NULL ){ continue; }
			SDL_RenderCopy( gameRenderer, tileSpriteSheet, tileClipList[t], tempPoint); 
			std::list<ImageObject*>* myList = mapArray[pos]->images;
			if(myList != NULL && !myList->empty()){
				std::list<ImageObject*>::reverse_iterator rit;
				for ( rit=myList->rbegin() ; rit != myList->rend(); ++rit ){
					//TODO: apply_surface( x, y-myList->front()->image->h+30,myList->front()->image, gameScreen, NULL );
				}
			}
			tempY--; tempX++;
		}
	}
	
	SDL_Rect* playerView = model->getPlayerView();

	SDL_Texture* playerSprite = Resource::getInstance()->loadImage( PLAYER_SPRITE );
	tempPoint->w = PLAYER_WIDTH;
	tempPoint->h = PLAYER_HEIGHT;
	tempPoint->x = playerView->x - camera->x + TILE_WIDTH/2;
	tempPoint->y = playerView->y - camera->y - TILE_HEIGHT/4;
	SDL_RenderCopy(gameRenderer, playerSprite, NULL, tempPoint);
	delete tempPoint;

}

void GameView::updateWin(){
	Player* player = model->getPlayer();
	SDL_Texture* playerSprite = Resource::getInstance()->loadImage( PLAYER_SPRITE );
	SDL_Texture* goldSprite = Resource::getInstance()->loadImage( GOLD_SPRITE );

	SDL_Rect gRect1 = SDL_Rect();
	SDL_Rect gRect2 = SDL_Rect();
	gRect1.x = SCREEN_WIDTH*1/5;
	gRect1.y = SCREEN_HEIGHT*3/5;
	gRect1.w = gRect1.h = 100;

	gRect2.x = SCREEN_WIDTH*3/5;
	gRect2.y = SCREEN_HEIGHT*3/5;
	gRect2.w = gRect2.h = 100;

	SDL_RenderCopy(gameRenderer, backGround, NULL, NULL);
	//SDL_RenderCopy(gameRenderer, playerSprite, NULL, player);
	SDL_RenderCopy(gameRenderer, goldSprite, NULL, &gRect1);
	SDL_RenderCopy(gameRenderer, goldSprite, NULL, &gRect2);
}


Vector2D* getPointOnView(Vector2D* v1){
	Vector2D* vOut = new Vector2D();

	return vOut;
}
