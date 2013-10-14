#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "stdafx.h"
#include "resources.h"
#include <map>
#include <string>

class AudioManager{
public:
	AudioManager();
	~AudioManager();

	void start();
	void playMusic( std::string musicName );
	void playSound( std::string soundName );

	void pauseToggleMusic();
	void stopMusic();

	void end();

private:
	
	SDL_Thread* musicThread;
	SDL_Thread* modifyThread;
	SDL_Thread* sfxThread;

	Resource* r;
};


#endif