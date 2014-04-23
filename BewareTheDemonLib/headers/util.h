#ifndef UTIL_H
#define UTIL_H

struct Vector2D{
	Vector2D():x(0),y(0){}
	Vector2D(float x, float y);
	Vector2D(const Vector2D& other);
	void operator=(const Vector2D& other);
	float x;
	float y;
};


#endif
