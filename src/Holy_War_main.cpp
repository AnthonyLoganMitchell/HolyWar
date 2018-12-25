
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork
   and high level programming outside of SDL2 framework, openGL,
   and c++ POSIX api standard. Are my original work in progress.
*/
#include "Texture.cpp"
#include "Core.cpp"

int WinMain( int argc, char* args[] )
{
    Core *CoreGame = new Core();
    uint64_t timer1;
    uint64_t timer2;
    //bool temp1 =init_Game_Textures(&mainTextureSheet);
    SDL_Event e;
    //Start up SDL and create window
    if( !CoreGame->CoreInit())
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //While application is running
        while( !CoreGame->quit_program )
        {

        }

    }
    //Free resources and close SDL
    CoreGame->CoreShutdown();
    //bool temp2 =deleteMainTextureSheet(&mainTextureSheet);
    return 0;
}






























/*  //Handle events on queue
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

