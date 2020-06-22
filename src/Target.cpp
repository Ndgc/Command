//generic enemy target. Can't move, can't shoot, can't even die yet. Exists to be targeted.
//should probably inherit from an entity class shared with Soldier that implements stuff like drawing and position.

#include "Target.h"
#include <stdlib.h>

Target::Target(unsigned int key,int xVal, int yVal, SDL_Renderer *ren)
{
    id=key;
    //position
    x=xVal;
    y=yVal;

    //create a texture, but a different colour range to the friendlies.
    createIcon(ren);

    dead=false;
}

Target::~Target()
{

}
void Target::createIcon(SDL_Renderer* ren)
{
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

    SDL_FillRect(Sketch,NULL,SDL_MapRGB(Sketch->format,rand()%255,200,rand()%255));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    if (Icon == NULL) {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());

    }
    SDL_FreeSurface(Sketch);

    int w, h;
    SDL_QueryTexture(Icon, NULL, NULL, &w, &h);
    std::cout<<"Texture created :" << Icon<<std::endl<<w<<","<<h<<std::endl;
}

bool Target::update()
{
    update_movement();
}

bool Target::update_movement()
{
    y+=get_movementspeed();
    //advance if you've reached the end
    if (y>=480) advance();
}





