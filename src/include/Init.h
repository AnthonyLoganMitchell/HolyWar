#ifndef INIT_H_
#define INIT_H_
bool init_SDL_Globals()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{

	      if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
           gameController = SDL_GameControllerOpen( 0 );
            if( gameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
        }




		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
            window = SDL_CreateWindow( "HolyWar", 500, 20, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{

			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{

				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}
bool init_Game_Textures(vector<Texture*> *v)
{
   Texture *temp = new Texture(9,"jesus",320,240);
   v->push_back(temp);
   temp = NULL;
   return true;

}
bool deleteMainTextureSheet(vector<Texture*> *v)
{
      delete v;
      return true;

}

bool loadFromFile( std::string path, Texture* t )
{
    //SDL_Surface* optimizedSurface = NULL;
	//Get rid of preexisting texture


	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	//SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    //printf("DEBUG:0\n");
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		//SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0x00, 0x00 ) );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			t->SetWidth(loadedSurface->w);
			t->SetHeight(loadedSurface->h);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	t->texture = newTexture;
	return t->texture != NULL;
}
bool loadMedia(Texture *t)
{
	//Loading success flag
	bool success = true;
   	//Load sprite sheet texture
	if(t->name == "jesus" && !loadFromFile("rec/Holy_War_Jesus.png",t) )
	{

		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{


		//Set top left sprite
		t->spriteClips[ 0 ].x = 2;
		t->spriteClips[ 0 ].y = 0;
		t->spriteClips[ 0 ].w = 38;
		t->spriteClips[ 0 ].h = 40;

		t->spriteClips[1].x = 43;
		t->spriteClips[1].y = 0;
		t->spriteClips[1].w = 38;
		t->spriteClips[1].h = 40;

		t->spriteClips[2].x = 84;
		t->spriteClips[2].y = 0;
		t->spriteClips[2].w = 38;
		t->spriteClips[2].h = 40;

		t->spriteClips[3].x = 125;
		t->spriteClips[3].y = 0;
		t->spriteClips[3].w = 38;
		t->spriteClips[3].h = 40;

		t->spriteClips[4].x = 166;
		t->spriteClips[4].y = 0;
		t->spriteClips[4].w = 38;
		t->spriteClips[4].h = 40;

		t->spriteClips[5].x = 207;
		t->spriteClips[5].y = 0;
		t->spriteClips[5].w = 38;
		t->spriteClips[5].h = 40;

		t->spriteClips[6].x = 248;
		t->spriteClips[6].y = 0;
		t->spriteClips[6].w = 38;
		t->spriteClips[6].h = 40;

		t->spriteClips[7].x = 289;
		t->spriteClips[7].y = 0;
		t->spriteClips[7].w = 38;
		t->spriteClips[7].h = 40;
	}
	return success;
}
void render(Texture *t, int x , int y ,int size , SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, t->GetWidth(), t->GetHeight() };

	//Set clip rendering dimensions
	if( &clip != NULL )
	{
		renderQuad.w = clip->w*size;
		renderQuad.h = clip->h*size;
	}

	//Render to screen
	SDL_RenderCopy( renderer, t->texture, clip, &renderQuad );
}

void Close_Globals()
{
    window        = NULL;
	renderer      = NULL;
	screenSurface = NULL;
	gameController= NULL;
	SDL_GameControllerClose(gameController);
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_FreeSurface(screenSurface);
	IMG_Quit();
	SDL_Quit();

}

#endif // INIT_H
