#ifndef PLAYER_H
#define PLAYER_H

#include "util.h"
#include "stdafx.h"

class Player{
public:
	Player();
	~Player();
	inline Vector2D* pos(){return position;}
	inline void pos(Vector2D& newPosition){(*position)=newPosition;}
	inline SDL_Rect* getCollisionRect(){return collisionRect;}


private:
	//Position is the top-left corner on the square representation of the player
	//On the sprite, this is the top-most point, where collisionRect starts
	Vector2D* position;
	
	//Collision rect is a square with values based on the isometric diamond
	//	being represented.
	//x is the top-most point
	//y is the top-most point too
	//w is the length from x to the right-most point
	//h is the length from y to the left-most point
	SDL_Rect* collisionRect;
	//Stats
	//Items
	//SDL surfaces

};



#endif