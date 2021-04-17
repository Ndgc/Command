#include "WaveController.h"

#include "Commander.h"
#include <iostream>
WaveController::WaveController()
{
    //ctor
    wavetime=0;
    wavethreshold=1000;
    wavenumber=0;
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
        next_wave();
    }
    return true;
}

bool WaveController::next_wave()
{
         wavenumber++;
        extern Commander* s;
        s->give_resource_points(1);

        for (int i=0; i<((wavenumber/3)+1);i++)
        {
                s->create_enemy(std::make_shared<Target>(rand()%s->get_battlefield_width(),0));
        }

        wavetime=0;
        return true;
}

float WaveController::wave_progress()
{

    return (float)wavetime/wavethreshold;
}

int WaveController::getwavenumber()
{
    return wavenumber;
}
