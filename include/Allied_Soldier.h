#ifndef ALLIED_SOLDIER_H
#define ALLIED_SOLDIER_H
#include <SDL.h>
#include <target.h>
#include <map>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <float.h>

#include "Base_Soldier.h"


class Allied_Soldier: public Base_Soldier
{
    public:
        Allied_Soldier(unsigned int id,float x, float y,SDL_Renderer* ren);
        virtual ~Allied_Soldier();

        bool update();
        bool update_idle();
        bool update_movement();
        bool update_aim();

        bool draw(SDL_Renderer* ren);
        bool moveto(float x, float y);

        bool fire_weapon();

        void createIcon(SDL_Renderer* ren);
    protected:

        int actionspeed;

        int idlecooldown;
        int aimcooldown;

        float movetox, movetoy;
        float CurrentTargetx,CurrentTargety;
        unsigned int CurrentTarget;
    private:
};



#endif // ALLIED_SOLDIER_H
