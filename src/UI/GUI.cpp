#include "UI\GUI.h"
#include "Commander.h"
#include "UI\MenuButtons.h"
#include "UI\tabs.h"

#include <string>
#include <iostream>
GUI::GUI()
{
    //ctor
    font=TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf",12);
    large_font=TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf",72);
    if(!font) {
        printf(TTF_GetError());
    }
    submenuptr=nullptr;

}

GUI::~GUI()
{
    //dtor
}

bool GUI::postinit()
{
    //create menu items
    std::shared_ptr<Tab_Button> tab;
    tab=std::make_shared<Tab_ButtonCommand>();
        tab->addButton(std::make_shared<ButtonForceWave>());
    addButton(tab);
    tab=std::make_shared<Tab_ButtonSoldiers>();
        tab->addButton(std::make_shared<ButtonCreateRifle>());
        tab->addButton(std::make_shared<ButtonCreateShotgun>());
    addButton(tab);
    return true;
}

bool GUI::addButton(std::shared_ptr<Button> new_button)
{
menu.push_back(new_button);
new_button->postinit(menu.size()-1);
sortButtons();
return true;
}

//place buttons in a row
bool GUI::sortButtons()
{
    for (unsigned int i=0;i<menu.size();i++)
    {
        menu[i]->setPosition({(int)i*40,0,40,40});
    }
    return true;
}

bool GUI::update()
{
    //clear the submenu if it's not actually referenced anywhere else.
    if (submenuptr.use_count()==1)
    {
        submenuptr=nullptr;
    }

    std::vector<std::shared_ptr<Button>>::iterator menu_Iterator=menu.begin();
    while(menu_Iterator!=menu.end())
    {
        (*menu_Iterator)->update();
    }

    return true;
}

bool GUI::event(SDL_Event e)

{
extern Commander* s;
SDL_Rect offset;

if (e.type==SDL_MOUSEBUTTONDOWN)//Mice events:
{
    //if the mouse is in the buttons
    if (s->game_window.pointinside(viewport::menu,e.button.x,e.button.y))
    {
        offset=s->game_window.get_viewport(viewport::menu);
        if (e.button.button==SDL_BUTTON_LEFT)//if left click, try to click a button.
        {
            std::vector<std::shared_ptr<Button>>::iterator menu_Iterator=menu.begin();
            while(menu_Iterator!=menu.end())
            {
                if ((*menu_Iterator)->pointinside(e.button.x-offset.x,e.button.y-offset.y))
                {
                    (*menu_Iterator)->onclick();
                    return true;
                }
                menu_Iterator++;
            }
        }

        if (submenuptr!=nullptr)
        {
            submenuptr->click_tab(e.button.x-offset.x,e.button.y-offset.y);
        }


    }
    //if the mouse is in the game area
    if (s->game_window.pointinside(viewport::game,e.button.x,e.button.y))
    {  
        offset=s->game_window.get_viewport(viewport::game);
        if (e.button.button==SDL_BUTTON_LEFT)//if left click, try to select a unit.
        {
            
            std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit=s->units.begin();
            while (unit!=s->units.end())
            {
                if (unit->second->pointinside(e.button.x-offset.x,e.button.y-offset.y))
                    s->SelUnit=unit->second->getid();
                unit++;
            }
        }
        if (e.button.button==SDL_BUTTON_RIGHT)// if right click, order move.
        {
                std::map<unsigned int,std::shared_ptr<Allied_Soldier>>::iterator unit;
                unit=s->units.find(s->SelUnit);
                //make sure the current unit exists.
                if (unit!=s->units.end())
                {
                    unit->second->moveto(e.button.x-offset.x,e.button.y-offset.y);
                }
                
        }

    }
}
return false;
}

bool GUI::draw()
{

    extern Commander* s;
    SDL_Renderer* r=s->getRenderer();
  

    SDL_Color white = { 255, 255, 255 };
    std::string str;
    SDL_Rect HUDArea;
    int w,h;
    SDL_Surface *surf;
    SDL_Texture * tex;


    SDL_SetRenderDrawColor(r,73,42,56,255);
    SDL_RenderFillRect(r,NULL);


    //Draw UI buttons last so they're always on top
    std::vector<std::shared_ptr<Button>>::iterator menu_Iterator=menu.begin();
    while(menu_Iterator!=menu.end())
    {
        (*menu_Iterator)->draw();
        menu_Iterator++;
    }

    if (submenuptr!=nullptr)
    {
        submenuptr->draw_tab();
    }

    if (s->is_gameover())
    {
        //reset viewport for the gameover
        SDL_RenderSetViewport(r,NULL);
        


        str = "GAME OVER";
        surf = TTF_RenderText_Solid(large_font,  str.c_str() , white);
        tex = SDL_CreateTextureFromSurface(r,surf);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        HUDArea={320-w/2,240-h/2,w,h};
        SDL_RenderCopy(r,tex,NULL,&HUDArea);
        //clean up
        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surf);
    }

    return true;
}
