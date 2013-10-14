#include "..\headers\audiomanager.h"

int runMusicThread( void* data );
int runModifyThread( void* data );
int runSoundThread( void* data );

Mix_Music* localMusic = NULL;
Mix_Chunk* localSound = NULL;
bool isPaused = false;
bool isStopped = false;

AudioManager::AudioManager(){
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

	musicThread = NULL;
	modifyThread = NULL;
	sfxThread = NULL;
}

AudioManager::~AudioManager(){
	end();
}

void AudioManager::start(){
	;
}

void AudioManager::playMusic( std::string musicName ){
	localMusic = Resource::getInstance()->loadMusic( musicName );
	runMusicThread(NULL);
	//musicThread = SDL_CreateThread(runMusicThread, (void*)NULL);
}

void AudioManager::stopMusic( ){
	Mix_HaltMusic();
}

void AudioManager::pauseToggleMusic(){
	isPaused = !isPaused;
	if( isPaused )
		Mix_PauseMusic();
	else
		Mix_ResumeMusic();
}

void AudioManager::playSound( std::string soundName ){
	localSound = Resource::getInstance()->loadSound( soundName );
	runSoundThread(NULL);
	//sfxThread = SDL_CreateThread(runSoundThread, (void*)NULL);
}

void AudioManager::end(){
	Mix_HaltMusic();
	Mix_CloseAudio();
}

int runMusicThread( void* data ){
	if( localMusic != NULL ){
		//If music is not playing
		if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_PlayMusic( localMusic, -1 );
		}
	}
	return 0;
}

int runModifyThread( void* data ){
	//Lock variables used by other threads and modify them.
	return 0;
}

int runSoundThread( void* data ){
	if( localSound != NULL ){
		Mix_PlayChannel( -1, localSound, 0 );
	}
	return 0;
}