//Commander, intended to be an RTS, but heck if i know.

#include "Commander.h"

//constructor.
Commander::Commander(SDL_Renderer* ren)
{
    nextid=0;
    //this is probably bad. Holding onto it for unit constructurs.
    renderer=ren;

    //add one friendly unit, and one enemy unit, and select the new friendly.
    units.insert(std::pair<unsigned int,Allied_Soldier>(nextid,Allied_Soldier(nextid,200,200,ren)));
    SelUnit=nextid;
    nextid++;

    enemies.insert(std::pair<unsigned int,Target>(nextid,Target(nextid,320,100,ren)));
    nextid++;
}

Commander::~Commander()
{
//clear maps.
    units.clear();
    enemies.clear();
}

bool Commander::update()
{
//declare iterators
std::map<unsigned int,Allied_Soldier>::iterator unit=units.begin();
std::map<unsigned int,Target>::iterator enemy=enemies.begin();
//update friendlies
while (unit!=units.end())
{
    unit->second.update();
    unit++;
}
//update enemies
while (enemy!=enemies.end())
{
        enemy->second.update();
        enemy++;
}



//clean up dead/advanced units
enemy=enemies.begin();
while (enemy!=enemies.end())
{
    if (enemy->second.isdead()==true||enemy->second.has_advanced()==true)
    {
        enemies.erase(enemy++);
    }
    else
    {
        enemy++;
    }
}


return true;
}

bool Commander::event(SDL_Event e)
{
//event handler, Should really change it to a case statement.

if (e.type==SDL_MOUSEBUTTONDOWN)//Mice events:
{
    if (e.button.button==SDL_BUTTON_RIGHT)// if right click, order move.
    {
        if (e.button.y<460)//that is, if they've clicked on the field, and not the info bar.
            units.find(SelUnit)->second. moveto(e.button.x,e.button.y);
    }
    if (e.button.button==SDL_BUTTON_LEFT)//if left click, try to select a unit.
    {
        std::map<unsigned int,Allied_Soldier>::iterator unit=units.begin();
        while (unit!=units.end())
        {
            if (unit->second.pointinside(e.button.x,e.button.y))
                SelUnit=unit->second.getid();
            unit++;
        }
    }
}
if (e.type==SDL_KEYDOWN)//keyboard events, basically only used to create objects.
{
    if (e.key.keysym.sym==SDLK_1)  //If 1 is pressed, create a friendly.
    {
        int x, y;
        SDL_GetMouseState(&x,&y);
        units.insert(std::pair<unsigned int,Allied_Soldier>(nextid,Allied_Soldier(nextid,x,y,renderer)));
        nextid++;
    }
    if (e.key.keysym.sym==SDLK_2) //if 2 is pressed, create an enemy at the mouse.
    {
        int x, y;
        SDL_GetMouseState(&x,&y);
        enemies.insert(std::pair<unsigned int,Target>(nextid,Target(nextid,x,y,renderer)));
        nextid++;
    }
}
return true;
}

//drawing.
bool Commander::draw(SDL_Renderer* r)
{
//paint background.
SDL_SetRenderDrawColor(r,0,0,0,0);
SDL_RenderClear(r);

//draw friendlies.
std::map<unsigned int,Allied_Soldier>::iterator unit=units.begin();
while (unit!=units.end())
{
    unit->second.draw(r);
    unit++;
}

//draw enemies.
std::map<unsigned int,Target>::iterator enemy=enemies.begin();
while (enemy!=enemies.end())
{
    enemy->second.draw(r);
    enemy++;
}

//draw a small HUD at the bottom, showing the selected unit.

//draw the HUD backdrop
SDL_Rect HUDArea={0,460,640,20};
SDL_SetRenderDrawColor(r,255,0,0,0);
SDL_RenderFillRect(r,&HUDArea);
//draw the unit icon.
HUDArea={0,460,20,20};
SDL_RenderCopy(r,units.find(SelUnit)->second.getIcon(),NULL,&HUDArea);
SDL_RenderPresent(r);
return true;
}
