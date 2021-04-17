#include "UI\MenuButtons.h"
#include "Commander.h"
#include "Soldiers\Allied_Soldier.h"
#include "Weapons\weapon.h"
#include "Weapons\shotgun.h"

ButtonCreateRifle::ButtonCreateRifle():Button()
{
    //ctor
}

void ButtonCreateRifle::createIcon(SDL_Renderer* ren)
{
    SDL_Surface *surf;
    surf=SDL_LoadBMP("./img/rifle.bmp");
    Icon=SDL_CreateTextureFromSurface(ren,surf);
}

ButtonCreateRifle::~ButtonCreateRifle()
{
    //dtor
}

bool ButtonCreateRifle::onclick()
{
    extern Commander* s;
    unsigned int id;
    int x;

    if (s->get_resource_points()>=3)
    {
        s->spend_resource_points(3);
        x=rand()%s->get_battlefield_width();

        id=s->create_ally(std::make_shared<Allied_Soldier>(x,s->get_battlefield_height(),std::make_shared<weapon>()));


        std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator it;
        it=s->units.find(id);
        it->second->moveto(x,s->get_battlefield_height()-20);
    }
    return true;
}

ButtonCreateShotgun::ButtonCreateShotgun():Button()
{
    //ctor
}

void ButtonCreateShotgun::createIcon(SDL_Renderer* ren)
{
    SDL_Surface *surf;
    surf=SDL_LoadBMP("./img/shotgun.bmp");
    Icon=SDL_CreateTextureFromSurface(ren,surf);
}

ButtonCreateShotgun::~ButtonCreateShotgun()
{
    //dtor
}

bool ButtonCreateShotgun::onclick()
{
    extern Commander* s;
    unsigned int id;
    int x;

    if (s->get_resource_points()>=3)
    {
        s->spend_resource_points(3);
        x=rand()%s->get_battlefield_width();

        id=s->create_ally(std::make_shared<Allied_Soldier>(x,s->get_battlefield_height(),std::make_shared<shotgun>()));


        std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator it;
        it=s->units.find(id);
        it->second->moveto(x,s->get_battlefield_height()-20);
    }
    return true;
}




ButtonForceWave::ButtonForceWave():Button()
{

}

void ButtonForceWave::createIcon(SDL_Renderer* ren)
{
    SDL_Surface *surf;
    surf=SDL_LoadBMP("./img/FastForward.bmp");
    Icon=SDL_CreateTextureFromSurface(ren,surf);
}

ButtonForceWave::~ButtonForceWave()
{

}

bool ButtonForceWave::onclick()
{
    extern Commander* s;
    s->WaveControl.next_wave();
    return true;
}
