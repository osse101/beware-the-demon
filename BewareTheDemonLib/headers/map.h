
#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>

#include "stdafx.h"
#include "tile.h"
#include "resources.h"
#include "imageobject.h"

#include <iostream>

class Map{
public:
	Map();
	Map(Tile** map, int mapWidth, int mapHeight, Vector2D* start, Vector2D* exit);
	~Map();
	
	int getMapHeight(){return mapHeight;}
	int getMapWidth(){return mapWidth;}
	int getMapSize(){return mapSize;}

	TileType getTileValue(int x, int y);
	Vector2D* getStart(){return start;}
	Vector2D* getExit(){return exit;}
	Tile** getMapArray(){ return map; }

	
private:
	//void setMap( std::vector<std::string>* newMap );

	int mapHeight;
	int mapWidth;
	int mapSize;

	
	Tile** map;
	Vector2D* start;
	Vector2D* exit;
	


};




#endif