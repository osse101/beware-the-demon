
#include "dungeonbuilder.h"

DungeonBuilder::DungeonBuilder():_mapWidth(0),_mapHeight(0){
	DungeonBuilder::buildingDungeon = SDL_CreateSemaphore(0);

	_tiles=NULL;
}

DungeonBuilder::~DungeonBuilder(){
	SDL_DestroySemaphore( buildingDungeon );

	//tiles are freed from the Map object
	_tiles=NULL;
}

Map* DungeonBuilder::buildDungeon(int mapWidth, int mapHeight){
	//SDL_SemWait( buildingDungeon );
	Map* newMap = NULL;

	_mapWidth = mapWidth;
	_mapHeight = mapHeight;
	int mapSize = mapWidth*mapHeight;
	_tiles = new Tile*[mapSize];
	for(int i=0; i<mapSize; i++){
		_tiles[i] = new Tile();
	}
	Vector2D* startPoint = new Vector2D(1,1);
	Vector2D* exitPoint = new Vector2D(mapWidth-1, mapHeight-1);

	for(int i=0; i<mapWidth; i++){
		for(int j=0; j<mapHeight; j++){
			int pos = i*mapHeight+j;
			TileType t = TileType::TILE_GREEN;
			if( i==0 || i==mapWidth-1 ||
				j==0 || j==mapHeight-1){
					t = TileType::TILE_CENTER;
			}
			_tiles[pos]->setType(t);
		}
	}
	//add a test room
	addRoom();

	newMap = new Map(_tiles, mapWidth, mapHeight, startPoint, exitPoint);
	//SDL_SemPost( buildingDungeon );

	return newMap;
}


void DungeonBuilder::addRoom(){
	//TODO: takes a subsection of the actual tiles array being built
	//	and inserts a room into that
	for(int i=5; i<11; i++){
		for(int j=5; j<11; j++){
			if( (i==5 && j!=7) || (i==10 && j!=7) || j==5 || j==10 ){
				_tiles[i*_mapHeight+j]->setType(TileType::TILE_CENTER);
			}
		}
	}
	
	

}