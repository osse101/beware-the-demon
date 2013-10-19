#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "stdafx.h"
#include "map.h"
#include "dungeonbuilder.h"

class MapManager{
public:
	static MapManager* getInstance();
	~MapManager();

	Map* getMapSelected();
	//Get map that is 'bias' indices away from current map
	//'bias' can be positive or negative
	Map* getMapRelative(int bias);
	Map* createNextMap();	
	//NOTE: truncates at list boundary
	void advanceCurrentMapSelection(int amount);
	//Add something to rearrange maps?

	int getMapCount(){return maps->size();}
	int getSelectedMapNumber(){return currentMapIndex;}
protected:

private:
	static MapManager* instance;
	MapManager();

	//The data structure might change if map relationships become more complicated.
	std::vector<Map*>* maps;
	DungeonBuilder* dungeonBuilder;
	int currentMapIndex;
};



#endif