
#include "Timer.h"
#include <SDL.h>
Timer::Timer()
{
    this->Paused = false;
    this->Started = false;
    this->PausedTicks = 0;
    this->StartTicks =0;
}

void Timer::stop()
{
    this->Started = false;
    this->Paused = false;
    this->StartTicks = 0;
    this->PausedTicks = 0;
}

void Timer::start()
{
    this->Started = true;
    this->Paused = false;
    this->StartTicks = SDL_GetTicks();
    this->PausedTicks = 0;
}

void Timer::pause()
{
    if( this->Started && !this->Paused )
    {
        this->Paused = true;
        this->PausedTicks = SDL_GetTicks() - this->StartTicks;
        this->StartTicks = 0;
    }
}

void Timer::unpause()
{
    if( this->Started && this->Paused )
    {
        this->Paused = false;
        this->StartTicks = SDL_GetTicks() - this->PausedTicks;
        this->PausedTicks = 0;
    }
}

uint32_t Timer::getTicks()
{
    uint32_t time = 0;
    if( this->Started )
    {
        if( this->Paused )
        {
            time = this->PausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - this->StartTicks;
        }
    }
    return time;
}

bool Timer::isStarted()
{
    return this->Started;
}

bool Timer::isPaused()
{
    return this->Paused && this->Started;
}