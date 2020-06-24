#ifndef COMMANDER_H
#define COMMANDER_H

#include <State.h>
#include <Allied_Soldier.h>
#include <Target.h>
#include <map>
#include <WaveController.h>
#include "SDL.h"

class Commander : public State
{
    public:
        Commander(SDL_Renderer* ren);
        virtual ~Commander();
        bool update();
        bool event(SDL_Event e);
        bool draw(SDL_Renderer* r);
        bool create_enemy(Target new_enemy);
        bool create_ally(Allied_Soldier new_ally);

        WaveController WaveControl;
        std::map<unsigned int,Target> enemies;
        std::map<unsigned int,Allied_Soldier> units;

        SDL_Renderer *getRenderer(){return renderer;}
        unsigned int getnextid(){return nextid;}
    protected:
        SDL_Renderer* renderer;

        unsigned int SelUnit;
        unsigned int nextid;
    private:
};

#endif // COMMANDER_H
