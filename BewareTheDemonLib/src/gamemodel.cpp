

#include "..\headers\gamemodel.h"
#include <iostream>
GameModel::GameModel(){
	
	state = GAME_BEGIN;

	keysDown = new bool[MAX_KEYS_USED];
	for( int i=0; i<MAX_KEYS_USED; i++)
		keysDown[i] = false;

	player = new Player();
	
	playerView = new SDL_Rect();
	playerView->x=0; playerView->y=0;
	playerView->w=PLAYER_WIDTH; playerView->h=PLAYER_HEIGHT/2;

	camera = new SDL_Rect();
	camera->x = 0; camera->y = 0;
	camera->w = SCREEN_WIDTH; camera->h = SCREEN_HEIGHT;

	cursor = new SDL_Rect();
	cursor->x = NEW_GAME_TEXT_X - CURSOR_OFFSET_X; cursor->y = TEXT_Y;
	cursor->w = 10; cursor->h = 10;

	tm = new TownModel();
	dm = new DungeonModel();
	
}

GameModel::~GameModel(){
	delete [] keysDown;
	keysDown = NULL;

	delete camera;
	camera = NULL;

	delete player;
	player = NULL;

	delete playerView;
	playerView = NULL;

	delete cursor;
	cursor = NULL;

	delete tm;
	tm = NULL;

	delete dm;
	dm = NULL;
	
}

void GameModel::initialize(){
	start();
}

void GameModel::stateChange(GameState newState){
	//Compare the state transition to determine which 
	//	action to take
	GameState oldState = state;
	//Update the local state value
	state = newState;

	//Use nested switch statements to define actions on 
	//	state transitions
	switch(state){
	case GAME_BEGIN:
		break;
	case GAME_TOWN:
		//dm->createNewMap();
		switch(oldState){
		case GAME_BEGIN:
			player->pos(Vector2D(TOWN_PLAYER_START_X, TOWN_PLAYER_START_Y));
			break;
		default:
			break;
		}
		break;

	case GAME_DUNGEON:
		
		switch(oldState){
		case GAME_BEGIN:
			createNewMap();
			loadMap();
			break;
		case GAME_TOWN:
			createNewMap();
			loadMap();
			break;
		default:
			break;
		}
		break;

	case GAME_WIN:
		switch(oldState){
		case GAME_DUNGEON:
			player->pos(Vector2D(WIN_PLAYER_START_X, WIN_PLAYER_START_Y));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GameModel::update(){
	switch(state){
	case GAME_BEGIN:
		updateBegin();
		break;
	case GAME_TOWN:
		tm->update();
		break;
	case GAME_DUNGEON:
		dm->update();
		break;
	case GAME_WIN:
		updateWin();
		break;
	default:
		break;
	}
}

void GameModel::start(){
	//Load start menu options and cursor location

}

void GameModel::createNewMap(){
	dm->createNewMap();
}

void GameModel::loadMap(){
	dm->loadMap();
	Map* map = dm->getMap();
	player->pos(Vector2D(
		(float)(map->getStart()->x * TILE_WIDTH),
		(float)(map->getStart()->y * TILE_HEIGHT)));
}

void GameModel::updateBegin(){
}

void GameModel::updateWin(){
}

