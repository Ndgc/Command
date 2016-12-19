#ifndef STATE_H
#define STATE_H

#include <SDL.h>


class State
{
    public:
        State();
        State(SDL_Renderer* ren);
        virtual ~State();
        virtual bool update();
        virtual bool event(SDL_Event e);
        virtual bool draw(SDL_Renderer* r);

    protected:
        SDL_Renderer* renderer;

    private:
};

#endif STATE_H
