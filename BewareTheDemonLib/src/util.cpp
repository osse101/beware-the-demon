#include "..\headers\util.h"

Vector2D::Vector2D(float x, float y):
	x(x),y(y){}

Vector2D::Vector2D(const Vector2D& other):
	x(other.x), y(other.y){}

void Vector2D::operator=(const Vector2D& other){
	this->x = other.x;
	this->y = other.y;
}