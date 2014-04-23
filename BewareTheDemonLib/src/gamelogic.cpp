
#include "..\headers\gamelogic.h"

GameLogic::GameLogic(GameModel* gm){
	model = gm;
	state = GAME_BEGIN;
	audio = new AudioManager();
}

GameLogic::~GameLogic(){
	model = NULL;

	delete audio;
	audio = NULL;
}

void GameLogic::initialize(){
	state = GAME_BEGIN;
	audio->playMusic( MAINMENU_MUSIC );
}

bool GameLogic::update( float secs ){
	switch(state){
	case GAME_BEGIN:
		return updateBegin(secs);
		break;
	case GAME_TOWN:
		return updateTown(secs);
		break;
	case GAME_DUNGEON:
		return updateDungeon(secs);
		break;
	case GAME_WIN:
		return updateWin(secs);
		break;
	default:
		break;
	}
	return false;
}

bool GameLogic::updateBegin( float secs ){
	bool* keysDown = model->getKeysDown();
	SDL_Rect* c = model->getCursor();

	static float accumulativeTime;
	const float waitThreshold = 0.3f;
	bool wait = false;
	accumulativeTime += secs;
	if( accumulativeTime > waitThreshold ){
		accumulativeTime = 0;
		wait = false;
	}
	else
		wait = true;

	GameState oldState = state;
	if( keysDown[SDL_SCANCODE_ESCAPE] )
		state = GAME_OVER;
	else if( keysDown[SDL_SCANCODE_RETURN] ){

		//Play confirmation sound
		audio->playSound( MAINMENU_SELECT_SOUND );

		//get Cursor location and decide on selected option
		switch( c->x + CURSOR_OFFSET_X){
		case NEW_GAME_TEXT_X:
			state = GAME_TOWN;
			audio->stopMusic();
			break;
		case LOAD_GAME_TEXT_X:
			//Goto load menu
			break;
		case OPTIONS_TEXT_X:
			//GOTO options menu
			break;
		case QUIT_TEXT_X:
			audio->stopMusic();
			state = GAME_OVER;
			break;
		default:
			state = GAME_TOWN;
			break;
		}
			
	}
	else if( keysDown[SDL_SCANCODE_LEFT] && !wait ){
		switch( c->x + CURSOR_OFFSET_X){
		case NEW_GAME_TEXT_X:
			c->x = QUIT_TEXT_X - CURSOR_OFFSET_X;
			break;
		case LOAD_GAME_TEXT_X:
			c->x = NEW_GAME_TEXT_X - CURSOR_OFFSET_X;
			break;
		case OPTIONS_TEXT_X:
			c->x = LOAD_GAME_TEXT_X - CURSOR_OFFSET_X;
			break;
		case QUIT_TEXT_X:
			c->x = OPTIONS_TEXT_X - CURSOR_OFFSET_X;
			break;
		default:
			c->x = NEW_GAME_TEXT_X - CURSOR_OFFSET_X;
			break;
		}
	}
	else if( keysDown[SDL_SCANCODE_RIGHT] && !wait ){
		switch( c->x + CURSOR_OFFSET_X ){
		case NEW_GAME_TEXT_X:
			c->x = LOAD_GAME_TEXT_X - CURSOR_OFFSET_X;
			break;
		case LOAD_GAME_TEXT_X:
			c->x = OPTIONS_TEXT_X - CURSOR_OFFSET_X;
			break;
		case OPTIONS_TEXT_X:
			c->x = QUIT_TEXT_X - CURSOR_OFFSET_X;
			break;
		case QUIT_TEXT_X:
			c->x = NEW_GAME_TEXT_X - CURSOR_OFFSET_X;
			break;
		default:
			c->x = NEW_GAME_TEXT_X - CURSOR_OFFSET_X;
			break;
		}
	}
	else if( keysDown[SDLK_p] ){
		audio->pauseToggleMusic();
	}
	else if( !(keysDown[SDL_SCANCODE_RIGHT] || keysDown[SDL_SCANCODE_LEFT]) ){
		accumulativeTime = waitThreshold;
	}
	
	return oldState != state;
}

