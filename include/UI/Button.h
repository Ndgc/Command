#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>


class Button
{
    public:
        Button();
        virtual ~Button();
        bool postinit(int index);

        virtual bool update();
        virtual bool draw();
        virtual bool onclick();
        bool pointinside(int x,int y);

        SDL_Texture* getIcon() { return Icon; }
        void SetIcon(SDL_Texture* val) { Icon = val; }
        SDL_Rect getPosition(){return Position;}
        bool setPosition(SDL_Rect pos){Position=pos;return true;}

    protected:
        int id;
        virtual void createIcon(SDL_Renderer* ren);
        SDL_Texture* Icon;
        SDL_Rect Position;
    private:

};

#endif // BUTTON_H