

#include "..\headers\basicframe.h"
#include <algorithm>

BasicFrame::BasicFrame(int x, int y, int w, int h, bool hasFrame)
	:frameWidth(w),frameHeight(h),hasFrame(hasFrame){
	origin = new Vector2D(x, y);
	contents = new std::vector<std::string>();

}

BasicFrame::~BasicFrame(){
	delete origin;
	contents->clear();
	delete contents;
}

void BasicFrame::addElement(std::string option){
	contents->push_back(option);
	
}

void BasicFrame::removeElement(std::string option){
	std::vector<std::string>::iterator it = std::find( contents->begin(), contents->end(), option);
	contents->erase(it);
}

std::vector<std::string>* BasicFrame::getContents(){
	return contents;
}