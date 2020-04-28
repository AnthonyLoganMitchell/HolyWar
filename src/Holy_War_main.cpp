/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/////
#define  SDL_MAIN_HANDLED
#include <SDL.h>
#include "Core.h"
#include <SDL_thread.h>
#include <vector>
SDL_mutex* parse_mutex;

int main( int argc, char* args[] )
{
    char pause;
    parse_mutex = SDL_CreateMutex();
    Core *CoreGame = new Core();
    CoreGame->data->parse_mutex = parse_mutex;
    //Start up SDL and create window
    if( !CoreGame->CoreInit())
    {
        std::cout<<"Failed to initialize!"<<std::endl;
    }

    else
    {
        SDL_Thread* EventThread = SDL_CreateThread(CoreGame->EventHandler, "EventThread", (void*)CoreGame->data);
        //While application is running
        SDL_SetRenderDrawColor(CoreGame->renderer, 0x00, 0x00, 0x00, 0x00);
        CoreGame->renderClear();
        CoreGame->renderPresent();
        while( !CoreGame->quit_program )
        {
            if ( CoreGame->state->onMainMenuStart&& !CoreGame->quit_program)
            {
                CoreGame->RunMainMenu(parse_mutex);
                //Initiate Main bootup sequence for main menu.
                std::cout <<"Exiting MainMenuRun()"<<std::endl;
            }
            else if (CoreGame->state->onCharacterSelection && !CoreGame->quit_program)
            {
                CoreGame->RunCharacterSelect(parse_mutex);
                 std::cout <<"Exiting CharacterSelectRun()"<<std::endl;
            }
            else if (CoreGame->state->onLevelSelection && !CoreGame->quit_program)
            {
                //Intiate Level selection screen
                 CoreGame->RunLevelSelect(parse_mutex);
                 std::cout <<"Exiting LevelSelction()"<<std::endl;
                 //CoreGame->quit_program= true;
            }
            else if (CoreGame->state->onRunningMatch && !CoreGame->quit_program)
            {
                //Initiate running match with previously loaded level.
                std::cout <<"Exiting RunningMatch()"<<std::endl;
                CoreGame->RunMatch(parse_mutex);
                CoreGame->quit_program = true;
            }
        }
        std::cout <<"PreThread shutdown."<<std::endl;
        SDL_DetachThread(EventThread);
        SDL_WaitThread(EventThread, NULL );
        std::cout <<"PostThread shutdown."<<std::endl;
    }
    //
    //Free resources and close SDL
    std::cout <<"PreCore shutdown."<<std::endl;
    CoreGame->CoreShutdown();
    std::cout <<"PostCore shutdown."<<std::endl;
    std::cin >> pause;
    return 0;
}
