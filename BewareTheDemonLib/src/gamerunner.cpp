
#include "..\headers\GameRunner.h"
#include <iostream>

GameRunner::GameRunner(){
	SDL_Init( SDL_INIT_EVERYTHING );
	TTF_Init();
	model = new GameModel();
	view = new GameView(model);
	logic = new GameLogic(model);
	//CON_SetExecuteFunction(model->console, Command_Handler);

	//Load all resources
	Resource::getInstance();
}

GameRunner::~GameRunner(){
	delete view;
	view = NULL;

	delete logic;
	logic = NULL;

	delete model;
	model = NULL;

	delete Resource::getInstance();
	TTF_Quit();
	SDL_Quit();
}

void GameRunner::start(){
	state = GAME_BEGIN;
	logic->initialize();
	model->initialize();
	view->initialize();
	
}

void GameRunner::mainLoop(){
	Timer fps;
	Timer delta;
	bool stateChange = false;
	int oldTime = 0;
	int currTime = 0;
	delta.start();
	
	while( state != GAME_OVER ){
		fps.start();

		handleEvents();
		stateChange = logic->update(delta.get_ticks()/1000.f);
		delta.start();
		if(stateChange){
			state = logic->getState();
			model->stateChange(state);
			view->stateChange(state);
		}
		
		model->update();
		view->update();

		if( fps.get_ticks() < 1000/FRAMES_PER_SECOND )
			SDL_Delay( 1000/FRAMES_PER_SECOND - fps.get_ticks() );
	}
	
}

void GameRunner::exit(){
}

void GameRunner::handleEvents(){
	

	SDL_Event event;
	while( SDL_PollEvent( &event ) ){
		
		switch( event.type ){
			case SDL_KEYDOWN:
				model->getKeysDown()[event.key.keysym.scancode] = true;
				
				break;

			case SDL_KEYUP:
				model->getKeysDown()[event.key.keysym.scancode] = false;
				break;

			case SDL_QUIT:
				state = GAME_OVER;
				break;
			
				break;
			default:
				break;
		}
	}

	
}

void GameRunner::update(){

}


