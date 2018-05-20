#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
        const int SCREEN_WIDTH = 1360;
        const int SCREEN_HEIGHT = 768;
        //The actual hardware texture
		SDL_Texture* texture;
		//Image dimensions
		SDL_Window* window;
        //The window renderer
        SDL_Renderer* renderer;
        //Scene sprites
        SDL_Surface* screenSurface;


#endif
