
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork
   and high level programming outside of SDL2 framework, openGL,
   and c++ POSIX api standard. Are my original work in progress.
*/
#define  SDL_MAIN_HANDLED
#include <SDL.h>
#include "Core.h"
#include <SDL_thread.h>
#include <vector>
SDL_mutex* parse_mutex;

int main( int argc, char* args[] )
{
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
                CoreGame->MainMenuRun(parse_mutex);
                //Initiate Main bootup sequence for main menu.
                std::cout <<"Exiting MainMenuRun()"<<std::endl;
            }
            else if (CoreGame->state->onCharacterSelection && !CoreGame->quit_program)
            {
                CoreGame->CharacterSelectRun(parse_mutex);
                 std::cout <<"Exiting CharacterSelectRun()"<<std::endl;
            }
            else if (CoreGame->state->onLevelSelction && !CoreGame->quit_program)
            {
                //Intiate Level selection screen
                 std::cout <<"Exiting LevelSelction()"<<std::endl;
            }
            else if (CoreGame->state->onRunningMatch && !CoreGame->quit_program)
            {
                //Initiate running match with previously loaded level.
                std::cout <<"Exiting RunningMatch()"<<std::endl;
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
    std::cout << SDL_GetError() << std::endl;
    return 0;
}
