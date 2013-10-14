#ifndef IMAGE_NODE_H
#define IMAGE_NODE_H

#include "imageobject.h"

struct ImageNode{
	ImageNode* next;
	ImageObject* data;
};



#endif