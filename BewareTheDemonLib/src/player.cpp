
#include "..\headers\player.h"

Player::Player(){
	//position is top-left of where the player is standing
	position = new Vector2D(0.0f,0.0f);

	collisionRect = new SDL_Rect();
	collisionRect->x = 0;
	collisionRect->y = 0;	
	collisionRect->w = PLAYER_COLLISION_WIDTH;
	collisionRect->h = PLAYER_COLLISION_HEIGHT;
}

Player::~Player(){
	delete position;
	delete collisionRect;
}