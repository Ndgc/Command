#ifndef PARTICLE_BULLET_TRAIL_H
#define PARTICLE_BULLET_TRAIL_H
#include <Classes.h>

class particle_Bullet_Trail : public particle
{
    public:
        particle_Bullet_Trail(int x1,int y1,int x2,int y2,int lifetime=150);
        virtual ~particle_Bullet_Trail();
        bool draw();
    protected:
        int x1, y1, x2, y2;
        int starting_lifetime;
    private:
};

#endif // PARTICLE_BULLET_TRAIL_H
