//Friendly soldiers. Can be ordered around.

#include "Soldier.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

#include <float.h>


Soldier::Soldier(float x, float y,SDL_Renderer* ren)
{
    //Set position, and target.
    this->x=x;
    this->y=y;
    movetox=x;
    movetoy=y;

    //Create a randomly coloured square texture, so they don't all look the same.
    SDL_Surface* Sketch;
    Sketch=SDL_CreateRGBSurface(0,20,20,32,0,0,0,0);
    SDL_FillRect(Sketch,NULL,SDL_MapRGBA(Sketch->format,20,rand()%255,rand()%255,255));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    SDL_FreeSurface(Sketch);

}

Soldier::~Soldier()
{
    SDL_DestroyTexture(Icon);
}

//set a destination.
bool Soldier::moveto(float a, float b)
{
    movetox=a;
    movetoy=b;
    return true;
}

bool Soldier::update(std::list<Target> Enemies)
{
//Movement. Probably a little calculation intensive, but bigger worries exist.
//find the vector you want to move towards.
float vx=movetox-x;
float vy=movetoy-y;
float vabs=sqrt(pow(vx,2)+pow(vy,2));
//Normalise the vector, and move.
x+=vx/vabs;
y+=vy/vabs;
//if close enough, snap to target.
if (vabs<1)
{
    x=movetox;
    y=movetoy;
}

//Logic to find targets. Currently only finds closest target.
double closest=DBL_MAX;
//variables for distance
double targetx;
double targety;
double dist=0;

std::list<Target>::iterator enemy=Enemies.begin();

while (enemy!=Enemies.end())
    {
    targetx=enemy->getX();
    targety=enemy->getY();
    //x axis distance to power 2.
    targetx-=x;
    targetx=abs(targetx);
    if(targetx!=0)
        targetx=pow(targetx,2);
    //y axis distance to power 2.
    targety-=y;
    targety=abs(targety);

    if(targety!=0)
        targety=pow(targety,2);
    //the sqrt is unnecessary, but gives me peace of mind
    dist=sqrt(targetx+targety);
    //if closer than the previous closest, set new closest enemy as current target.
    if (dist<closest)
    {
        CurrentTarget=enemy;
        closest=dist;
    }
enemy++;
}
return true;
}

bool Soldier::draw(SDL_Renderer* ren)
{
//draw this units texture.
SDL_Rect r = {x-10,y-10,20,20};
SDL_RenderCopy(ren,Icon,NULL,&r);

//Draw a line to the current target (should be closest)
SDL_SetRenderDrawColor(ren,255,0,0,0);
float targetx=CurrentTarget->getX();
float targety=CurrentTarget->getY();
SDL_RenderDrawLine(ren,x,y,targetx,targety);
}


//function to find if you are being clicked on.
bool Soldier::pointinside(int Px, int Py)
{
if (Px>x-10 && Px<x+10)
    if (Py>y-10 && Py<y+10)
        return true;

return false;
}


