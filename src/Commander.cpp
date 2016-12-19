//Commander, intended to be an RTS, but heck if i know.

#include "Commander.h"
#include "SDL.h"

//constructor.
Commander::Commander(SDL_Renderer* ren)
{
    //this is probably bad. Holding onto it for unit constructures.
    renderer=ren;

    //add one friendly unit, and one enemy unit, and select the new friendly.
    units.push_back(Soldier(200,200,ren));
    SelUnit=units.begin();
    enemies.push_back(Target(320,100,ren));
}

Commander::~Commander()
{
//clear lists.
    units.clear();
    enemies.clear();
}

bool Commander::update()
{
//update friendlies. enemies have no updatable properties yet.
std::list<Soldier>::iterator unit=units.begin();
while (unit!=units.end())
{
    unit->update(enemies);
    unit++;
}
}

bool Commander::event(SDL_Event e)
{
//event handler, Should really change it to a case statement.

if (e.type==SDL_MOUSEBUTTONDOWN)//Mice events:
{
    if (e.button.button==SDL_BUTTON_RIGHT)// if right click, order move.
    {
        if (e.button.y<460)//that is, if they've clicked on the field, and not the info bar.
            SelUnit->moveto(e.button.x,e.button.y);
    }
    if (e.button.button==SDL_BUTTON_LEFT)//if left click, try to select a unit.
    {
        std::list<Soldier>::iterator unit=units.begin();
        while (unit!=units.end())
        {
            if (unit->pointinside(e.button.x,e.button.y))
                SelUnit=unit;
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
        units.push_back(Soldier(x,y,renderer));
    }
    if (e.key.keysym.sym==SDLK_2) //if 2 is pressed, create an enemy at the mouse.
    {
        int x, y;
        SDL_GetMouseState(&x,&y);
        enemies.push_back(Target(x,y,renderer));
    }
}
}

//drawing.
bool Commander::draw(SDL_Renderer* r)
{
//paint background.
SDL_SetRenderDrawColor(r,0,0,0,0);
SDL_RenderClear(r);

//draw friendlies.
std::list<Soldier>::iterator unit=units.begin();
while (unit!=units.end())
{
unit->draw(r);
unit++;
}

//draw enemies.
std::list<Target>::iterator enemy=enemies.begin();
while (enemy!=enemies.end())
{
enemy->draw(r);
enemy++;
}

//draw a small HUD at the bottom, showing the selected unit.

//draw the HUD backdrop
SDL_Rect HUDArea={0,460,640,20};
SDL_SetRenderDrawColor(r,255,0,0,0);
SDL_RenderFillRect(r,&HUDArea);
//draw the unit icon.
HUDArea={0,460,20,20};
SDL_RenderCopy(r,SelUnit->getIcon(),NULL,&HUDArea);
SDL_RenderPresent(r);
}
