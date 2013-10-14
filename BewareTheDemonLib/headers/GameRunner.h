
#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include "stdafx.h"
#include "gameview.h"
#include "gamelogic.h"
#include "gamemodel.h"
#include "resources.h"
#include "timer.h"
#include <string>

enum GameState;
struct command_t;

class GameRunner{
public:
	GameRunner();
	~GameRunner();

	void start();
	void mainLoop();
	void exit();
	void update();

private:
	GameView* view;
	GameLogic* logic;
	GameModel* model;

	Resource* resourceInstance;

	void handleEvents();
	GameState state;

	
};


#endif