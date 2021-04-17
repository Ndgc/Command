#ifndef PARTICLE_H
#define PARTICLE_H


class particle
{
    public:
        particle(int lifetime);
        virtual ~particle();
        bool update(){lifetime--;return true;}
        virtual bool draw();
        bool isexpired();
    protected:
        int lifetime;
    private:
};

#endif // PARTICLE_H
