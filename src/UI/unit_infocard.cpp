#include "UI\unit_infocard.h"

#include <map>
#include <Commander.h>

unit_infocard::unit_infocard()
{
font=TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf",20);
    
}

unit_infocard::~unit_infocard()
{

}

bool unit_infocard::draw()
{
    extern Commander* s;
    SDL_Renderer* r=s->getRenderer();

    SDL_SetRenderDrawColor(r,255,233,127,255);
    SDL_RenderFillRect(r,NULL);
    std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit;
    unit=s->units.find(s->SelUnit);
    //make sure the current unit exists.
    if (unit!=s->units.end())
    {
        //draw the unit icon.
        SDL_Rect IconArea={0,0,60,60};
        SDL_RenderCopy(r,unit->second->getIcon(),NULL,&IconArea);
        
        SDL_Color Black = { 0, 0, 0 };
        std::string str;
        //Unit Name
        str = "Unit Name : " + (unit->second->name);
        SDL_Surface *surf = TTF_RenderText_Solid(font,  str.c_str() , Black);
        SDL_Texture * tex = SDL_CreateTextureFromSurface(r,surf);
        int w,h;
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        SDL_Rect NameArea={65,0,w,h};
        SDL_RenderCopy(r,tex,NULL,&NameArea);
        //clean up
        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surf);

        //Weapon Name
        str = "Weapon : " + (unit->second->unit_weapon->get_name());
        surf = TTF_RenderText_Solid(font,  str.c_str() , Black);
        tex = SDL_CreateTextureFromSurface(r,surf);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        NameArea={65,22,w,h};
        SDL_RenderCopy(r,tex,NULL,&NameArea);
        //clean up
        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surf);

        //Aim Skill
        str = "Aim : " + std::to_string(unit->second->get_aim());
        surf = TTF_RenderText_Solid(font,  str.c_str() , Black);
        tex = SDL_CreateTextureFromSurface(r,surf);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        NameArea={65,44,w,h};
        SDL_RenderCopy(r,tex,NULL,&NameArea);
        //clean up
        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surf);

        //health
        SDL_Rect HP_BAR{0,65,(width*unit->second->get_health())/unit->second->get_max_health(),24};
        SDL_SetRenderDrawColor(r,255,0,0,255);
        SDL_RenderFillRect(r,&HP_BAR);
        str = "Health : " + std::to_string(unit->second->get_health());
        surf = TTF_RenderText_Solid(font,  str.c_str() , Black);
        tex = SDL_CreateTextureFromSurface(r,surf);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        NameArea={0,67,w,h};
        SDL_RenderCopy(r,tex,NULL,&NameArea);
        //clean up
        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surf);
        return true;

    }



 return false;
}

bool unit_infocard::update()
{
 return true;
}