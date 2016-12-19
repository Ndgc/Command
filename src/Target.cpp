//generic enemy target. Can't move, can't shoot, can't even die yet. Exists to be targeted.
//should probably inherit from an entity class shared with Soldier that implements stuff like drawing and position.

#include "Target.h"
#include <stdlib.h>


Target::Target(int xVal, int yVal, SDL_Renderer *ren)
{
    //position
    x=xVal;
    y=yVal;

    //create a texture, but a different colour range to the friendlies.
    SDL_Surface* Sketch;
    Sketch=SDL_CreateRGBSurface(0,20,20,32,0,0,0,0);
    SDL_Rect r = {0,0,20,20};
    SDL_FillRect(Sketch,NULL,SDL_MapRGB(Sketch->format,rand()%255,240,rand()%255));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    SDL_FreeSurface(Sketch);
}

Target::~Target()
{
    SDL_DestroyTexture(Icon);
}


//getters.
float Target::getX()
{
    return x;
}

float Target::getY()
{
    return y;
}
