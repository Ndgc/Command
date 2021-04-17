#include "UI\Button.h"
#include "Commander.h"
#include "UI\MenuButtons.h"
#include <iostream>
Button::Button()
{
    Position={0,0,40,40};
    //ctor
}

Button::~Button()
{
    //dtor
}

bool Button::postinit(int index)
{
    extern Commander* s;

    createIcon(s->getRenderer());
    id=index;
    return true;
}
bool Button::onclick()
{
        std::cout<<"click";
        return true;
}

bool Button::pointinside(int Px, int Py)
{
if (Px>Position.x-Position.w && Px<Position.x+Position.w)
    if (Py>Position.y-Position.h && Py<Position.y+Position.h)
        return true;

return false;
}

void Button::createIcon(SDL_Renderer* ren)
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

    //Create a coloured square texture
    SDL_Surface* Sketch;
    Sketch=SDL_CreateRGBSurface(0,20,20,32, rmask, gmask, bmask, amask);
    if (Sketch == NULL) {
        printf("CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    SDL_FillRect(Sketch,NULL,SDL_MapRGB(Sketch->format,255,255,255));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    if (Icon == NULL) {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());

    }
    SDL_FreeSurface(Sketch);

}

bool Button::update()
{
    return true;
}

bool Button::draw()
{
    extern Commander* s;

    //Copy texture to renderer.
    SDL_RenderCopy(s->getRenderer(),getIcon(),NULL,&Position);
    return true;
}
