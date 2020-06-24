#include "WaveController.h"

#include "Commander.h"
#include <iostream>
WaveController::WaveController()
{
    //ctor
    wavetime=0;
    wavethreshold=500;
}

WaveController::~WaveController()
{
    //dtor
}

bool WaveController::update()
{
    wavetime++;

    if (wavetime>wavethreshold)
    {
        extern Commander* s;
        s->create_enemy(Target(s->getnextid(),rand()%640,0,s->getRenderer()));
        s->create_enemy(Target(s->getnextid(),rand()%640,0,s->getRenderer()));
        s->create_enemy(Target(s->getnextid(),rand()%640,0,s->getRenderer()));
        wavetime=0;
    }
}

float WaveController::wave_progress()
{

    return (float)wavetime/wavethreshold;
}
