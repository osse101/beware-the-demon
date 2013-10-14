
#include "..\headers\tile.h"

Tile::Tile(){
	type = TILE_NULL;
	images = new std::list<ImageObject*>();
}

Tile::Tile(int x, int y, TileType tileType){
	//Get the offsets
	box.x = x;
	box.y = y;

	//Set the collision box
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;

	//Get the tile type
	type = tileType;

	images = new std::list<ImageObject*>();
}

Tile::~Tile(){
	delete images;
}

TileType Tile::getType(){
	return type;
}

void Tile::setType( TileType t ){
	type = t;
}

SDL_Rect Tile::getBox(){
	return box;
}

void Tile::setX( int x ){
	box.x = x;
}

void Tile::setY( int y ){
	box.y = y;
}

