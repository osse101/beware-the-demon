
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
	SDL_Rect roomRect;
	roomRect.x = 5; roomRect.y= 5 ;
	roomRect.w = 5; roomRect.h= 5 ;
	addRoom(roomRect);

	newMap = new Map(_tiles, mapWidth, mapHeight, startPoint, exitPoint);
	//SDL_SemPost( buildingDungeon );

	return newMap;
}


void DungeonBuilder::addRoom(const SDL_Rect &dimensions){
	SDL_assert( dimensions.x >= 0 &&
				dimensions.y >= 0 &&
				dimensions.x + dimensions.w < _mapWidth &&
				dimensions.y + dimensions.h < _mapHeight);

	for(int x=dimensions.x; x<dimensions.x+dimensions.w; x++){
		for(int y=dimensions.y; y<dimensions.y+dimensions.h; y++){
			if( (x==5 && y!=7) || (x==9 && y!=7) || (x!=7 && y==5) || (x!=7 && y==9) ){
				_tiles[x*_mapHeight+y]->setType(TileType::TILE_CENTER);
			}
		}
	}

}