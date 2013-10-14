
#ifndef TILE_H
#define TILE_H

#include "stdafx.h"
#include "imageobject.h"
#include <list>

class Tile{
public:
	Tile();
	Tile( int x, int y, TileType tileType );
	virtual ~Tile();

	//Show the tile
	void show();

	//Get the tile type
	TileType getType();
	void setType( TileType t );

	//Get the collision box
	SDL_Rect getBox();
	void setX( int x );
	void setY( int y );

	std::list<ImageObject*>* images;

private:
	//The attribtues of the tile
	SDL_Rect box;

	//The tile type
	TileType type;
	
};

#endif

