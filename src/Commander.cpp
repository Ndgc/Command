//Commander, intended to be an RTS, but heck if i know what it might become.

#include "Commander.h"


//constructor.
Commander::Commander(SDL_Renderer* ren)
{
    nextid=0;
    //this might be bad? Holding onto it.
    game_window.set_renderer(ren);
    lives_lost=0;
    kills=0;
    resource_points=0;
    gameover=false;

    
    
}

Commander::~Commander()
{
//clear maps.
    units.clear();
    enemies.clear();
    particles.clear();
}

//Do things that need to pull info from the game state and associated (mainly, they need to call getrenderer())
bool Commander::postinit()
{
    //add two friendly units
    create_ally(std::make_shared<Allied_Soldier>(200,200));
    create_ally(std::make_shared<Allied_Soldier>(100,200));
    //start up the GUI
    UserInterface.postinit();
    return true;
}

bool Commander::update()
{
if (lives_lost>=10) gameover=true;
if (!gameover)
{
//declare iterators
std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit=units.begin();
std::map<unsigned int,std::shared_ptr<Target>>::iterator enemy=enemies.begin();
std::list<std::shared_ptr<particle>>::iterator it_particle=particles.begin();
//update the wave control
WaveControl.update();
//update friendlies
while (unit!=units.end())
{
    unit->second->update();
    unit++;
}
//update enemies
while (enemy!=enemies.end())
{
        enemy->second->update();
        enemy++;
}
//update particle lifetimes
while (it_particle!=particles.end())
{
    (*it_particle)->update();
    it_particle++;
}


//clean up dead/advanced units
enemy=enemies.begin();
while (enemy!=enemies.end())
{
    if (enemy->second->isdead()==true||enemy->second->has_advanced()==true)
    {
        if (enemy->second->isdead()==true)
        {
            kills++;
        }
        enemies.erase(enemy++);
    }
    else
    {
        enemy++;
    }
}
it_particle=particles.begin();
while (it_particle!=particles.end())
{
    if ((*it_particle)->isexpired()==true)
    {
        particles.erase(it_particle++);
    }
    else
    {
        it_particle++;
    }

}


return true;
}
else
{

}
return false;
}

bool Commander::event(SDL_Event e)
{
if (!gameover)
{
//event handler, Should really change it to a case statement.

//GUI gets first dibs
if (!UserInterface.event(e))
{
if (e.type==SDL_MOUSEBUTTONDOWN)//Mice events:
{
    //check that it's inside the game view
/*    SDL_Rect offset=game_window.get_viewport(viewport::game);
    if (game_window.pointinside(viewport::game,e.button.x,e.button.y))
    {
        if (e.button.button==SDL_BUTTON_RIGHT)// if right click, order move.
        {
                std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit;
                unit=units.find(SelUnit);
                //make sure the current unit exists.
                if (unit!=units.end())
                {
                    unit->second->moveto(e.button.x-offset.x,e.button.y-offset.y);
                }
                
        }
        if (e.button.button==SDL_BUTTON_LEFT)//if left click, try to select a unit.
        {
            
            std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit=units.begin();
            while (unit!=units.end())
            {
                if (unit->second->pointinside(e.button.x-offset.x,e.button.y-offset.y))
                    SelUnit=unit->second->getid();
                unit++;
            }
        }
    }*/
}
if (e.type==SDL_KEYUP)//keyboard events, not used at the moment
{

}
}
return true;
}
return false;
}

//drawing.
bool Commander::draw(SDL_Renderer* r)
{

game_window.set_viewport(viewport::game);
//paint background.
SDL_SetRenderDrawColor(r,0,0,0,0);
SDL_RenderClear(r);


//draw friendlies.
std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit=units.begin();
while (unit!=units.end())
{
    unit->second->draw(r);
    unit++;
}

//draw enemies.
std::map<unsigned int,std::shared_ptr<Target>>::iterator enemy=enemies.begin();
while (enemy!=enemies.end())
{
    enemy->second->draw(r);
    enemy++;
}
std::list<std::shared_ptr<particle>>::iterator it_particle=particles.begin();
while (it_particle!=particles.end())
{
    (*it_particle)->draw();
    it_particle++;
}


game_window.set_viewport(viewport::menu);
UserInterface.draw();
game_window.set_viewport(viewport::game_card);
game_info_card.draw();

game_window.set_viewport(viewport::unit_card);
unit_info_card.draw();


//commit rendering
SDL_RenderPresent(r);
return true;
}


unsigned int Commander::create_ally(std::shared_ptr<Allied_Soldier> new_ally)
{
    new_ally->postinit(nextid);
    units.emplace(nextid,new_ally);
    return nextid++;
}

unsigned int Commander::create_enemy (std::shared_ptr<Target> new_enemy)
{
    new_enemy->postinit(nextid);
    enemies.emplace(nextid,new_enemy);
    return nextid++;
}
