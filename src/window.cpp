#include "window.h"

window::window()
{
    multiplier=1;

    viewports.emplace(viewport::game,SDL_Rect{0,0,400,600});
    
    viewports.emplace(viewport::unit_card,SDL_Rect{400,0,400,200});
    viewports.emplace(viewport::game_card,SDL_Rect{400,200,400,200});

    viewports.emplace(viewport::menu,SDL_Rect{400,400,400,200});
}

window::~window()
{

}

bool window::set_viewport(viewport selection)
{
    return SDL_RenderSetViewport(ren,&(viewports[selection]));
}

bool window::pointinside(viewport selected_view,int Px, int Py)
{
SDL_Rect R=viewports[selected_view];
if (Px>R.x-R.w && Px<R.x+R.w)
    if (Py>R.y-R.h && Py<R.y+R.h)
        return true;

return false;
}