#include "TimerObject.h"

#include <SDL.h>

TimerObject::TimerObject(uint32_t waiting_milisecond)
{
    this->wanted_time = waiting_milisecond;
    this->started_ticks = 0U;
    this->paused = true;
}

void TimerObject::start()
{
    this->paused = false;
    this->started_ticks = SDL_GetTicks();
}

bool TimerObject::is_time_reached()
{
    return !this->paused && SDL_GetTicks() - this->started_ticks >= this->wanted_time;
}

void TimerObject::reset(uint32_t waiting_milisecond)
{
    this->wanted_time = waiting_milisecond;
    this->started_ticks = SDL_GetTicks();
}