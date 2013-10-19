// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef STD_AFX_H
#define STD_AFX_H


//Third party libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

//standard lib
#include <vector>

//Local files
#include "constants.h"
#include "targetver.h"
#include "vector2d.h"

#ifdef NULL
	#define DELETE(p) if(p!=NULL){delete p;p=NULL;}else{}
	#define DELETEARRAY(p) if(p!=NULL){delete [] p;p=NULL;}else{}
#endif

#endif