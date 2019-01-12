
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork
   and high level programming outside of SDL2 framework, openGL,
   and c++ POSIX api standard. Are my original work in progress.
*/
#include "Core.h"

int WinMain( int argc, char* args[] )
{
    Core *CoreGame = new Core();
    SDL_Event* e;
    //Start up SDL and create window
    if( !CoreGame->CoreInit())
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        CoreGame->OnMainMenu = true;
        //While application is running
        SDL_SetRenderDrawColor(CoreGame->renderer, 0x00, 0x00, 0x00, 0x00);
        CoreGame->renderClear();
        CoreGame->renderPresent();
        while( !CoreGame->quit_program )
        {
            if ( CoreGame->OnMainMenu == true)
            {
                CoreGame->CoreMainMenuRun(e);
                CoreGame->OnMainMenu = false;
                CoreGame->quit_program = true;
                //Initiate Main bootup sequence for main menu.
            }
            else if (CoreGame->onLevelSelction == true)
            {
                //Intiate Level selection screen
            }
            else if (CoreGame->onRunningMatch == true)
            {
                //Initiate running match with previously loaded level.
            }
        }
    }
    //Free resources and close SDL
    CoreGame->CoreShutdown();

    return 0;
}
