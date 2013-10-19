#ifndef DUNGEON_BUILDER_H
#define DUNGEON_BUIDLER_H

#include "stdafx.h"
#include "map.h"

/***
Class for generating a Map object following some parameters
***/
class DungeonBuilder{
public:
	DungeonBuilder();
	~DungeonBuilder();
	Map* buildDungeon(int mapWidth, int mapHeight);
protected:

private:
	SDL_semaphore* buildingDungeon;
};



#endif