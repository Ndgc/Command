#ifndef TARGET_H
#define TARGET_H
#include <SDL.h>
#include <iostream>
#include "Base_Soldier.h"

class Target: public Base_Soldier
{
    public:
        Target(int x, int y);
        virtual ~Target();
        void createIcon();
        bool update();
        bool update_movement();
        bool advance();
    protected:


    private:

};

#endif // TARGET_H
