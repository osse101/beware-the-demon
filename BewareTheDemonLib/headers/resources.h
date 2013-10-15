
#ifndef RESOURCES_H
#define RESOURCES_H

#include "constants.h"
#include "tile.h"
#include "stdafx.h"
#include "ttftext.h"
#include <map>
#include <string>

class Resource{
public:
	static Resource* getInstance();
	static void registerRenderer(SDL_Renderer* renderer);

	SDL_Texture* getTiles(){return tileSheet;}
	SDL_Rect** getTileClips(){return tileClipList;}

	Mix_Music* loadMusic( std::string musicName );
	Mix_Chunk* loadSound( std::string soundName );
	TTF_TEXT* loadText( std::string fontName, std::string text, int fontSize, SDL_Color color, int textX, int textY );
	SDL_Texture* loadImage( std::string imageName );
	void freeMusic( std::string musicName);
	void freeSound( std::string soundName);
	void freeImage( std::string imageName );

	void freeTiles();
	void freePlayer();
	void freeBackGround();
	void freeGoldSprite();
	
	void loadAllTiles();
	

	~Resource();

protected:
	Resource();
	
private:
	std::map<std::string, Mix_Music*>* musicList;
	std::map<std::string, Mix_Chunk*>* soundList;
	std::map<std::string, SDL_Texture*>* imageList;
	SDL_Texture* tileSheet;
	SDL_Rect** tileClipList;

	static Resource* instance;
	static SDL_Renderer* renderer;
	
};





#endif