#ifndef CORE_H
#define CORE_H
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "Texture.h"
#include "GeneralTexture.h"
#include "Interaction.h"
#include "ThreadData.h"
#include "MenuButton.h"
#include "State.h"
#include "PlayerObject.h"
#include <map>
#include <vector>
#include "CharacterPortrait.h"
#include <stdlib.h>
#include "PlayerCursor.h"
#include "LevelPortrait.h"
//
class Core
{
public:
    Core();
    bool CoreInit();
    void CoreShutdown();
    void renderPresent();
    void renderClear();
    void MainMenuRun(SDL_mutex*);
    void CharacterSelectRun(SDL_mutex*);
    void LevelSelectRun(SDL_mutex*);
    template<class T>
    void ParseEvents(ThreadData* data,T* Modify,SDL_mutex*);
    bool CollisionDetect(PlayerCursor*,SDL_Rect*);
    static int EventHandler(void*);
    std::vector<CharacterPortrait*> *InitCharacterPortraits(SDL_Renderer*);
    std::vector<LevelPortrait*> *InitLevelPortraits(SDL_Renderer*);


    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit_program;
    int tick;
    ThreadData *data;
    SDL_mutex* parse_mutex;
    std::vector<PlayerObject*>* players;
    //Game State
    //////////////
    State* state;//
    //////////////

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};
#endif
