#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
//
class Core
{
public:
    Core();
    void CoreShutdown();
    void renderPresent();
    void renderClear();
    bool CoreInit();
    void EventHandler(SDL_Event);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GameController* gameController;
    bool quit_program;
    int xPos;
    int yPos;
    int Tick;
    bool OnMainMenu;
    bool onLevelSelction;
    bool onCharacterSelection;
    bool onRunningMatch;

private:
    const int SCREEN_WIDTH = 700;
    const int SCREEN_HEIGHT = 700;
};




#endif
