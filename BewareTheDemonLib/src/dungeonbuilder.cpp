
#include "dungeonbuilder.h"

DungeonBuilder::DungeonBuilder(){
	DungeonBuilder::buildingDungeon = SDL_CreateSemaphore(0);
}

DungeonBuilder::~DungeonBuilder(){
	SDL_DestroySemaphore( buildingDungeon );
}

Map* DungeonBuilder::buildDungeon(int mapWidth, int mapHeight){
	//SDL_SemWait( buildingDungeon );
	Map* newMap = NULL;

	int mapSize = mapWidth*mapHeight;
	Tile** tiles = new Tile*[mapSize];
	for(int i=0; i<mapSize; i++){
		tiles[i] = new Tile();
	}
	Vector2D* startPoint = new Vector2D(0,0);
	Vector2D* exitPoint = new Vector2D(mapWidth-1, mapHeight-1);

	for(int i=0; i<mapWidth; i++){
		for(int j=0; j<mapHeight; j++){
			int pos = i*mapHeight+j;
			TileType t = TileType::TILE_GREEN;
			if( i==0 || i==mapWidth-1 ||
				j==0 || j==mapHeight-1){
					t = TileType::TILE_CENTER;
			}
			tiles[pos]->setType(t);
		}
	}

	newMap = new Map(tiles, mapWidth, mapHeight, startPoint, exitPoint);
	//SDL_SemPost( buildingDungeon );

	return newMap;
}