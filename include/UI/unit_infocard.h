#ifndef unit_infocard_H
#define unit_infocard_H
#include <SDL.h>
#include <SDL_ttf.h>


class unit_infocard
{
    public:
    unit_infocard();
    ~unit_infocard();
    bool draw();
    bool update();
    protected:
    int width=400;
    int height=200;
    TTF_Font *font;
    

};

#endif // unit_infocard_H