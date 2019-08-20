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
#include "CharacterObject.h"
#include "Level.h"
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
    void MatchRun(SDL_mutex*);
    void RunContextSimulation(int,int,int);
    void RunCollisionModule(int,int, Level*);
    void ParseEvents(ThreadData* data,SDL_mutex*);
    bool CursorCollisionDetect(PlayerCursor*,SDL_Rect*);
    bool CollisionObjectCharacter(GeneralTexture* A, int, CharacterObject* B, int);
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
