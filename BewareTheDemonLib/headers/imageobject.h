#ifndef IMAGE_OBJECT_H
#define IMAGE_OBJECT_H

#include "stdafx.h"

class ImageObject{
public:
	ImageObject(int pos, SDL_Surface* img){image=img; frontalPos=pos;}
	~ImageObject(){SDL_FreeSurface(image);}
	int frontalPos;		//0 is at plane level
	SDL_Surface* image;
	int offsetX;
	int offsetY;
};


#endif