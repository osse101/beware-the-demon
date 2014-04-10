#ifndef PLAYER_H
#define PLAYER_H

#include "util.h"

class Player{
public:
	Player();
	~Player();
	inline Vector2D* pos(){return position;}
	inline void pos(Vector2D& newPosition){(*position)=newPosition;}


private:
	//Location
	Vector2D* position;
	//Stats
	//Items
	//SDL surfaces

};



#endif