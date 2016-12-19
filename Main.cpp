//Main: contains game loop, init and exit.
//Lots of brief variable names.

//Using Libraries
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
//Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS=60;

//Game Window
SDL_Window* win= NULL;

//Window Renderer
SDL_Renderer* ren = NULL;


//Use personal headers
#include <timer.h>
#include <State.h>
#include <Commander.h>

//The Game State itself
State* s;



int main( int argc, char* args[] )
{
    //seed random numbers because why not.
    srand(time(NULL));

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		win = SDL_CreateWindow( "SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( win == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
            //create renderer, and paint it a funny colour, so later failure states don't just leave a black screen.
            ren= SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(ren,0,255,100,0);
            SDL_RenderClear(ren);
            SDL_RenderPresent(ren);
        }
	}
	//Create Game loop variables

	//Game state. Commander is the actual game.
	s=new Commander(ren);
	//this exits the game, figure it's easier to make it something i can't easily code around.
    bool quit=false;
    SDL_Event e;
    //frame timer, limits frames
    timer t;
    t.Setperiod(1000/FPS);

    //actual loop
    while (!quit)
    {
        //start frame clock.
        t.StartTimer();

        while (SDL_PollEvent(&e))
        {
            //if time to go, get ready to leave the game loop
            if (e.type==SDL_QUIT)
                quit=true;
            s->event(e);
        }
        s->update();
        s->draw(ren);
        if (t.GetRemaining()>0)
        {
            SDL_Delay(t.GetRemaining());
        }

    }
    //Destroy state
    delete s;

	//Destroy window
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	//Quit SDL
	SDL_Quit();

	return 0;
}
