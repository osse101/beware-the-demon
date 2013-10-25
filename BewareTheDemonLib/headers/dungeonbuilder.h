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
	//functions for constructing the dungeon
	//TODO: some type of room
	void addRoom(const SDL_Rect &dimensions);

	SDL_semaphore* buildingDungeon;

	//internal variabeles
	int _mapHeight;
	int _mapWidth;
	Tile** _tiles;
	

};



#endif