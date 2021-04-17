#ifndef ALLIED_SOLDIER_H
#define ALLIED_SOLDIER_H
#include <SDL.h>
#include <map>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <float.h>

#include <classes.h>


class Allied_Soldier: public Base_Soldier
{
    public:
        Allied_Soldier(float x, float y,std::shared_ptr<weapon>gun=NULL);
        virtual ~Allied_Soldier();

        bool update();
        bool update_idle();
        bool update_movement();
        bool update_aim();

        bool draw(SDL_Renderer* ren);
        bool moveto(float x, float y);

        bool fire_weapon();

        void createIcon();
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
