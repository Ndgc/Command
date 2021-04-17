#ifndef WEAPON_H
#define WEAPON_H
#include <classes.h>
#include <string>

class weapon
{
    public:
        weapon();
        virtual ~weapon();
        virtual bool shoot(Base_Soldier* user, std::shared_ptr<Base_Soldier> shot_target);
        int get_aimtime(){return aimtime;}
        int needs_reloading(){return false;};
        virtual std::string get_name(){return "Weapon";}
    protected:
        int damage=1;
        int aimtime=1000;
    private:
};

#endif // WEAPON_H
