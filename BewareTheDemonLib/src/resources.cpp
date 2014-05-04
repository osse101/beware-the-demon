
#include "..\headers\resources.h"
#include <iostream>

Resource* Resource::instance = NULL;
SDL_Renderer* Resource::renderer=NULL;

Resource* Resource::getInstance(){
	if( instance == NULL )
		instance = new Resource();
	return instance;
}

void Resource::registerRenderer(SDL_Renderer* renderer){
	Resource::renderer = renderer;
	SpriteSheet::registerRenderer(renderer);
}

Resource::Resource(){
	musicList = new musicMap();
	soundList = new soundMap();
	imageList = new imageMap();
}

Resource::~Resource(){
	
	for( musicMap::iterator i = musicList->begin(); i != musicList->end(); i++ ){
		Mix_FreeMusic( i->second );
	}
	delete musicList;

	for( soundMap::iterator i = soundList->begin(); i != soundList->end(); i++ ){
		Mix_FreeChunk( i->second );
	}
	delete soundList;

	for( imageMap::iterator i = imageList->begin(); i != imageList->end(); i++ ){
		SDL_DestroyTexture(i->second);
	}
	delete imageList;
}

SDL_Texture* Resource::loadImage( std::string imageName, std::string spriteSheetName, SDL_Rect*& imageRect ){
	SpriteSheet* sheet = SpriteSheet::loadSpriteSheet(spriteSheetName);
	if(sheet==NULL){
		//TODO: Debug Log Here
		return NULL;
	}

	imageRect = sheet->spriteList->at(imageName);
	return sheet->spriteSheet;
}

void Resource::freeImage( std::string imageName, std::string spriteSheetName ){
	SpriteSheet::unloadSpriteSheet(spriteSheetName);
	return;
}


SDL_Texture* Resource::loadImage( std::string imageName ){
	SDL_Texture* loadedImage = NULL;
	if( !(*imageList)[imageName] ){
		SDL_Surface* image = IMG_Load(imageName.c_str());
		loadedImage = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
		(*imageList)[imageName] = loadedImage;
	}
	else
		loadedImage = (*imageList)[imageName];

	return loadedImage;
}

void Resource::freeImage( std::string imageName ){
	if( (*imageList)[imageName] ){
		SDL_DestroyTexture( (*imageList)[imageName] );
		imageList->erase( imageName );
	}
}


Mix_Music* Resource::loadMusic( std::string musicName ){
	Mix_Music* music = NULL;
	if( !(*musicList)[musicName] ){
		const char* file =  musicName.c_str();
		music =  Mix_LoadMUS( file );
		(*musicList)[ musicName ] = music;
	}
	else
		music = (*musicList)[musicName];
	return music;
}
void Resource::freeMusic( std::string musicName){
	if( (*musicList)[musicName] ){
		Mix_FreeMusic( (*musicList)[musicName] );
		musicList->erase( musicName );
	}
}

Mix_Chunk* Resource::loadSound( std::string soundName ){
	Mix_Chunk* sound = NULL;
	if( !(*soundList)[soundName] ){
		const char* file = soundName.c_str();
		sound =  Mix_LoadWAV( file );
		(*soundList)[soundName] = sound;
	}
	else
		sound = (*soundList)[soundName];
	return sound;
}

void Resource::freeSound( std::string soundName ){
	if( (*soundList)[soundName] ){
		Mix_FreeChunk( (*soundList)[soundName] );
		soundList->erase( soundName );
	}
}

//	*A SDL_Rect is created at this point because the texture information is defined in the SDL_Surface but
//	 is lost when it becomes a SDL_Texture
TTF_TEXT* Resource::loadText( std::string fontName, std::string text, int fontSize, SDL_Color color, int textX, int textY ){
	TTF_TEXT* retText = NULL;
	
	retText = new TTF_TEXT();
	TTF_Font* font = TTF_OpenFont(fontName.c_str(), fontSize);
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
	retText->text = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect* textRect = new SDL_Rect();
	textRect->x = textX;			textRect->y = textY;
	textRect->w = textSurface->w;	textRect->h = textSurface->h;
	retText->rect = textRect;

	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	

	return retText;
	
}







