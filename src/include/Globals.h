#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
        const int SCREEN_WIDTH = 700;
        const int SCREEN_HEIGHT = 700;
        //The actual hardware texture
		//Image dimensions
		SDL_Window* window;
        //The window renderer
        SDL_Renderer* renderer;
        //Scene sprites
        SDL_Surface* screenSurface;

        void renderPresent(){
            SDL_RenderPresent(renderer);
        }
        void renderClear(){
            SDL_RenderClear(renderer);
        }



#endif
