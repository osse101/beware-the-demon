#include "mapmanager.h"

MapManager* MapManager::instance = NULL;

MapManager* MapManager::getInstance(){
	if(instance==NULL){
		instance = new MapManager();
	}
	return instance;
}

MapManager::MapManager(){
	dungeonBuilder = new DungeonBuilder();
	maps = new std::vector<Map*>();
	currentMapIndex=-1;
}

MapManager::~MapManager(){
	for(std::vector<Map*>::iterator it = maps->begin(); it!=maps->end(); it++){
		DELETE(*it);
	}
	DELETE(maps);
	DELETE(dungeonBuilder);
}

Map* MapManager::getMapSelected(){
	SDL_assert(maps!=NULL && maps->size() > currentMapIndex); 
	return maps->at(currentMapIndex);
}

Map* MapManager::getMapRelative(int bias){
	SDL_assert(maps!=NULL && maps->size() > (currentMapIndex+bias));
	return maps->at(currentMapIndex + bias);
}

Map* MapManager::createNextMap(){
	Map* newMap = dungeonBuilder->buildDungeon(25, 25);
	maps->push_back(newMap);
	return newMap;
}

void MapManager::advanceCurrentMapSelection(int amount){
	SDL_assert(maps!=NULL);

	currentMapIndex += amount;

	if(currentMapIndex >= maps->size()){
		currentMapIndex = maps->size()-1;
	}else if(currentMapIndex <= 0){
		currentMapIndex = 0;
	}

}