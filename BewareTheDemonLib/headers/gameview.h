
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "stdafx.h"
#include "resources.h"
#include "constants.h"
#include "gamemodel.h"
#include "ttftext.h"

class GameView{
public:
	GameView(GameModel* model);
	~GameView();
	void update();
	void initialize();
	void stateChange(GameState newState);

private:
	void updateBegin();
	void updateTown();
	void updateDungeon();
	void updateWin();

	GameModel* model;
	GameState state;
	SDL_Texture* tileSpriteSheet;
	SDL_Rect** tileClipList;
	SDL_Texture* backGround;
	
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;


	TTF_TEXT* newGame;
	TTF_TEXT* loadGame;
	TTF_TEXT* options;
	TTF_TEXT* quit;
};



#endif