#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "CharacterTexture.h"
//
class Core
{
public:
    Core();
    bool CoreInit();
    void CoreShutdown();
    void CoreMainMenuRun();
    void renderPresent();
    void renderClear();
    void EventHandler(SDL_Event);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GameController* gameController;
    bool quit_program;
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
