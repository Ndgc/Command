//Friendly soldiers. Can be ordered around.

#include "Soldiers\Allied_Soldier.h"
#include "Commander.h"
#include <math.h>

#include <Weapons\shotgun.h>




Allied_Soldier::Allied_Soldier(float x, float y,std::shared_ptr<weapon>gun)
{
    //Set position, and target.
    this->x=x;
    this->y=y;
    movetox=x;
    movetoy=y;
    w=10;
    h=10;

    currentstate=AI_State::idle;
    aimcooldown=0;
    idlecooldown=0;
    actionspeed=10;
    health=75;

    if (gun==NULL)
    {
        if (rand()%2==0)
        {
            unit_weapon=std::make_shared<shotgun>();
        }
        else
        {
            unit_weapon=std::make_shared<weapon>();
        }
    }
    else
    {
        unit_weapon=gun;
    }


}

Allied_Soldier::~Allied_Soldier()
{
    //SDL_DestroyTexture(Icon);
}

void Allied_Soldier::createIcon()
{
    extern Commander* s;
    SDL_Renderer* ren=s->getRenderer();

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

    SDL_FillRect(Sketch,NULL,SDL_MapRGB(Sketch->format,20,150+rand()%105,20));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    if (Icon == NULL) {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());

    }
    SDL_FreeSurface(Sketch);

}

//set a destination.
bool Allied_Soldier::moveto(float a, float b)
{
    movetox=a;
    movetoy=b;
    currentstate=AI_State::movement;
    return true;
}



bool Allied_Soldier::update()
{

if (currentstate==AI_State::movement) update_movement();
if (currentstate==AI_State::idle) update_idle();
if (currentstate==AI_State::aim) update_aim();
return true;
}

//if the soldier has nothing on its plate, perform idle actions (e.g. find a target, reload weapon, apply buffs)
bool Allied_Soldier::update_idle()
{
extern Commander* s;
std::map<unsigned int,std::shared_ptr<Target>>::iterator enemy;
idlecooldown+=actionspeed;

//find a target after 1000 ticks.
if (idlecooldown>1000)
{
//reset cooldown if no enemies exist
if (s->enemies.size()==0)
{
    idlecooldown=0;
    CurrentTargetx=x;
    CurrentTargety=y;
}
else
{
//Logic to find targets. Currently only finds closest target.
double closest=DBL_MAX;
//variables for distance
double targetx;
double targety;
double dist=0;

enemy=s->enemies.begin();

while (enemy!=s->enemies.end())
    {
    targetx=enemy->second->getX();
    targety=enemy->second->getY();

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
        CurrentTarget=enemy->second->getid();
        closest=dist;
    }
enemy++;
}
aimcooldown=1000;
currentstate=AI_State::aim;
    enemy=s->enemies.find(CurrentTarget);
    CurrentTargetx=enemy->second->getX();
    CurrentTargety=enemy->second->getY();
}
}
else
{
    CurrentTargetx=x;
    CurrentTargety=y;
}
return true;
}


bool Allied_Soldier::update_movement()
{
//Movement. Probably a little calculation intensive, but bigger worries exist.
//find the vector you want to move towards.
float vx=movetox-x;
float vy=movetoy-y;
float vabs=sqrt(pow(vx,2)+pow(vy,2));
//Normalise the vector, and move.
x+=get_movementspeed()*vx/vabs;
y+=get_movementspeed()*vy/vabs;
//if close enough, snap to target, and become idle
if (vabs<get_movementspeed())
{
    x=movetox;
    y=movetoy;
    currentstate=AI_State::idle;
    idlecooldown=0;
}

CurrentTargetx=movetox;
CurrentTargety=movetoy;
return true;
}


bool Allied_Soldier::update_aim()
{
    extern Commander* s;
    //
    std::map<unsigned int,std::shared_ptr<Target>>::iterator enemy;
    enemy=s->enemies.find(CurrentTarget);

    //make sure the current target exists. if not, go back to idle
    if (enemy==s->enemies.end())
        {
        currentstate=AI_State::idle;
        idlecooldown=0;
        CurrentTargetx=x;
        CurrentTargety=y;
        return true;
        }

    CurrentTargetx=enemy->second->getX();
    CurrentTargety=enemy->second->getY();


    aimcooldown-=actionspeed;
    if (aimcooldown<0)
    {


        fire_weapon();
        aimcooldown=1000;
    }
    return true;
}

bool Allied_Soldier::fire_weapon()
{
    extern Commander* s;
    std::map<unsigned int,std::shared_ptr<Target>>::iterator enemy;
    enemy=s->enemies.find(CurrentTarget);
    unit_weapon->shoot(this,enemy->second);
    return true;
}


bool Allied_Soldier::draw(SDL_Renderer* ren)
{
double angle;
//draw this units texture.
angle=atan2(y-CurrentTargety,x-CurrentTargetx)*180/3.14159;

SDL_Rect r = {int(x)-10,int(y)-10,20,20};
SDL_RenderCopyEx(ren,getIcon(),NULL,&r,angle,NULL,SDL_FLIP_NONE);
//Base_Soldier::draw(ren);


//Draw a line to the current target (should be closest)
SDL_SetRenderDrawColor(ren,255,255*aimcooldown/1000,0,0);

SDL_RenderDrawLine(ren,x,y,CurrentTargetx,CurrentTargety);
return true;
}





