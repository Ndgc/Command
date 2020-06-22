#ifndef TARGET_H
#define TARGET_H
#include <SDL.h>
#include <iostream>
#include "Base_Soldier.h"

class Target: public Base_Soldier
{
    public:
        Target(unsigned int id,int x, int y, SDL_Renderer *ren);
        virtual ~Target();
        void createIcon(SDL_Renderer *ren);
        bool update();
        bool update_movement();
    protected:


    private:

};

#endif // TARGET_H
