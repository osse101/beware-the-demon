#include "..\headers\dungeonmodel.h"


int runCreateMapThread(void* data);
SDL_sem* fileToLoad = NULL;
	
DungeonModel::DungeonModel():createNewDungeon(NULL),map(NULL){
	mapLoader = new MapLoader();
	currentLevel = 0;
	fileToLoad = SDL_CreateSemaphore( 1 );
}

DungeonModel::~DungeonModel(){
	if(map!=NULL){
		delete map;
		map = NULL;
	}
	if(mapLoader!=NULL){
		delete mapLoader;
		mapLoader = NULL;
	}
	if( createNewDungeon != NULL)
		SDL_WaitThread( createNewDungeon, NULL );
	if( fileToLoad != NULL)
		SDL_DestroySemaphore( fileToLoad );

	
}

void DungeonModel::initialize(){
	start();
}

void DungeonModel::start(){

}

void DungeonModel::cleanUp(){

}

void DungeonModel::loadMap(){
	//Cannot load the file while it is being written
	SDL_SemWait( fileToLoad );
	map = mapLoader->createMap();
	SDL_SemPost( fileToLoad );
}

void DungeonModel::createNewMap(){
	//TODO: Rewrite dungeon creation algorithim as a component of the project
	//createNewDungeon = SDL_CreateThread( runCreateMapThread, (void*)NULL );
}

void DungeonModel::update(){

}

int runCreateMapThread( void* data){
	////Cannot write the file while it is being loaded
	SDL_SemWait( fileToLoad );

	SDL_SemPost( fileToLoad );
	return 0;
}