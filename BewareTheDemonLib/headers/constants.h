#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <math.h>

//File path constants
const std::string resource_path = "resource\\";
const std::string music_path = resource_path + "music\\";
const std::string sound_path = resource_path + "sound\\";
const std::string image_path = resource_path + "image\\";
const std::string font_path = resource_path + "font\\";
const std::string bin_path = "bin\\";
const std::string header_path = "headers\\";
const std::string src_path = "src\\";

//Config file
const std::string CONFIG_FILE = resource_path + "config.xml";

//Screen constants
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

//Event constants
const int MAX_KEYS_USED = 323;

//Math constants
const float PI = 3.14159265f;
const float ISO_ROTATION_ANGLE_IN_RADS = 45*PI/180;
const float ISO_ROTATION_VALUE = cos(ISO_ROTATION_ANGLE_IN_RADS);

//Tile constants
const std::string TILE_SPRITE_MAP = "tiles.png";
const std::string WALL_TILE_SPRITE = image_path+"wallTile.png";
const std::string DOOR_SPRITE = image_path+"doorsprite.jpg";
const std::string FLOOR_TILE_SPRITE = image_path+"floorTile.png";
const std::string STAIRS_SPRITE = image_path+"stairssprite.jpg";
const std::string PLANT_SPRITE = image_path+"ficusPlant2.png";
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 30;
const float TILE_RATIO = TILE_HEIGHT/TILE_WIDTH;
const int TILE_TILEMAP_ROWS = 3;
const int TILE_TILEMAP_COLS = 4;

//Player constants
const std::string PLAYER_SPRITE = image_path+"myChar100.png";
const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 20;
const int PLAYER_COLLISION_WIDTH = PLAYER_WIDTH;
const int PLAYER_COLLISION_HEIGHT = PLAYER_HEIGHT;
const int MOVE_SPEED_VERTICAL = TILE_HEIGHT*5;
const int MOVE_SPEED_HORIZONTAL = TILE_WIDTH*5;


//Main Menu Constants
const std::string WELCOME_BACKGROUND = image_path+"welcome.png";
const std::string MAINMENU_BACKGROUND = image_path+"DungeonMaster.png";
const std::string MAINMENU_CURSOR = image_path+"cursor.png";
const std::string MAINMENU_MUSIC = music_path+"graveyard.mid";
const std::string MAINMENU_SELECT_SOUND = sound_path+"lazer.wav";

const int TEXT_Y = SCREEN_HEIGHT*21/24;
const int CURSOR_OFFSET_X = 30;
const int NEW_GAME_TEXT_X = SCREEN_WIDTH*1/5;
const int LOAD_GAME_TEXT_X = SCREEN_WIDTH*2/5;
const int OPTIONS_TEXT_X = SCREEN_WIDTH*3/5;
const int QUIT_TEXT_X = SCREEN_WIDTH*4/5;

//Town Constants
const std::string TOWN_BACKGROUND = image_path+"town.png";
const int TOWN_PLAYER_START_X = SCREEN_WIDTH/2;
const int TOWN_PLAYER_START_Y = SCREEN_HEIGHT - PLAYER_HEIGHT/3*10;

//Dungeon Constants
const int NUMBER_OF_LEVELS = 2;
const std::string NEXT_MAP_FILE = resource_path+"newMap.txt";
const std::string PY_GENERATOR_SCRIPT_FILE = resource_path+"genRandomDungeon.py";

//Win constants
const std::string WIN_BACKGROUND = image_path+"win.png";
const std::string GOLD_SPRITE = image_path+"gold2.png";
const int WIN_PLAYER_START_X = SCREEN_WIDTH/2;
const int WIN_PLAYER_START_Y = SCREEN_HEIGHT - PLAYER_HEIGHT;

//Music Constants
const std::string START_MUSIC = music_path+"startMusic.mp3";

//Sound Constants
const std::string START_SOUND = sound_path+"start.wav";

//Font Constants
const std::string REMOVE_FONT = image_path+"removeThis.bmp";
const std::string BE_STILL_FONT = font_path+"KGBeStillAndKnow.ttf";

enum TileType{
	TILE_RED,
	TILE_TOP_LEFT,
	TILE_TOP,
	TILE_TOP_RIGHT,
	TILE_GREEN,
	TILE_LEFT,
	TILE_CENTER,
	TILE_RIGHT,
	TILE_BLUE,
	TILE_BOTTOM_LEFT,
	TILE_BOTTOM,
	TILE_BOTTOM_RIGHT,
	TILE_NULL,
	TILE_TYPE_COUNT
};

//Game state constants
enum GameState{
	GAME_BEGIN,
	GAME_MAIN_MENU,
	GAME_TOWN,
	GAME_DUNGEON,
	GAME_PAUSE,
	GAME_WIN,
	GAME_OVER
};

#endif
