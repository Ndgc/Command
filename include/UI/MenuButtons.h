#ifndef MENUBUTTONS_H
#define MENUBUTTONS_H
#include "Button.h"


class ButtonCreateRifle : public Button
{
    public:
        ButtonCreateRifle();
        virtual ~ButtonCreateRifle();
        bool onclick();
    protected:
        void createIcon(SDL_Renderer* ren);
    private:
};

class ButtonCreateShotgun : public Button
{
    public:
        ButtonCreateShotgun();
        virtual ~ButtonCreateShotgun();
        bool onclick();
    protected:
        void createIcon(SDL_Renderer* ren);
    private:
};

class ButtonForceWave : public Button
{
    public:
        ButtonForceWave();
        virtual ~ButtonForceWave();
        bool onclick();
    protected:
        void createIcon(SDL_Renderer* ren);
    private:
};

#endif // MENUBUTTONS_H
