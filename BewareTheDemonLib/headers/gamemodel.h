
#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "stdafx.h"
#include "dungeonmodel.h"
#include "townmodel.h"

class GameModel{
public:
	GameModel();
	~GameModel();

	void initialize();
	void start();
	void update();
	void createNewMap();
	void loadMap();
	void stateChange(GameState newState);
	
	bool* getKeysDown(){return keysDown;}
	int getLevel(){return dm->getLevel();}
	void setLevel(int newVal){dm->setLevel(newVal);}
	Map* getMap(){return dm->getMap();}

	SDL_Rect* getPlayer(){return player;}
	SDL_Rect* getPlayerView(){return playerView;}
	SDL_Rect* getCamera(){return camera;}
	SDL_Rect* getCursor(){return cursor;}

private:
	
	void updateBegin();
	void updateWin();

	GameState state;
	bool* keysDown;
	SDL_Rect* camera;
	SDL_Rect* player;
	SDL_Rect* playerView;
	SDL_Rect* cursor;
	
	DungeonModel* dm;
	TownModel* tm;
	std::vector<Vector2D> frameList;
	
};

#endif