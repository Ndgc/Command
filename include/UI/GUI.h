#ifndef GUI_H
#define GUI_H
#include "SDL_ttf.h"
#include <list>
#include <vector>
#include "UI\Tab_Button.h"
#include <UI\button.h>
#include <memory>

class GUI
{
    public:
        GUI();
        virtual ~GUI();
        bool postinit();

        bool update();
        bool draw();
        bool event(SDL_Event e);
        bool addButton(std::shared_ptr<Button> new_button);
        bool sortButtons();
        bool setsubmenu(std::shared_ptr<Tab_Button> ptr){submenuptr=ptr;return true;}
    protected:
        std::shared_ptr<Tab_Button> submenuptr;
        std::vector<std::shared_ptr<Button>> menu;
        TTF_Font *font;
        TTF_Font *large_font;
    private:
};

#endif // GUI_H
