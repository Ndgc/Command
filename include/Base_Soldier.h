#ifndef Base_Soldier_H
#define Base_Soldier_H
#include <SDL.h>
#include <iostream>
enum AI_State
{
    idle,
    movement,
    aim
};

class Base_Soldier
{
    public:

        Base_Soldier();
        virtual ~Base_Soldier();



        virtual bool update(){return true;}
        virtual bool update_idle(){return true;}
        virtual bool update_movement(){return true;}
        virtual bool update_aim(){return true;}

        virtual bool draw(SDL_Renderer* ren);

        unsigned int getid(){return id;}
        int get_evasion() {return skill_evasion;}
        int get_aim() {return skill_aim;}
        int get_movementspeed(){return movementspeed;}
        SDL_Texture* getIcon(){return Icon;}


        bool take_damage(int damage);

        float getX();
        float getY();
        bool pointinside(int x,int y);




        SDL_Texture* Icon;

        virtual bool advance();
        bool isdead(){return dead;}
        bool has_advanced(){return advanced;}


    protected:

        int movementspeed=1;
        float x,y;
        int w,h;
        int skill_evasion = 50;
        int skill_aim=0;
        int health=1;
        unsigned int id;

        bool advanced=false;
        bool dead=false;
        AI_State currentstate;
    private:
};

#endif // Base_Soldier_H
