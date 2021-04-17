#include "UI\game_infocard.h"

#include <map>
#include <Commander.h>

game_infocard::game_infocard()
{
font=TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf",20);
    
}

game_infocard::~game_infocard()
{

}

bool game_infocard::draw()
{
    extern Commander* s;
    SDL_Renderer* r=s->getRenderer();

    SDL_SetRenderDrawColor(r,42,73,56,255);
    SDL_RenderFillRect(r,NULL);

    //draw progress to next wave
    int width=400*s->WaveControl.wave_progress();

    SDL_Rect HUDArea={0,0,width,10};
    SDL_SetRenderDrawColor(r,255,0,0,0);
    SDL_RenderFillRect(r,&HUDArea);

    //write wavenumbers/kills. If i wanted this to be faster, i could probably make this texture only change when the quantity does.
    SDL_Color white = { 255, 255, 255 };
    std::string str;
    str = "Wave : " + std::to_string(s->WaveControl.getwavenumber());
    SDL_Surface *surf = TTF_RenderText_Solid(font,  str.c_str() , white);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(r,surf);
    int w,h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    HUDArea={3,15,w,h};
    SDL_RenderCopy(r,tex,NULL,&HUDArea);
    //clean up
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
    //kills
    str = "Kills : " + std::to_string(s->getkills());
    surf = TTF_RenderText_Solid(font,  str.c_str() , white);
    tex = SDL_CreateTextureFromSurface(r,surf);
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    HUDArea={3,HUDArea.h+18,w,h};
    SDL_RenderCopy(r,tex,NULL,&HUDArea);
    //clean up
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
    //Resource Points
    str = "Resource Points : " + std::to_string(s->get_resource_points());
    surf = TTF_RenderText_Solid(font,  str.c_str() , white);
    tex = SDL_CreateTextureFromSurface(r,surf);
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    HUDArea={3,HUDArea.h+36,w,h};
    SDL_RenderCopy(r,tex,NULL,&HUDArea);
    //clean up
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);

    //Resource Points
    str = "Lives Lost : " + std::to_string(s->get_lives_lost());
    surf = TTF_RenderText_Solid(font,  str.c_str() , white);
    tex = SDL_CreateTextureFromSurface(r,surf);
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    HUDArea={3,HUDArea.h+54,w,h};
    SDL_RenderCopy(r,tex,NULL,&HUDArea);
    //clean up
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
    return true;
}