bool GameLogic::updateTown( float secs ){
	bool* keysDown = model->getKeysDown();
	GameState oldState = state;
	if( keysDown[SDL_SCANCODE_ESCAPE] )
		state = GAME_OVER;
	else if( keysDown[SDL_SCANCODE_DOWN] || keysDown[SDLK_s]){
		int mapExit = SCREEN_HEIGHT - PLAYER_HEIGHT;
		model->getPlayer()->pos()->y += (float)MOVE_SPEED_VERTICAL*secs;
		if( (int)(model->getPlayer()->pos()->y) >= mapExit ){
			state = GAME_DUNGEON;
			audio->playMusic( START_MUSIC );
		}
	}
	return oldState != state;
}

bool GameLogic::updateDungeon( float secs ){
	GameState oldState = state;
	bool* keysDown = model->getKeysDown();
	if( keysDown[SDL_SCANCODE_ESCAPE] ){
		state = GAME_OVER;
	}
	else{
	
	Map* map = model->getMap();
	Player* player = model->getPlayer();
	Vector2D playerPos(*(player->pos()));	
	SDL_Rect playerCollision(*player->getCollisionRect());
	SDL_Rect* camera = model->getCamera();

	int mapHeightInPixels = map->getMapHeight() * TILE_HEIGHT;
	int mapWidthInPixels = map->getMapWidth() * TILE_WIDTH;
	int distX = MOVE_SPEED_HORIZONTAL*secs;
	int distY = MOVE_SPEED_VERTICAL*secs;

	//TODO: revisit when an appropriate sprite is loaded
	if( keysDown[SDL_SCANCODE_UP] ){
		playerPos.y -= distY;
		int tileXL = (playerPos.x+playerCollision.x)/static_cast<float>(TILE_WIDTH);						//left side
		int tileXR = (playerPos.x+playerCollision.x+playerCollision.w)/static_cast<float>(TILE_WIDTH);		//right side
		int tileY = (playerPos.y+playerCollision.y)/static_cast<float>(TILE_HEIGHT);	//top half
		if( map->getTileValue(tileXL, tileY)==TILE_CENTER ||		//check top-left
			map->getTileValue(tileXR, tileY)==TILE_CENTER)		//check top-right
			//undo player movement
			playerPos.y += (TILE_HEIGHT - ((int)playerPos.y+playerCollision.y)%TILE_HEIGHT);
	}
	if( keysDown[SDL_SCANCODE_DOWN] ){
		playerPos.y += distY;
		int tileXL = (playerPos.x+playerCollision.x)/static_cast<float>(TILE_WIDTH);						//left side
		int tileXR = (playerPos.x+playerCollision.x+playerCollision.w)/static_cast<float>(TILE_WIDTH);		//right side
		int tileY = (playerPos.y+playerCollision.y+playerCollision.h)/static_cast<float>(TILE_HEIGHT);		//bot half
		if( map->getTileValue(tileXL, tileY)==TILE_CENTER ||
			map->getTileValue(tileXR, tileY)==TILE_CENTER)
			//undo player movement
			playerPos.y -= (((int)playerPos.y+playerCollision.y+playerCollision.h)%TILE_HEIGHT) +1;
	}
	if( keysDown[SDL_SCANCODE_RIGHT] ){
		playerPos.x += distX;
		int tileX  = (playerPos.x+playerCollision.x+playerCollision.w)/static_cast<float>(TILE_WIDTH);	//right side
		int tileYT = (playerPos.y+playerCollision.y)/static_cast<float>(TILE_HEIGHT);					//top
		int tileYB = (playerPos.y+playerCollision.y+playerCollision.h)/static_cast<float>(TILE_HEIGHT);	//bottom
		if( map->getTileValue(tileX, tileYT)==TILE_CENTER ||	//check top-right
			map->getTileValue(tileX, tileYB)==TILE_CENTER)	//check top-left
			playerPos.x -= ((int)playerPos.x+playerCollision.x+playerCollision.w)%TILE_WIDTH +1;
	}
	if( keysDown[SDL_SCANCODE_LEFT] ){
		playerPos.x -= distX;
		int tileX  = (playerPos.x+playerCollision.x)/TILE_WIDTH;					//left side
		int tileYT = (playerPos.y+playerCollision.y)/TILE_HEIGHT;					//top 
		int tileYB = (playerPos.y+playerCollision.y+playerCollision.h)/static_cast<float>(TILE_HEIGHT);//bottom
		if( map->getTileValue(tileX, tileYT)==TILE_CENTER ||	
			map->getTileValue(tileX, tileYB)==TILE_CENTER)	
			playerPos.x += (TILE_WIDTH - ((int)playerPos.x+playerCollision.x)%TILE_WIDTH);
	}
	
	int exitX = map->getExit()->x * TILE_WIDTH;
	int exitY = map->getExit()->y * TILE_HEIGHT;
/*	if( playerPos->x+PLAYER_WIDTH/2 < exitX+TILE_WIDTH   && playerPos->x+PLAYER_WIDTH/2 > exitX &&
		playerPos->y+PLAYER_HEIGHT/2 < exitY+TILE_HEIGHT && playerPos->y+PLAYER_HEIGHT/2 > exitY ){

		model->setLevel(model->getLevel()+1);
		
		if( model->getLevel() == NUMBER_OF_LEVELS ){
			state = GAME_WIN;
		}
		else{
			model->loadMap();
			model->createNewMap();
		}
	}
*/
	
	if( playerPos.x < 0 ) playerPos.x = 0;
	if( playerPos.x + PLAYER_WIDTH > mapWidthInPixels ) playerPos.x = mapWidthInPixels - PLAYER_WIDTH;
	if( playerPos.y < 0 ) playerPos.y = 0;
	if( playerPos.y + PLAYER_HEIGHT > mapHeightInPixels ) playerPos.y = mapHeightInPixels - PLAYER_HEIGHT;

	player->pos(playerPos);

	SDL_Rect* playerView = model->getPlayerView();
	int offsetX = (map->getMapWidth()-1)*TILE_WIDTH/2;

	playerView->x = offsetX + (playerPos.x/(float)TILE_WIDTH - playerPos.y/(float)TILE_HEIGHT)*TILE_WIDTH/2;
	playerView->y = (playerPos.x/(float)TILE_WIDTH + playerPos.y/(float)TILE_HEIGHT)*TILE_HEIGHT/2;

	camera->x = playerView->x - SCREEN_WIDTH/2;
	camera->y = playerView->y - SCREEN_HEIGHT/2;

	if( camera->x < 0 ) camera->x = 0;
	if( camera->x + camera->w > mapWidthInPixels ) camera->x = mapWidthInPixels - camera->w;
	if( camera->y < 0 ) camera->y = 0;
	if( camera->y + camera->h > mapHeightInPixels ) camera->y = mapHeightInPixels - camera->h;

	}

	

	return oldState != state;
}

bool GameLogic::updateWin( float secs ){
	GameState oldState = state;
	bool* keysDown = model->getKeysDown();

	if( keysDown[SDL_SCANCODE_ESCAPE] )
		state = GAME_OVER;
	else{

/*		SDL_Rect* player = model->getPlayer();
		if( keysDown[SDL_SCANCODE_UP] ){
			player->y -= MOVE_SPEED_VERTICAL*secs;
			if( player->x == TOWN_PLAYER_START_X && player->y <= TOWN_PLAYER_START_Y )
				state = GAME_OVER;
		}
*/


	}
	return oldState != state;
}




