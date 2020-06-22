#include "timer.h"
#include <SDL.h>
timer::timer()
{
    StartTimer();
}

timer::~timer()
{
    //dtor
}

void timer::StartTimer()
{
    StartTime=SDL_GetTicks();
}

int timer::GetTime()
{
    return SDL_GetTicks()-StartTime;
}

int timer::GetRemaining()
{
    return period-(SDL_GetTicks()-StartTime);
}
