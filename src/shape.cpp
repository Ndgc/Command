#include "shape.h"

shape::shape()
{
    //ctor
}

shape::~shape()
{
    //dtor
}

bool shape::draw(SDL_Renderer* ren)
{
    SDL_Rect r = {x-10,y-10,20,20};
    SDL_RenderCopy(ren,Icon,NULL,&r);
}
