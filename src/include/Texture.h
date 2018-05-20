#ifndef   TEXTURE_H_
#define   TEXTURE_H_
#include "Globals.h"
#include <stdio.h>
#include <string>
class Texture
{
	public:
        SDL_Rect spriteClips[ 4 ];
		//Initializes variables
		Texture();
		//Deallocates memory
		~Texture();
		bool init();
        bool loadMedia();
        bool SetRenderDrawColor();
        void renderPresent();
        void renderClear();
		//Loads image at specified path
		bool loadFromFile( std::string path );

		void close();

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Rect& clip);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
	   	int mWidth;
		int mHeight;
};


bool Texture::init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
            window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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


Texture::Texture()
{
	//Initialize
	texture    = NULL;
	mWidth      = 0;
	mHeight     = 0;
	window     = NULL;
	renderer   = NULL;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile( std::string path )
{
    SDL_Surface* optimizedSurface = NULL;
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );



	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

		//Create texture from surface pixels
		optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void Texture::renderPresent(){
    SDL_RenderPresent(renderer);
}
void Texture::renderClear(){
    SDL_RenderClear(renderer);
}

void Texture::render( int x, int y, SDL_Rect& clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( &clip != NULL )
	{
		renderQuad.w = clip.w*2;
		renderQuad.h = clip.h*2;
	}

	//Render to screen
	SDL_RenderCopy( renderer, texture, &clip, &renderQuad );
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
bool Texture::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( ! Texture::loadFromFile( "rec\Holy_War_Table_1.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite
		this->spriteClips[ 0 ].x = 29;
		this->spriteClips[ 0 ].y = 0;
		this->spriteClips[ 0 ].w = 38;
		this->spriteClips[ 0 ].h = 39;

		this->spriteClips[1].x = 99;
		this->spriteClips[1].y = 0;
		this->spriteClips[1].w = 38;
		this->spriteClips[1].h = 39;

		this->spriteClips[2].x = 169;
		this->spriteClips[2].y = 0;
		this->spriteClips[2].w = 38;
		this->spriteClips[2].h = 39;

		this->spriteClips[3].x = 239;
		this->spriteClips[3].y = 0;
		this->spriteClips[3].w = 38;
		this->spriteClips[3].h = 39;

	}

	return success;
}
bool Texture::SetRenderDrawColor(){
    if(!SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF )){
        printf("RenderDrawColor failed:SDL_ERROR:%s\n",SDL_GetError());
        return false;
    }else{
        return true;
    }

}
void Texture::close()
{
	//Free loaded images
	free();
	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

#endif
