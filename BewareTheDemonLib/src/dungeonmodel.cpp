#include "..\headers\dungeonmodel.h"
	
DungeonModel::DungeonModel():map(NULL),currentLevel(0){
}

DungeonModel::~DungeonModel(){
	if(map!=NULL){
		delete map;
		map = NULL;
	}
}

void DungeonModel::initialize(){
	start();
}

void DungeonModel::start(){

}

void DungeonModel::cleanUp(){

}

void DungeonModel::loadMap(){
	std::cout << "Map loaded\n";
	map = MapManager::getInstance()->getMapSelected();
}

void DungeonModel::createNewMap(){
	std::cout << "Map created\n";
	MapManager::getInstance()->createNextMap();
	currentLevel++;
	MapManager::getInstance()->advanceCurrentMapSelection(1);
}

void DungeonModel::update(){

}
