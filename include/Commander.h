#ifndef COMMANDER_H
#define COMMANDER_H

#include <State.h>
#include <Allied_Soldier.h>
#include <Target.h>
#include <map>
#include "SDL.h"

class Commander : public State
{
    public:
        Commander(SDL_Renderer* ren);
        virtual ~Commander();
        bool update();
        bool event(SDL_Event e);
        bool draw(SDL_Renderer* r);

        std::map<unsigned int,Target> enemies;
    protected:
        SDL_Renderer* renderer;

        std::map<unsigned int,Allied_Soldier> units;
        unsigned int SelUnit;
        unsigned int nextid;
    private:
};

#endif // COMMANDER_H
