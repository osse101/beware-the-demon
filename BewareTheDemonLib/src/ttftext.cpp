#include "..\headers\ttftext.h"

TTF_TEXT::TTF_TEXT(){

}

TTF_TEXT::~TTF_TEXT(){
	if(text){
		SDL_DestroyTexture(text);
	}

	if(rect){
		delete rect;
	}
}

