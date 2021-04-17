#include "particle.h"
#include <iostream>
particle::particle(int lifetime)
{
    //ctor
    this->lifetime=lifetime;
}

particle::~particle()
{
    //dtor
}

bool particle::draw()
{
    //draw whatever it is here
    return true;
}

bool particle::isexpired()
{
    return (lifetime<=0);
}
