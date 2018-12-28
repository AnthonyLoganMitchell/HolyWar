
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork
   and high level programming outside of SDL2 framework, openGL,
   and c++ POSIX api standard. Are my original work in progress.
*/
#include "Core.h"

int WinMain( int argc, char* args[] )
{
    Core *CoreGame = new Core();
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






























/*  //Handle events on queue
             uint64_t timer1; // These originally werent in this block
             uint64_t timer2; // These originally werent in this block
             EventHandler(e);
             //Clear screen
             renderClear();
             render( mainTextureSheet[0],mainTextureSheet[0]->xposition+=xPos,(mainTextureSheet[0]->yposition-=yPos),2, &mainTextureSheet[0]->spriteClips[mainTextureSheet[0]->GetFrameCount()] );
             mainTextureSheet[0]->TickFrameCount();


                if(mainTextureSheet[0]->GetFrameCount() == mainTextureSheet[0]->GetSpriteCount()){

                    mainTextureSheet[0]->SetFrameCount(0);
                }

                renderPresent();
                //cout<<"Xpos:"<<xPos<<" "<<"Ypos:"<<yPos<<endl;
                timer1 = SDL_GetPerformanceCounter();
                SDL_Delay(70);
                timer2 = SDL_GetPerformanceCounter();
                cout<<(timer2-timer1)/(double )SDL_GetPerformanceFrequency()<<endl;*/

