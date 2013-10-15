#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "stdafx.h"
#include "tile.h"
#include "map.h"
#include <string>
#include <vector>

class MapLoader{
public:
	MapLoader();
	~MapLoader();
	Map* createMap();
	Map* loadMap(std::string fileName);
	void clear();
protected:

private:
	void parseLine(std::string line);
	void parseHeader(std::string line);
	void parseMeta(std::string line);
	void parseObject(std::string line);

	struct MapObject{
		enum objectType{ tile };
		objectType objType;
		int id;
		int x;
		int y;
		TileType tileType;
		int isCollidable;
	};

	std::vector<MapObject*>* objects;
	std::map<std::string, TileType>* strToTileTypeMap;
	int mapWidth;
	int mapHeight;

};



#endif