#ifndef COMMANDER_H
#define COMMANDER_H

#include <State.h>
#include <Soldier.h>
#include <Target.h>
#include <list>

class Commander : public State
{
    public:
        Commander(SDL_Renderer* ren);
        virtual ~Commander();
        bool update();
        bool event(SDL_Event e);
        bool draw(SDL_Renderer* r);

    protected:
        SDL_Renderer* renderer;
        std::list<Target> enemies;
        std::list<Soldier> units;
        std::list<Soldier>::iterator SelUnit;
    private:
};

#endif // COMMANDER_H
