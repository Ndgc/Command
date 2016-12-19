//State. entirely virtual class designed to hold a game.
//only contains three methods:
//update, draw and event.

#include "State.h"
#include <SDL.h>
#include <stdlib.h>
State::State()
{
    //ctor
}

State::~State()
{
    //dtor
}

//In an actual game this would handle logic.
bool State::update()
{


}

//In an actual game, this would handle rendering. The argument is so it can draw on something.
bool State::draw(SDL_Renderer* r)
{
            //give epilepsy as a reward for forgetting a draw method.
            SDL_SetRenderDrawColor(r,0,rand()%255,100,0);
            SDL_RenderClear(r);
            SDL_RenderPresent(r);
}

//in an actual game this is an SDL Event handler
bool State::event(SDL_Event e)
{

}
