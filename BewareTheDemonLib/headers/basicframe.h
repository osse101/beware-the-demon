
#ifndef BASIC_FRAME_H
#define BASIC_FRAME_H

#include "vector2d.h"
#include <string>
#include <vector>


class BasicFrame{
public:
	BasicFrame(int x, int y, int w, int h, bool hasFrame=true);
	~BasicFrame();

	void addElement(std::string option);
	void removeElement(std::string option);
	std::vector<std::string>* getContents();

	char foreColor;
	char backColor;
	bool hasFrame;
	int frameThickness;
	int frameWidth;
	int frameHeight;
	Vector2D* origin;
protected:
	std::vector<std::string>* contents;

private:
	

};


#endif