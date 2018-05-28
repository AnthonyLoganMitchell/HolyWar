
/* CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   Holy war is my personal programming project and all artwork for this
   Game are my original work.
*/
#include "include/Texture.h"
#include "include/Globals.h"
#include "include/Init.h"



int WinMain( int argc, char* args[] ){
    vector<Texture*> mainTextureSheet;
    vector<Texture*> *TempSheet = &mainTextureSheet;
    bool temp1 =init_Game_Textures(TempSheet);
    bool temp2 =deleteMainTextureSheet(TempSheet);
    Texture *jesus = new Texture(9,"jesus");


	//Start up SDL and create window
	if( !init_SDL_Globals() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia(jesus) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen

                renderClear();

				//Render top left sprite

				if (Tick%8 == 0)
                {
                    render( jesus,320,240,2, jesus->spriteClips[Tick] );
                    Tick++;

				}
				else if(Tick%8==1)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                else if(Tick%8==2)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                else if(Tick%8==3)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                 else if(Tick%8==4)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                 else if(Tick%8==5)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                 else if(Tick%8==6)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                 else if(Tick%8==7)
                {
                    render(jesus,320,240,2, jesus->spriteClips[Tick]);
                    Tick++;

                }
                if (Tick >=8){
                    Tick =0;
                }



				renderPresent();
				//printf("TICK#%d\n",Tick);
                SDL_Delay(100);

			}
		}
	}

	//Free resources and close SDL
	jesus->Free_Texture();
	Close_Globals();

	return 0;
}
