#ifndef game_infocard_H
#define game_infocard_H
#include <SDL.h>
#include <SDL_ttf.h>


class game_infocard
{
    public:
    game_infocard();
    ~game_infocard();
    bool draw();
    bool update();
    protected:
    int width=400;
    int height=200;
    TTF_Font *font;
    

};

#endif // game_infocard_H