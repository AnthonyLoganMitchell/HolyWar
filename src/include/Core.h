#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "Texture.h"
#include "MenuTexture.h"
#include "Interaction.h"
#include "ThreadData.h"

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
    template<class T>
    void ParseEvents(ThreadData* data,T* Modify);
    static int EventHandler(void*);
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit_program;
    int Tick;
    bool OnMainMenu;
    bool onLevelSelction;
    bool onCharacterSelection;
    bool onRunningMatch;
    ThreadData *data;
    SDL_mutex* parse_mutex;

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};
#endif
