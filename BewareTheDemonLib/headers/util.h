#ifndef UTIL_H
#define UTIL_H

struct Vector2D{
	Vector2D(float x, float y);
	void operator=(const Vector2D& other);
	float x;
	float y;
};


#endif
