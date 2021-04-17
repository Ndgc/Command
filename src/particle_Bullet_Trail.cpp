#include "particle_Bullet_Trail.h"
#include <Commander.h>
#include <iostream>

particle_Bullet_Trail::particle_Bullet_Trail(int x1,int y1,int x2,int y2,int lifetime):particle{lifetime}
{
    //ctor
    this->x1=x1;
    this->y1=y1;

    this->x2=x2;
    this->y2=y2;
    starting_lifetime=lifetime;

}

particle_Bullet_Trail::~particle_Bullet_Trail()
{
    //dtor
}

bool particle_Bullet_Trail::draw()
{
    extern Commander* s;
    SDL_Renderer* ren;
    ren=s->getRenderer();
    double shade=255*lifetime/starting_lifetime;
    SDL_SetRenderDrawColor(ren,0,10,shade,10);

    SDL_RenderDrawLine(ren,x1,y1,x2,y2);
    return true;
}
