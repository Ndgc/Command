#include "Soldiers\Base_Soldier.h"
Base_Soldier::Base_Soldier()
{
    //ctor
}

Base_Soldier::~Base_Soldier()
{

}

bool Base_Soldier::postinit(int key)
{
    id=key;
    name="John Smith " + std::to_string(key);
    createIcon();
    return true;
}

bool Base_Soldier::draw(SDL_Renderer* ren)
{
    int w, h;
    SDL_QueryTexture(getIcon(), NULL, NULL, &w, &h);
    //std::cout<<w<<" , "<<h<<std::endl;

    SDL_Rect r = {int(x)-10,int(y)-10,20,20};
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
    if (health<=0)
    {
        dead=true;
    }
return true;
}

bool Base_Soldier::take_damage(int damage,Base_Soldier* source)
{
    health-=damage;
    if (health<=0 && dead==false)
    {
        source->on_kill(this);
        dead=true;
    }
return true;
}

bool Base_Soldier::on_kill(Base_Soldier* dead_unit)
{
    skill_aim++;
    return true;
}

bool Base_Soldier::advance()
{
    advanced=true;
    return true;
}
