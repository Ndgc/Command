#ifndef COMMANDER_H
#define COMMANDER_H

#include <State.h>
#include <Soldiers\Allied_Soldier.h>
#include <Soldiers\Target.h>
#include <WaveController.h>
#include <UI\gui.h>
#include <UI\Button.h>
#include <particle.h>
#include <window.h>
#include <UI\unit_infocard.h>
#include <UI\game_infocard.h>

#include <map>
#include <list>
#include <memory>

#include "SDL.h"
#include "SDL_ttf.h"

class Commander : public State
{
    public:
        Commander(SDL_Renderer* ren);
        virtual ~Commander();
        bool postinit();

        bool update();
        bool event(SDL_Event e);
        bool draw(SDL_Renderer* r);
        unsigned int create_enemy(std::shared_ptr<Target> new_enemy);
        unsigned int create_ally(std::shared_ptr<Allied_Soldier> new_ally);

        window game_window;
        WaveController WaveControl;
        std::map<unsigned int,std::shared_ptr<Target>> enemies;
        std::map<unsigned int,std::shared_ptr<Allied_Soldier>> units;
        std::list<std::shared_ptr<particle>> particles;
        unsigned int SelUnit;

        SDL_Renderer *getRenderer(){return game_window.get_renderer();}
        unsigned int getnextid(){return nextid;}
        int getkills(){return kills;}

        int get_resource_points(){return resource_points;}
        int give_resource_points(int award){resource_points+=award;return true;}
        int spend_resource_points(int cost){resource_points-=cost;return true;}

        int get_lives_lost(){return lives_lost;}
        int lose_lives(int num){lives_lost+=num;return true;}
        int gain_lives (int num){lives_lost=(num>lives_lost)?0:(lives_lost-num);return true;}

        bool is_gameover(){return gameover;}
        
        int get_battlefield_width(){return battlefield_width;}
        int get_battlefield_height(){return battlefield_height;}

        GUI UserInterface;
    protected:
        int battlefield_width=400;
        int battlefield_height=600;
        
        bool gameover;
        
        unit_infocard unit_info_card;
        game_infocard game_info_card;

        int kills;
        int resource_points;
        int lives_lost;
        unsigned int nextid;
    private:
};

#endif // COMMANDER_H
