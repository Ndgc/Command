#include "Weapons\shotgun.h"


#include <classes.h>

#include <Commander.h>
#include <particle_Bullet_Trail.h>
#include <functions\geometry.h>

#include <memory>
#include <math.h>

shotgun::shotgun()
{
    //ctor
}

shotgun::~shotgun()
{
    //dtor
}

bool shotgun::shoot(Base_Soldier* user, std::shared_ptr<Base_Soldier> shot_target)
{
    extern Commander* s;

    std::cout<<"Shotgun fired by unit: "<< user->getid() << " at unit " << shot_target->getid() <<" Evasion : "<< shot_target->get_evasion() <<std::endl;

    int x_diff = user->getX()-shot_target->getX();
    int y_diff = user->getY()-shot_target->getY();
    float angle = std::atan2(y_diff,x_diff);

    float angle_range=0.4;
    if(user->get_aim()<=100)
    {
        angle_range=0.9-0.5*user->get_aim()/100.0;  
    }
    else
    {
        angle_range=0.4;
    }

    float random_angle;
    int x,y;


    int length=170;
    int pellet_count=6;
    std::shared_ptr<particle> ptr;
    for(int i=0;i<pellet_count;i++)
    {
        random_angle=angle+ (((float)rand()/RAND_MAX)*2*angle_range)-angle_range;
        x=user->getX()-length*std::cos(random_angle);
        y=user->getY()-length*std::sin(random_angle);
        //draw bullet trails
        ptr= std::make_shared<particle_Bullet_Trail>(user->getX(),user->getY(),x,y);
        s->particles.push_back(ptr);


        std::map<unsigned int,std::shared_ptr<Target>>::iterator enemy;
        enemy=s->enemies.begin();
        while (enemy!=s->enemies.end())
        {
            if (get_line_square_intersection(user->getX(),user->getY(),x,y,enemy->second->getX(),enemy->second->getY(),20,20))
            {
                int skillresult;
                int skilldifficulty;

                skillresult=rand()%100+user->get_aim();
                skilldifficulty=enemy->second->get_evasion();

                if (skillresult>skilldifficulty)
                {
                    std::cout<<"Result :" << skillresult<<" HIT unit "<<enemy->second->getid()<<std::endl;
                    enemy->second->take_damage(damage,user);
                }
                else
                {
                    std::cout<<"Result :" << skillresult<<" MISS unit "<<enemy->second->getid()<<std::endl;
                }
            }
            enemy++;
        }
    }


    return true;


}
