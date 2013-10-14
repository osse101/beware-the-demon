
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
	if( keysDown[SDLK_ESCAPE] )
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
	if( keysDown[SDLK_ESCAPE] )
		state = GAME_OVER;
	else if( keysDown[SDL_SCANCODE_DOWN] || keysDown[SDLK_s]){
		int mapExit = SCREEN_HEIGHT - PLAYER_HEIGHT;
		model->getPlayer()->y += (float)MOVE_SPEED_VERTICAL*secs;
		if( (int)(model->getPlayer()->y) >= mapExit ){
			state = GAME_DUNGEON;
			audio->playMusic( START_MUSIC );
		}
	}
	return oldState != state;
}

bool GameLogic::updateDungeon( float secs ){
	GameState oldState = state;
	bool* keysDown = model->getKeysDown();
	if( keysDown[SDLK_ESCAPE] )
		state = GAME_OVER;
	else{
	
	Map* map = model->getMap();
	SDL_Rect* player = model->getPlayer();
	SDL_Rect* camera = model->getCamera();

	int mapHeightInPixels = map->getMapHeight() * TILE_HEIGHT;
	int mapWidthInPixels = map->getMapWidth() * TILE_WIDTH;
	int distX = MOVE_SPEED_HORIZONTAL*secs;
	int distY = MOVE_SPEED_VERTICAL*secs;

	if( keysDown[SDL_SCANCODE_UP] ){
		player->y -= distY;
		int playerPosX = (int)(player->x+0.5f)/TILE_WIDTH;
		int playerPosY = (int)(player->y+0.5f)/TILE_HEIGHT;
		if( map->getTileValue(playerPosX, playerPosY) == TILE_CENTER )
			player->y += (TILE_HEIGHT-player->y%TILE_HEIGHT);
	}
	if( keysDown[SDL_SCANCODE_DOWN] ){
		player->y += distY;
		int playerPosX = (int)(player->x+0.5f)/TILE_WIDTH;
		int playerPosY = (int)(player->y+0.5f)/TILE_HEIGHT;
		if( map->getTileValue(playerPosX, playerPosY) == TILE_CENTER )
			player->y = player->y - player->y%TILE_HEIGHT - PLAYER_HEIGHT;
	}
	if( keysDown[SDL_SCANCODE_RIGHT] ){
		player->x += distX;
		int playerPosX = (int)(player->x+0.5f)/TILE_WIDTH;
		int playerPosY = (int)(player->y+0.5f)/TILE_HEIGHT;
		if( map->getTileValue(playerPosX, playerPosY) == TILE_CENTER )
			player->x = player->x - (player->x)%TILE_WIDTH - PLAYER_WIDTH;
	}
	if( keysDown[SDL_SCANCODE_LEFT] ){
		player->x -= distX;
		int playerPosX = (int)(player->x+0.5f)/TILE_WIDTH;
		int playerPosY = (int)(player->y+0.5f)/TILE_HEIGHT;
		if( map->getTileValue(playerPosX, playerPosY) == TILE_CENTER )
			player->x += TILE_WIDTH-player->x%TILE_WIDTH;
	}

	int exitX = map->getExit()->x * TILE_WIDTH;
	int exitY = map->getExit()->y * TILE_HEIGHT;
	if( player->x+PLAYER_WIDTH/2 < exitX+TILE_WIDTH   && player->x+PLAYER_WIDTH/2 > exitX &&
		player->y+PLAYER_HEIGHT/2 < exitY+TILE_HEIGHT && player->y+PLAYER_HEIGHT/2 > exitY ){

		model->setLevel(model->getLevel()+1);
		
		if( model->getLevel() == NUMBER_OF_LEVELS ){
			state = GAME_WIN;
		}
		else{
			model->loadMap();
			model->createNewMap();
		}
	}
	
	if( player->x < 0 ) player->x = 0;
	if( player->x + player->w > mapWidthInPixels ) player->x = mapWidthInPixels - player->w;
	if( player->y < 0 ) player->y = 0;
	if( player->y + player->h > mapHeightInPixels ) player->y = mapHeightInPixels - player->h;

	SDL_Rect* playerView = model->getPlayerView();
	int offsetX = (map->getMapWidth()-1)*TILE_WIDTH/2;

	playerView->x = offsetX + (player->x/(float)TILE_WIDTH - player->y/(float)TILE_HEIGHT)*TILE_WIDTH/2;
	playerView->y = (player->x/(float)TILE_WIDTH + player->y/(float)TILE_HEIGHT)*TILE_HEIGHT/2;

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

	if( keysDown[SDLK_ESCAPE] )
		state = GAME_OVER;
	else{

		SDL_Rect* player = model->getPlayer();
		if( keysDown[SDL_SCANCODE_UP] ){
			player->y -= MOVE_SPEED_VERTICAL*secs;
			if( player->x == TOWN_PLAYER_START_X && player->y <= TOWN_PLAYER_START_Y )
				state = GAME_OVER;
		}



	}
	return oldState != state;
}




