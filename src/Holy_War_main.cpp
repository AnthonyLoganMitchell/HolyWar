#include "include/Texture.h"
#include "include/Globals.h"
#include "include/Init.h"

int WinMain( int argc, char* args[] ){

    Texture *temp = new Texture();
    int Tick=0;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !temp->loadMedia() )
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
				if (Tick%4 == 0)
                {
                    temp->render( 320,240, temp->spriteClips[Tick] );
                    Tick++;

				}
				else if(Tick%4==1)
                {
                    temp->render(320,240, temp->spriteClips[Tick]);
                    Tick++;

                }
                else if(Tick%4==2)
                {
                    temp->render(320,240, temp->spriteClips[Tick]);
                    Tick++;

                }
                else if(Tick%4==3)
                {
                    temp->render(320,240, temp->spriteClips[Tick]);
                    Tick++;

                }
                if (Tick >=4){
                    Tick =0;
                }

				//Update screen320,240

				renderPresent();
                SDL_Delay(100);

			}
		}
	}

	//Free resources and close SDL
	temp->close();

	return 0;
}
