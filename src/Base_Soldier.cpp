#include "Base_Soldier.h"
Base_Soldier::Base_Soldier()
{
    //ctor
}

Base_Soldier::~Base_Soldier()
{

}

bool Base_Soldier::draw(SDL_Renderer* ren)
{
    int w, h;
    SDL_QueryTexture(getIcon(), NULL, NULL, &w, &h);
    //std::cout<<w<<" , "<<h<<std::endl;

    SDL_Rect r = {x-10,y-10,20,20};
    //Just draw a rectangle
    SDL_SetRenderDrawColor(ren,255,255,255,255);
    SDL_RenderFillRect(ren,&r);

    SDL_RenderCopy(ren,getIcon(),NULL,&r);


    return true;
}

//function to find if you are being clicked on.
bool Base_Soldier::pointinside(int Px, int Py)
{
if (Px>x-w && Px<x+w)
    if (Py>y-h && Py<y+h)
        return true;

return false;
}

//getters.
float Base_Soldier::getX()
{
    return x;
}

float Base_Soldier::getY()
{
    return y;
}

bool Base_Soldier::take_damage(int damage)
{
    health-=damage;
    if (health<0)
    {
        dead=true;
    }

}

bool Base_Soldier::advance()
{
    advanced=true;
}
