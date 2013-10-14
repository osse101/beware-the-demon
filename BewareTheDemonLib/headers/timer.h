/*! 
* \author Mike McKenzie
* \date February 22, 2012
* \copyright unlicensed
*/
#ifndef TIMER_H
#define TIMER_H

#include "stdafx.h"

/*!
* \details A class used for tracking time in milliseconds.
*/
class Timer
{
public:
/*!
* \details Constructor for the Timer Class
* \post Initialize all internal variables
* \return void
*/
    Timer();

/*!
* \details Set the reference point for the timer to this moment.
* \post start flag is set, timer is reset
* \return void
*/
    void start();

/*!
* \details Effectively, turn off the timer completely
* \post start and pause flags are reset
* \return void
*/
    void stop();

/*!
* \details Save this moment as a relative time for when getting ticks or unpausing.
* \pre if not started or is paused, nothing is changed
* \post pause flag is set, paused-ticks-tracker starts counting ticks
* \return void
*/
    void pause();

/*!
* \details Remove the duration of time paused from the timers ticks and continue timing.
* \pre if not paused, no change
* \post pause flag is reset, remove ticks accumulated while paused, reset pause-tick-tracker
* \return void
*/
    void unpause();

/*!
* \details Get the amount of time since the timer started, not counting paused time.
* \return The amount of time since the timer started minus time paused.
*			0 if the timer has not started or has been stopped.
*/
    int get_ticks();

/*!
* \details Get the flag which indicates whether the timer is started
* \return bool - the flag indicating whether the timer is started
*/
	bool is_started(){return started;}

/*!
* \details Get the flag which indicates whether the timer is paused
* \return bool - the flag indicating whether the timer is paused
*/
	bool is_paused(){return paused;}

private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;


};

#endif
