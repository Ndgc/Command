#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Weapons\weapon.h>


class shotgun : public weapon
{
    public:
        shotgun();
        virtual ~shotgun();
        bool shoot(Base_Soldier* user, std::shared_ptr<Base_Soldier> shot_target);
        virtual std::string get_name(){return "Shotgun";}
    protected:

    private:
};

#endif // SHOTGUN_H
