#include "Weapons\weapon.h"
#include <Commander.h>
#include <iostream>
#include <particle_Bullet_Trail.h>

weapon::weapon()
{
    //ctor
}

weapon::~weapon()
{
    //dtor
}

bool weapon::shoot(Base_Soldier* user, std::shared_ptr<Base_Soldier> shot_target)
{
    extern Commander* s;

    std::cout<<"Shot fired by unit: "<< user->getid() << " at unit " << shot_target->getid() <<" Evasion : "<< shot_target->get_evasion() <<std::endl;

    //draw bullet trail
    std::shared_ptr<particle> ptr;
    ptr= std::make_shared<particle_Bullet_Trail>(user->getX(),user->getY(),shot_target->getX(),shot_target->getY());
    s->particles.push_back(ptr);

    int skillresult;
    int skilldifficulty;

    skillresult=rand()%100+user->get_aim();
    skilldifficulty=shot_target->get_evasion();

    if (skillresult>skilldifficulty)
    {
        std::cout<<"Result :" << skillresult<<" HIT"<<std::endl;
        shot_target->take_damage(damage,user);
        return true;
    }
    else
    {
        std::cout<<"Result :" << skillresult<<" MISS"<<std::endl;
        return false;
    }


}
