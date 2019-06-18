#ifndef CORE_H
#define CORE_H
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "Texture.h"
#include "MenuTexture.h"
#include "Interaction.h"
#include "ThreadData.h"
#include "MenuButton.h"
#include "State.h"

//
class Core
{
public:
    Core();
    bool CoreInit(SDL_GameController* controllers[]);
    void CoreShutdown();
    void renderPresent();
    void renderClear();
    void MainMenuRun();
    void CharacterSelectRun();
    template<class T>
    void ParseEvents(ThreadData* data,T* Modify);
    static int EventHandler(void*);


    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit_program;
    int tick;
    ThreadData *data;
    SDL_mutex* parse_mutex;
    //Game State
    //////////////
    State* state;//
    //////////////

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};
#endif
