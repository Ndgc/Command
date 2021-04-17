#include "UI\Tab_Button.h"
#include "Commander.h"
#include "UI\MenuButtons.h"
#include <iostream>
Tab_Button::Tab_Button(/* args */)
{

}

Tab_Button::~Tab_Button()
{

}

bool Tab_Button::addButton(std::shared_ptr<Button> new_button)
{
submenu.push_back(new_button);
new_button->postinit(submenu.size()-1);
sortButtons();
return true;
}

//place buttons in a row
bool Tab_Button::sortButtons()
{
    for (unsigned int i=0;i<submenu.size();i++)
    {
        submenu[i]->setPosition({(int)i*40,45,40,40});
    }
    return true;
}


bool Tab_Button::click_tab(int px,int py)
{
    std::vector<std::shared_ptr<Button>>::iterator menu_Iterator=submenu.begin();
    while(menu_Iterator!=submenu.end())
    {
        if ((*menu_Iterator)->pointinside(px,py))
            {
                (*menu_Iterator)->onclick();
                return true;
            }
        menu_Iterator++;
    }
    return false;
}

bool Tab_Button::onclick()
{
    extern Commander* s;
    s->UserInterface.setsubmenu(shared_from_this());
    return true;
}

bool Tab_Button::draw_tab()
{
    //Draw UI buttons
    std::vector<std::shared_ptr<Button>>::iterator menu_Iterator=submenu.begin();
    while(menu_Iterator!=submenu.end())
    {
        (*menu_Iterator)->draw();
        menu_Iterator++;
    }
    return true;

}

bool Tab_Button::update()
{
    std::vector<std::shared_ptr<Button>>::iterator menu_Iterator=submenu.begin();
    while(menu_Iterator!=submenu.end())
    {
        (*menu_Iterator)->update();
        menu_Iterator++;
    }
    return true;
}