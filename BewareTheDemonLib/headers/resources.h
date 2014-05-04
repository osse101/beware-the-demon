
#ifndef RESOURCES_H
#define RESOURCES_H

#include "constants.h"
#include "tile.h"
#include "stdafx.h"
#include "ttftext.h"
#include "spritesheet.h"

#include <map>
#include <string>

typedef std::map<std::string, Mix_Music*> musicMap;
typedef std::map<std::string, Mix_Chunk*> soundMap;
typedef std::map<std::string, SDL_Texture*> imageMap;

class Resource{
public:
	static Resource* getInstance();
	static void registerRenderer(SDL_Renderer* renderer);

	Mix_Music* loadMusic( std::string musicName );
	Mix_Chunk* loadSound( std::string soundName );
	TTF_TEXT* loadText( std::string fontName, std::string text, int fontSize, SDL_Color color, int textX, int textY );
	SDL_Texture* loadImage( std::string imageName );
	SDL_Texture* loadImage( std::string imageName, std::string spriteSheetName, SDL_Rect*& imageRect );
	void freeMusic( std::string musicName);
	void freeSound( std::string soundName);
	void freeImage( std::string imageName );
	void freeImage( std::string imageName, std::string spriteSheetName );

	void freePlayer();
	void freeBackGround();
	void freeGoldSprite();

	~Resource();

protected:
	Resource();
	
private:
	musicMap* musicList;
	soundMap* soundList;
	imageMap* imageList;
	
	static Resource* instance;
	static SDL_Renderer* renderer;
	
};





#endif