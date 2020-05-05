/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
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

    void RunMainMenu(SDL_mutex*);
    void RunCharacterSelect(SDL_mutex*);
    void RunLevelSelect(SDL_mutex*);
    void RunMatch(SDL_mutex*);
    void RunCharacters(int,int,int);
    void RunCollisionModule(int,int, Level*);
    void SetInitialCharacterPositions(Level*);

    bool CursorCollisionDetect(PlayerCursor*,SDL_Rect*);
    bool CollisionObjectCharacter(GeneralTexture* A, int, CharacterObject* B, int);
    static int EventHandler(void*);
    std::vector<CharacterPortrait*> *InitCharacterPortraits(SDL_Renderer*);
    std::vector<LevelPortrait*> *InitLevelPortraits(SDL_Renderer*);


    SDL_Window* window;
    SDL_Renderer* renderer;
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
