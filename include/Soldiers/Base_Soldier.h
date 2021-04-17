#ifndef Base_Soldier_H
#define Base_Soldier_H
#include <SDL.h>
#include <iostream>
#include <memory>
#include <string>

#include <Weapons\weapon.h>
enum class AI_State
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

        bool postinit(int key);


        virtual void createIcon(){;}

        virtual bool update(){return true;}
        virtual bool update_idle(){return true;}
        virtual bool update_movement(){return true;}
        virtual bool update_aim(){return true;}

        virtual bool draw(SDL_Renderer* ren);

        unsigned int getid(){return id;}
        int get_evasion() {return skill_evasion;}
        int get_aim() {return skill_aim;}
        float get_movementspeed(){return movementspeed;}
        SDL_Texture* getIcon(){return Icon;}

        std::string name ="John Smith";

        bool take_damage(int damage);
        bool take_damage(int damage,Base_Soldier* source);
        virtual bool on_kill(Base_Soldier* dead_unit);

        float getX();
        float getY();
        int getW(){return w;}
        int getH(){return h;}
        bool pointinside(int x,int y);

        int get_health(){return health;}
        int get_max_health(){return max_health;}



        SDL_Texture* Icon;

        virtual bool advance();
        bool isdead(){return dead;}
        bool has_advanced(){return advanced;}
        std::shared_ptr<weapon> unit_weapon;

    protected:

        float movementspeed=0.5;
        float x,y;
        int w,h;
        int skill_evasion = 50;
        int skill_aim=0;
        int health=1;
        int max_health=100;
        unsigned int id;

        bool advanced=false;
        bool dead=false;
        AI_State currentstate;
    private:
};

#endif // Base_Soldier_H
