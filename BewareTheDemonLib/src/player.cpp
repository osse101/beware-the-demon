
#include "..\headers\player.h"

Player::Player(){
	position = new Vector2D(0.0f,0.0f);
}

Player::~Player(){
	delete position;
}