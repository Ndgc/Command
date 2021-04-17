#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>

enum class viewport
{
    game,
    menu,
    unit_card,
    game_card
};

class window
{
    public:
        window();
        virtual ~window();
        
        float get_multiplier(){return multiplier;}
        SDL_Renderer* get_renderer(){return ren;}
        bool set_renderer(SDL_Renderer* renderer){ren=renderer;return true;}
        bool set_viewport (viewport selection);
        SDL_Rect get_viewport(viewport selection){return viewports[selection];}
        bool pointinside(viewport selcted_view,int Px, int Py);
    protected:
        std::map<viewport,SDL_Rect> viewports;
        float multiplier;
        SDL_Window* win;
        SDL_Renderer* ren;

        int w,h;
    private:
};
#endif // WINDOW_H