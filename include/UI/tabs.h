#ifndef TAB_H
#define TABS_H
#include <SDL.h>
#include "UI\Tab_Button.h"
#include "Button.h"

class Tab_ButtonCommand : public Tab_Button
{
    public:
        Tab_ButtonCommand();
        virtual ~Tab_ButtonCommand();
    protected:
        void createIcon(SDL_Renderer* ren);
    private:
};

class Tab_ButtonSoldiers : public Tab_Button
{
    public:
        Tab_ButtonSoldiers();
        virtual ~Tab_ButtonSoldiers();
    protected:
        void createIcon(SDL_Renderer* ren);
    private:
};


#endif // TABS_H