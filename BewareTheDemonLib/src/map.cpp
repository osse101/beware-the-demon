
#include "..\headers\map.h"

Map::Map(Tile** map, int mapWidth, int mapHeight, Vector2D* start, Vector2D* exit):
		map(map), 
		mapWidth(mapWidth),
		mapHeight(mapHeight),
		start(start),
		exit(exit){
			mapSize = mapWidth*mapHeight;
}

Map::~Map(){
	DELETE(start);
	DELETE(exit);

	for( int t = 0; t < mapSize; t++ ){
		DELETE(map[t]);
	}
	DELETEARRAY(map);
}

TileType Map::getTileValue(int x, int y){
	if( x < 0 || x >= mapHeight ||
		y < 0 || y >= mapHeight){
			std::cout << "Invalid map position attempt: " << x << "," << y << std::endl;
			return TILE_NULL;
	}
	int pos = x*mapHeight+y;
	if(map[pos]==NULL){
		std::cout << "Map Tile is undefined: " << x << "," << y << std::endl;
	}
	return map[pos]->getType();
}




//No promises for maps at non-standardized sizes
//void Map::setMap( std::vector<std::string>* newMap ){
//	const static int cellExpansion = 4;
//	const static int halfCellExpansion = cellExpansion/2;
//	std::string line;
//
//	if( newMap->size() <= 0 ){ 
//		//invalid input 
//		std::cout << "size=" + newMap->size() << std::endl;
//		std::cout << "Bad map width!\n";
//		return;
//	}	
//
//	mapHeight = newMap->size()*cellExpansion;	//Each map cell represents 3x3 tiles
//	mapWidth = newMap->at(0).length()*cellExpansion;	//Each map cell represents 3x3 tiles
//	int compressedMapWidth=newMap->at(0).length();
//	resetMap();
//
//	for( int i = 0; i< newMap->size(); i++){
//		line = newMap->at(i);
//		
////		if( line.length() != mapWidth ){
////			//Invalid input
////			std::cout << "size=" + line.length() << std::endl;
////			std::cout << "Bad map height!" << std::endl; 
////			return;
////		}
//		
//		for( int j = 0; j < compressedMapWidth; j++){
//			int pos = j * mapHeight*cellExpansion + i*cellExpansion;
//			TileType t = chooseTileType( line[j] );
//			//std::cout << "Tile at " << j << "," << i << " is " << line[j] << std::endl;
//			for(int l=0; l<cellExpansion; l++){
//				for(int k=0; k<cellExpansion; k++){
//					int tilePos = pos+l*mapWidth+k; 
//					TileType replaceT = t;
//					if(t==TILE_BLUE){
//						if(l!=halfCellExpansion || k!=halfCellExpansion){ 
//							replaceT=TILE_GREEN;
//						}
//						else{
//							if(line[j]=='s'){
//								start->x = j*cellExpansion+halfCellExpansion;
//								start->y = i*cellExpansion+halfCellExpansion;
//							}
//							else if(line[j]=='x'){
//								exit->x = j*cellExpansion+halfCellExpansion;
//								exit->y = i*cellExpansion+halfCellExpansion;
//							}
//						}
//					}//end if t is blue tile
//					
//					map[tilePos]->setType( replaceT );
//					std::string debugString = "NULL";
//					if(replaceT==TILE_GREEN){debugString="green";}
//					else if(replaceT==TILE_BLUE){debugString="blue";}
//					else if(replaceT==TILE_RED){debugString="red";}
//					else if(replaceT==TILE_CENTER){debugString="wall";}
//					//std::cout << "Set tile for: " << tilePos << "=" << debugString << std::endl;
//					//if(t==TILE_CENTER){
//					//	map[tilePos]->images->push_back(new ImageObject(1, Resource::getInstance()->loadImage(WALL_TILE_SPRITE, true)));
//					//}
//					if(replaceT==TILE_RED)
//						map[tilePos]->images->push_back(new ImageObject(1, Resource::getInstance()->loadImage(DOOR_SPRITE, true)));
//					if(replaceT==TILE_BLUE)
//						map[tilePos]->images->push_back(new ImageObject(1, Resource::getInstance()->loadImage(STAIRS_SPRITE, true)));
//				}
//			}
//			
//		}
//	}
//	
//}
