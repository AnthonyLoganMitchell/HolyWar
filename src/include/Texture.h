#ifndef   TEXTURE_H_
#define   TEXTURE_H_
#include "Globals.h"
#include <stdio.h>
#include <string>

class Texture
{
	public:
        SDL_Rect spriteClips[4];
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
		int framesCount;

	private:
	   	int mWidth;
		int mHeight;
};


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
    //SDL_Surface* optimizedSurface = NULL;
	//Get rid of preexisting texture
	free();

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
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

		//Create texture from surface pixels
		//printf("DEBUG:1\n");
		//optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );

		/*if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			printf("DEBUG:2");
		}*/

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
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


void Texture::render( int x, int y, SDL_Rect& clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( &clip != NULL )
	{
		renderQuad.w = clip.w*3;
		renderQuad.h = clip.h*3;
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
	if( ! Texture::loadFromFile("rec/Holy_War_Table_1.png"))
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite
		this->spriteClips[ 0 ].x = 31;
		this->spriteClips[ 0 ].y = 1;
		this->spriteClips[ 0 ].w = 37;
		this->spriteClips[ 0 ].h = 38;

		this->spriteClips[1].x = 101;
		this->spriteClips[1].y = 1;
		this->spriteClips[1].w = 37;
		this->spriteClips[1].h = 38;

		this->spriteClips[2].x = 171;
		this->spriteClips[2].y = 1;
		this->spriteClips[2].w = 37;
		this->spriteClips[2].h = 38;

		this->spriteClips[3].x = 241;
		this->spriteClips[3].y = 1;
		this->spriteClips[3].w = 37;
		this->spriteClips[3].h = 38;

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
