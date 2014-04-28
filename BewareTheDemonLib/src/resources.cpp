
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
}

Resource::Resource(){
	tileClipList = NULL;
	tileSheet = NULL;
	musicList = new musicMap();
	soundList = new soundMap();
	imageList = new imageMap();
	spriteSheetList = new spriteSheetMap();
}

Resource::~Resource(){
	freeTiles();
	
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

	for( spriteSheetMap::iterator i = spriteSheetList->begin(); i != spriteSheetList->end(); i++ ){
		delete i->second;	//textures are shared with imageList and deleted there
	}
	delete spriteSheetList;
}

SDL_Texture* loadImage( std::string imageName, std::string spriteSheetName ){



	return NULL;
}

void freeImage( std::string imageName, std::string spriteSheetName ){

	return;
}

void Resource::loadAllTiles(){
	if( tileSheet != NULL ){
		std::cout << "Tiles are already loaded!" << std::endl;
		return;
	}

	tileClipList = new SDL_Rect*[(int)TILE_TYPE_COUNT];	
	
	SDL_Surface* tileSheet_surface = IMG_Load( TILE_SPRITE_MAP.c_str() );
	tileSheet = SDL_CreateTextureFromSurface(renderer, tileSheet_surface);
	SDL_FreeSurface(tileSheet_surface);
	
	//Initialize the rectangles that are blitting the
	//	loaded image
	for( int i = 0; i < TILE_TILEMAP_ROWS; i++){
		for( int j = 0; j < TILE_TILEMAP_COLS; j++ ){
			int pos = i * TILE_TILEMAP_COLS + j;

			SDL_Rect* thisTileRect = new SDL_Rect();
			thisTileRect->w = TILE_WIDTH;
			thisTileRect->h = TILE_HEIGHT;
			thisTileRect->x = j*TILE_WIDTH;
			thisTileRect->y = i*TILE_HEIGHT;
			tileClipList[pos] = thisTileRect;
		}
	}
}

void Resource::freeTiles(){
	if( tileClipList != NULL ){
		for( int i = 0; i < (int)TILE_TYPE_COUNT-1; i++ ){  //NULL tile is not created as a surface
			if( tileClipList[i] != NULL ){
				delete tileClipList[i];
			}
		}
		delete [] tileClipList;
		tileClipList = NULL;
	}
	if( tileSheet != NULL ){
		SDL_DestroyTexture( tileSheet );
		tileSheet = NULL;
	}
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







