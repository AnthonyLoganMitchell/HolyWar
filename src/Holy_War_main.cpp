
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork
   and high level programming outside of SDL2 framework, openGL,
   and c++ POSIX api standard. Are my original work in progress.
*/
#include "Core.h"
#include <SDL_thread.h>
#include <vector>

int WinMain( int argc, char* args[] )
{
    Core *CoreGame = new Core();
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
            if ( CoreGame->state->onMainMenuStart == true && !CoreGame->quit_program)
            {
                CoreGame->MainMenuRun();
                //Initiate Main bootup sequence for main menu.
            }
            else if (CoreGame->state->onCharacterSelection && !CoreGame->quit_program)
            {
                //CoreGame->CharacterSelectRun();
                CoreGame->quit_program = true;
            }
            else if (CoreGame->state->onLevelSelction && !CoreGame->quit_program)
            {
                //Intiate Level selection screen
            }
            else if (CoreGame->state->onRunningMatch && !CoreGame->quit_program)
            {
                //Initiate running match with previously loaded level.
            }
        }
        //SDL_WaitThread(EventThread, NULL );
    }
    //Free resources and close SDL
    CoreGame->CoreShutdown();
    return 0;
}
