//generic enemy target. Can't move, can't shoot, can't even die yet. Exists to be targeted.
//should probably inherit from an entity class shared with Soldier that implements stuff like drawing and position.

#include "Soldiers\Target.h"
#include "Commander.h"
#include <stdlib.h>

Target::Target(int xVal, int yVal)
{
    //position
    x=xVal;
    y=yVal;

    dead=false;
}

Target::~Target()
{

}
void Target::createIcon()
{
    extern Commander* s;
    SDL_Renderer* ren=s->getRenderer();
        Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    //Create a randomly coloured square texture, so they don't all look the same.
    SDL_Surface* Sketch;
    Sketch=SDL_CreateRGBSurface(0,20,20,32, rmask, gmask, bmask, amask);
    if (Sketch == NULL) {
        printf("CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    SDL_FillRect(Sketch,NULL,SDL_MapRGB(Sketch->format,100+rand()%105,20,rand()%20));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    if (Icon == NULL) {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());

    }
    SDL_FreeSurface(Sketch);
}

bool Target::update()
{
    update_movement();
    return true;
}

bool Target::update_movement()
{
    extern Commander* s;
    y+=get_movementspeed();
    //advance if you've reached the end
    if (y>=s->get_battlefield_height()) advance();
    return true;
}

bool Target::advance()
{
    extern Commander* s;
    s->lose_lives(1);
    advanced=true;
    return true;
}





