// DungeonMasterExecutable.cpp : Defines the entry point for the console application.
//

#include "..\BewareTheDemonLib\headers\GameRunner.h"
#include <tchar.h>
#include <iostream>

int SDL_main(int argc, _TCHAR* argv[])
{
	GameRunner* gr = new GameRunner();
	gr->start();
	gr->mainLoop();
	gr->exit();
	delete gr;
	return 0;
}

