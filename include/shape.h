#ifndef SHAPE_H
#define SHAPE_H
#include <SDL.h>


class shape
{
    public:
        shape();
        virtual ~shape();
        virtual bool draw(SDL_Renderer* ren);
    protected:
        SDL_Texture* Icon;
        float x,y;
    private:
};

#endif // SHAPE_H
