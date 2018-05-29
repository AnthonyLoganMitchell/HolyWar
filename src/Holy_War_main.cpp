
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork for this
   Game are my original work.
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
                int count=0;

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
                           count++;
                           cout<<"button pushed# "<<count<<endl;

                        }
                    }

                    //Clear screen

                    renderClear();


                    render( mainTextureSheet[0],320,240,6, &mainTextureSheet[0]->spriteClips[mainTextureSheet[0]->GetFrameCount()] );
                    mainTextureSheet[0]->TickFrameCount();


                    if(mainTextureSheet[0]->GetFrameCount() == mainTextureSheet[0]->GetSpriteCount())
                    {
                        //cout<<mainTextureSheet[0]->GetFrameCount()<<": "<<mainTextureSheet[0]->GetSpriteCount()<<endl;
                        mainTextureSheet[0]->SetFrameCount(0);
                    }

                    renderPresent();
                    //cout<<"Xpos:"<<xPos<<" "<<"Ypos:"<<yPos<<endl;
                    //printf("TICK#%d\n",Tick);
                    SDL_Delay(100);


                }




	}

	//Free resources and close SDL
	//jesus->Free_Texture();
	Close_Globals();
    bool temp2 =deleteMainTextureSheet(&mainTextureSheet);         ////<<<<problem
	return 0;
}

