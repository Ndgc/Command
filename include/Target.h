#ifndef TARGET_H
#define TARGET_H
#include <SDL.h>
#include <iostream>
#include "shape.h"

class Target : public shape
{
    public:
        Target(int x, int y, SDL_Renderer *ren);
        virtual ~Target();
        bool update();
        float getX();
        float getY();
    protected:

    private:

};

#endif // TARGET_H
