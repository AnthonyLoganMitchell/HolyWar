
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork for this
   Game are my original works.
*/
#include "include/Texture.h"
#include "include/Globals.h"
#include "include/Init.h"
#include "include/Event.h"
vector<Texture*> mainTextureSheet;



int WinMain( int argc, char* args[] ){

    bool temp1 =init_Game_Textures(&mainTextureSheet);
    SDL_Event e;
	//Start up SDL and create window
	if( !init_SDL_Globals() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		//Load media
		for (int i=0; i< mainTextureSheet.size();i++) //for
        {
            ;
            if( !loadMedia(mainTextureSheet[i]) )
            {
                printf( "Failed to load media!\n" );
                exit(1);
            }

        } //for


                //While application is running
                while( !quit_program )
                {
                    //Handle events on queue

                    EventHandler(e);
                    //Clear screen

                    renderClear();


                    render( mainTextureSheet[0],mainTextureSheet[0]->xposition+=xPos,(mainTextureSheet[0]->yposition-=yPos),2, &mainTextureSheet[0]->spriteClips[mainTextureSheet[0]->GetFrameCount()] );
                    mainTextureSheet[0]->TickFrameCount();


                    if(mainTextureSheet[0]->GetFrameCount() == mainTextureSheet[0]->GetSpriteCount())
                    {

                        mainTextureSheet[0]->SetFrameCount(0);
                    }

                    renderPresent();
                    cout<<"Xpos:"<<xPos<<" "<<"Ypos:"<<yPos<<endl;

                    SDL_Delay(80);


                }




	}

	//Free resources and close SDL
	Close_Globals();
    bool temp2 =deleteMainTextureSheet(&mainTextureSheet);
	return 0;
}

