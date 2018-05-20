/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings

#include "include/Texture.h"
#include <unistd.h>
#include "include/Globals.h"

//#include "include/Globals.h"


//
//Screen dimension constants



int WinMain( int argc, char* args[] ){

    Texture *temp = new Texture();
    int Tick=0;
	//Start up SDL and create window
	if( !temp->init() )
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



				//Render top left sprite
				if (Tick%4 == 0)
                {
				temp->render( 320,240, temp->spriteClips[0] );
                Tick++;
                printf("DEBUG#1\n");
				}
				else if(Tick%4==1)
                {
                temp->render(320,240, temp->spriteClips[1]);
                Tick++;
                printf("DEBUG#2\n");
                }
                else if(Tick%4==2)
                {
                temp->render(320,240, temp->spriteClips[2]);
                Tick++;
                printf("DEBUG#3\n");
                }
                else if(Tick%4==3)
                {
                temp->render(320,240, temp->spriteClips[3]);
                Tick++;
                printf("DEBUG#4\n");
                }

                if (Tick >=20)
                {
                    Tick=0;
                }



				//Update screen320,240

				temp->renderPresent();
                temp->renderClear();
				Tick++;
               // SDL_Delay(500);

			}
		}
	}

	//Free resources and close SDL
	temp->close();

	return 0;
}
