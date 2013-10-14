
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "gamemodel.h"
#include "audiomanager.h"

class GameLogic{
public:
	GameLogic(GameModel* gm);
	~GameLogic();

	GameState getState(){return state;}

	void initialize();
	bool update( float secs );

private:
	bool updateBegin( float secs );
	bool updateTown( float secs );
	bool updateDungeon( float secs );
	bool updateWin( float secs );

	AudioManager* audio;
	GameModel* model;
	GameState state;

};

#endif