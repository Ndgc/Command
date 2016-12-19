#ifndef SOLDIER_H
#define SOLDIER_H
#include <SDL.h>
#include <target.h>
#include <list>
#include "shape.h"

class Soldier: public shape
{
    public:
        Soldier(float x, float y,SDL_Renderer* ren);
        virtual ~Soldier();
        bool update(std::list<Target> Enemies);
        bool draw(SDL_Renderer* ren);
        bool moveto(float x, float y);
        bool pointinside(int x,int y);
        SDL_Texture* getIcon(){return Icon;};
    protected:


        float movetox, movetoy;
        std::list<Target>::iterator CurrentTarget;
    private:
};

#endif // SOLDIER_H
