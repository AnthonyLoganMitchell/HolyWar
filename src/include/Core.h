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
#define  SDL_MAIN_HANDLED
#include <vector>
class ThreadData;
class State;
class SDL_mutex;
class SDL_Window;
class SDL_Renderer;
class Projectile;
class PlayerObject;
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


    SDL_Window* window;
    SDL_Renderer* renderer;
    int tick;
    ThreadData *data;
    SDL_mutex* parse_mutex;
    std::vector<PlayerObject*>* players;
    std::vector<Projectile*>* Projectiles;
    //Game State
    //////////////
    State* state;//
    //////////////

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};
#endif
