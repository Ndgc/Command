//Friendly soldiers. Can be ordered around.

#include "Allied_Soldier.h"
#include "Commander.h"




Allied_Soldier::Allied_Soldier(unsigned int key,float x, float y,SDL_Renderer* ren)
{
    id=key;
    //Set position, and target.
    this->x=x;
    this->y=y;
    movetox=x;
    movetoy=y;
    w=10;
    h=10;
    createIcon(ren);
    SDL_RenderCopy(ren,getIcon(),NULL,NULL);
}

Allied_Soldier::~Allied_Soldier()
{
    //SDL_DestroyTexture(Icon);
}

void Allied_Soldier::createIcon(SDL_Renderer* ren)
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

    //Create a randomly coloured square texture, so they don't all look the same.
    SDL_Surface* Sketch;
    Sketch=SDL_CreateRGBSurface(0,20,20,32, rmask, gmask, bmask, amask);
    if (Sketch == NULL) {
        printf("CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    SDL_FillRect(Sketch,NULL,SDL_MapRGB(Sketch->format,20,rand()%255,rand()%255));
    Icon=SDL_CreateTextureFromSurface(ren,Sketch);
    if (Icon == NULL) {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());

    }
    SDL_FreeSurface(Sketch);

    int w, h;
    SDL_QueryTexture(Icon, NULL, NULL, &w, &h);
    std::cout<<"Texture created :" << Icon<<std::endl<<w<<","<<h<<std::endl;

    currentstate=idle;
    aimcooldown=0;
    idlecooldown=0;
    actionspeed=10;

}

//set a destination.
bool Allied_Soldier::moveto(float a, float b)
{
    movetox=a;
    movetoy=b;
    currentstate=movement;
    return true;
}



bool Allied_Soldier::update()
{

if (currentstate==movement) update_movement();
if (currentstate==idle) update_idle();
if (currentstate==aim) update_aim();
return true;
}

//if the soldier has nothing on its plate, perform idle actions (e.g. find a target, reload weapon, apply buffs)
bool Allied_Soldier::update_idle()
{
extern Commander* s;
std::map<unsigned int,Target>::iterator enemy;
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
    targetx=enemy->second.getX();
    targety=enemy->second.getY();

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
        CurrentTarget=enemy->second.getid();
        closest=dist;
    }
enemy++;
}
aimcooldown=1000;
currentstate=aim;
    enemy=s->enemies.find(CurrentTarget);
    CurrentTargetx=enemy->second.getX();
    CurrentTargety=enemy->second.getY();
}
}
else
{
    CurrentTargetx=x;
    CurrentTargety=y;
}
}


bool Allied_Soldier::update_movement()
{
//Movement. Probably a little calculation intensive, but bigger worries exist.
//find the vector you want to move towards.
float vx=movetox-x;
float vy=movetoy-y;
float vabs=sqrt(pow(vx,2)+pow(vy,2));
//Normalise the vector, and move.
x+=vx/vabs;
y+=vy/vabs;
//if close enough, snap to target, and become idle
if (vabs<1)
{
    x=movetox;
    y=movetoy;
    currentstate=idle;
    idlecooldown=0;
}

CurrentTargetx=movetox;
CurrentTargety=movetoy;
return true;
}


bool Allied_Soldier::update_aim()
{
    extern Commander* s;
    std::map<unsigned int,Target>::iterator enemy;
    enemy=s->enemies.find(CurrentTarget);

    if (enemy==s->enemies.end()) //make sure the current target exists. if not, go back to idle
        {
        currentstate=idle;
        idlecooldown=0;
        }

    aimcooldown-=actionspeed;
    if (aimcooldown<0)
    {


        fire_weapon();
        aimcooldown=1000;
    }
    enemy=s->enemies.find(CurrentTarget);
    CurrentTargetx=enemy->second.getX();
    CurrentTargety=enemy->second.getY();

}

bool Allied_Soldier::fire_weapon()
{
    extern Commander* s;
    std::map<unsigned int,Target>::iterator enemy;
    enemy=s->enemies.find(CurrentTarget);
    std::cout<<"Shot fired by unit: "<<id<<" at unit "<<CurrentTarget<<" Evasion : "<< enemy->second.get_evasion() <<std::endl;

    int skillresult;
    int skilldifficulty;

    skillresult=rand()%100+get_aim();
    skilldifficulty=enemy->second.get_evasion();

    if (skillresult>skilldifficulty)
    {
        std::cout<<"Result :" << skillresult<<" HIT"<<std::endl;
        enemy->second.take_damage(10);
        return true;
    }
    else
    {
        std::cout<<"Result :" << skillresult<<" MISS"<<std::endl;
        return false;
    }

}


bool Allied_Soldier::draw(SDL_Renderer* ren)
{
//draw this units texture.
Base_Soldier::draw(ren);


//Draw a line to the current target (should be closest)
SDL_SetRenderDrawColor(ren,255,255*aimcooldown/1000,0,0);

SDL_RenderDrawLine(ren,x,y,CurrentTargetx,CurrentTargety);
return true;
}





