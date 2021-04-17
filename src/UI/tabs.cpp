#include "UI\tabs.h"
#include "UI\MenuButtons.h"

Tab_ButtonCommand::Tab_ButtonCommand()
{

}

Tab_ButtonCommand::~Tab_ButtonCommand()
{

}

void Tab_ButtonCommand::createIcon(SDL_Renderer* ren)
{
    SDL_Surface *surf;
    surf=SDL_LoadBMP("./img/Command.bmp");
    Icon=SDL_CreateTextureFromSurface(ren,surf);
}

Tab_ButtonSoldiers::Tab_ButtonSoldiers()
{

}

Tab_ButtonSoldiers::~Tab_ButtonSoldiers()
{

}

void Tab_ButtonSoldiers::createIcon(SDL_Renderer* ren)
{
     SDL_Surface *surf;
    surf=SDL_LoadBMP("./img/Soldiers.bmp");
    Icon=SDL_CreateTextureFromSurface(ren,surf);   
}