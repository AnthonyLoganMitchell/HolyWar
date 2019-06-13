#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "Texture.h"
#include "MenuTexture.h"
//
class Core
{
public:
    Core();
    bool CoreInit(SDL_GameController* controllers[]);
    void CoreShutdown();
    void renderPresent();
    void renderClear();
    void CoreMainMenuRun();


    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit_program;
    int Tick;
    bool OnMainMenu;
    bool onLevelSelction;
    bool onCharacterSelection;
    bool onRunningMatch;

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};
#endif
