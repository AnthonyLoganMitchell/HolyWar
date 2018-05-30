
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork for this
   Game are my original works.
*/
#include "include/Texture.h"
#include "include/Globals.h"
#include "include/Init.h"



int WinMain( int argc, char* args[] ){
    vector<Texture*> mainTextureSheet;
    bool temp1 =init_Game_Textures(&mainTextureSheet);
    int xPos =0;
    int yPos =0;

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



                //Main loop flag


                //Event handler
                SDL_Event e;


                //While application is running
                while( !quit_program )
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ))
                    {
                       //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit_program = true;
                        }
                        else if(e.type == SDL_CONTROLLERBUTTONDOWN)
                        {

                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_DOWN) ==1 )
                            {
                                yPos=-3;
                            }

                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_UP) ==1)
                            {
                                yPos=3;
                            }

                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT) ==1)
                            {
                                xPos=-3;
                            }

                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ==1)
                            {
                                xPos=3;
                            }



                        }// BUTTONDOWN
                        else if(e.type == SDL_CONTROLLERBUTTONUP)
                        {


                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_DOWN) ==0 )
                            {
                                yPos=0;
                            }
                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_UP) ==0)
                            {
                                yPos=0;
                            }
                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT) ==0)
                            {
                                xPos=0;
                            }
                            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ==0)
                            {
                                xPos=0;
                            }

                        }

                    }

                    //Clear screen

                    renderClear();


                    render( mainTextureSheet[0],mainTextureSheet[0]->xposition+=xPos,(mainTextureSheet[0]->yposition-=yPos),3, &mainTextureSheet[0]->spriteClips[mainTextureSheet[0]->GetFrameCount()] );
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
	//jesus->Free_Texture();
	Close_Globals();
    bool temp2 =deleteMainTextureSheet(&mainTextureSheet);         ////<<<<problem
	return 0;
}

