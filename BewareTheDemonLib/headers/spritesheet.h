#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "stdafx.h"
#include <map>
#include <pugixml.hpp>

class SpriteSheet;
typedef std::map<std::string, SpriteSheet*> spriteSheetMap;
typedef std::map<std::string, SDL_Rect*> sprites;

class SpriteSheet{

public:
	static SpriteSheet* loadSpriteSheet(std::string name);
	static void unloadSpriteSheet(std::string name);
	static void registerRenderer(SDL_Renderer* renderer);

	~SpriteSheet();
	std::string sheetName;
	SDL_Texture* spriteSheet;
	sprites* spriteList;
	SDL_Rect** clips;
private:
	static spriteSheetMap* spriteSheets;
	static SDL_Renderer* renderer;

	SpriteSheet(std::string name);
};


#endif