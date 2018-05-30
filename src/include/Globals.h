#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
using namespace std;
        const int SCREEN_WIDTH = 700;
        const int SCREEN_HEIGHT = 700;
        bool quit_program = false;
        int xPos =0;                    //<<-----
        int yPos =0;                    //<<-----
        int Tick=0;

        //The actual hardware texture
		//Image dimensions
		SDL_Window* window;
        //The window renderer
        SDL_Renderer* renderer;
        //Scene sprites
        SDL_Surface* screenSurface;

        SDL_GameController* gameController;

        void renderPresent(){
            SDL_RenderPresent(renderer);
        }
        void renderClear(){
            SDL_RenderClear(renderer);
        }



#endif
