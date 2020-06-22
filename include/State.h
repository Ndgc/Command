#ifndef STATE_H
#define STATE_H
#include <SDL.h>

class State
{
    public:
        State();
        virtual ~State();
        virtual bool update();
        virtual bool event(SDL_Event E);
        virtual bool draw(SDL_Renderer* R);
    protected:
    private:
};

#endif // STATE_H
