#include "spritesheet.h"

spriteSheetMap* SpriteSheet::spriteSheets = new spriteSheetMap();
SDL_Renderer* SpriteSheet::renderer=NULL;

void SpriteSheet::registerRenderer(SDL_Renderer* renderer){
	SpriteSheet::renderer = renderer;
}

SpriteSheet* SpriteSheet::loadSpriteSheet(std::string name){
	if(spriteSheets->count(name)==1){
		return spriteSheets->at(name);
	}else{
		SpriteSheet* sheet = new SpriteSheet(name);
		return sheet;
	}
}

void SpriteSheet::unloadSpriteSheet(std::string name){
	if(spriteSheets->count(name)==1){
		SpriteSheet* sheet = spriteSheets->at(name);
		spriteSheets->erase(name);
		delete sheet;
	}
	
	
}

SpriteSheet::SpriteSheet(std::string name){
	sheetName = name;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(CONFIG_FILE.c_str());
	//std::cout  << "Load result: " << result.description() << ", sheet name: " << doc.child("SpriteSheet").attribute("name").value() << std::endl;

	pugi::xml_node sheet = doc.find_child_by_attribute("name", name.c_str());
	//if(sheet.attribute("structured").as_bool()){	
		//SpriteSheet node contains spacing information
		bool structured = sheet.attribute("structured").as_bool();
		int rows = sheet.attribute("rows").as_int();
		int cols = sheet.attribute("cols").as_int();
		int width = sheet.attribute("width").as_int();
		int height = sheet.attribute("height").as_int();
	//}else{
		//Sprite node contains absolute position
	//}

	std::string sheetPathName = image_path + sheet.attribute("name").value();
	SDL_Surface* tileSheet_surface = IMG_Load( sheetPathName.c_str() );
	spriteSheet = SDL_CreateTextureFromSurface(renderer, tileSheet_surface);
	SDL_FreeSurface(tileSheet_surface);

	//Initialize the rectangles that are blitting the
	//	loaded image
	clips = new SDL_Rect*[width*height];
	spriteList = new sprites();
	for( pugi::xml_node sprite = sheet.child("Sprite"); sprite; sprite = sprite.next_sibling("Sprite") ){
		std::string spriteName = sprite.attribute("name").value();
		const int x = sprite.attribute("x").as_int();
		const int y = sprite.attribute("y").as_int();
		const int pos = y * cols + x;
		SDL_Rect* thisTileRect = new SDL_Rect();
		thisTileRect->w = width;
		thisTileRect->h = height;
		thisTileRect->x = x*width;
		thisTileRect->y = y*height;
		clips[pos] = thisTileRect;
		
		spriteList->emplace(spriteName, thisTileRect);
	}


}

SpriteSheet::~SpriteSheet(){
	for(sprites::iterator it=spriteList->begin(); it!=spriteList->end(); it++){
		delete it->second;
	}
	delete spriteList;
	delete [] clips;
	SDL_DestroyTexture(spriteSheet);
}