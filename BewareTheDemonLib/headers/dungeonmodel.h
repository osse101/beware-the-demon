#ifndef DUNGEON_MODEL_H
#define DUNGEON_MODEL_H

#include <string.h>

#include "maploader.h"
#include "map.h"
#include "stdafx.h"

class DungeonModel{
public:
	DungeonModel();
	~DungeonModel();

	void initialize();
	void update();
	
	void createNewMap();
	void loadMap();
	
	int getLevel(){return currentLevel;}
	void setLevel(int newVal){currentLevel=newVal;}
	Map* getMap(){return map;}

private:
	void start();
	void cleanUp();
	//Sprite List
	//Boss List
	//Chest List
	//Dungeon Map

	SDL_Thread* createNewDungeon;
	int currentLevel;
	MapLoader* mapLoader;
	Map* map;
	
};


#endif