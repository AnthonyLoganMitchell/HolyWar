#ifndef   TEXTURE_H_
#define   TEXTURE_H_
#include "Globals.h"
#include <stdio.h>
#include <string>

class Texture
{

	public:
        SDL_Rect* spriteClips;
        SDL_Texture* texture;
		//Initializes variables
		Texture();
		Texture(int x);

		//Deallocates memory
		~Texture();
		bool init();
        bool loadMedia();
        bool SetRenderDrawColor();
        void renderPresent();
        void renderClear();
		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x , int y ,int size , SDL_Rect& clip);

		//Gets image dimensions
		int getWidth();
		int getHeight();
		int framesCount;

	private:
		SDL_Texture * texture;
	   	int mWidth;
		int mHeight;
};


Texture::Texture()
{
	//Initialize

	texture     = NULL;
	mWidth      = 0;
	mHeight     = 0;
	window      = NULL;
	renderer    = NULL;
	spriteClips = NULL;
}
Texture::Texture(int x){
    texture     = NULL;
	mWidth      = 0;
	mHeight     = 0;
	window      = NULL;
	renderer    = NULL;
  spriteClips = new SDL_Rect[x];

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
	this->texture = newTexture;
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



void Texture::render( int x , int y ,int size , SDL_Rect& clip )

{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip)
	{

		renderQuad.w = clip.w*size;
		renderQuad.h = clip.h*size;

	}

	//Render to screen
	SDL_RenderCopy( renderer, texture, NULL, &renderQuad );
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
	if( ! Texture::loadFromFile("rec/Holy_War_Jesus.png"))
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite

		this->spriteClips[ 0 ].x = 2;
		this->spriteClips[ 0 ].y = 0;
		this->spriteClips[ 0 ].w = 38;
		this->spriteClips[ 0 ].h = 40;

		this->spriteClips[1].x = 43;
		this->spriteClips[1].y = 0;
		this->spriteClips[1].w = 38;
		this->spriteClips[1].h = 40;

		this->spriteClips[2].x = 84;
		this->spriteClips[2].y = 0;
		this->spriteClips[2].w = 38;
		this->spriteClips[2].h = 40;

		this->spriteClips[3].x = 125;
		this->spriteClips[3].y = 0;
		this->spriteClips[3].w = 38;
		this->spriteClips[3].h = 40;

		this->spriteClips[4].x = 166;
		this->spriteClips[4].y = 0;
		this->spriteClips[4].w = 38;
		this->spriteClips[4].h = 40;

		this->spriteClips[5].x = 207;
		this->spriteClips[5].y = 0;
		this->spriteClips[5].w = 38;
		this->spriteClips[5].h = 40;

		this->spriteClips[6].x = 248;
		this->spriteClips[6].y = 0;
		this->spriteClips[6].w = 38;
		this->spriteClips[6].h = 40;

		this->spriteClips[7].x = 289;
		this->spriteClips[7].y = 0;
		this->spriteClips[7].w = 38;
		this->spriteClips[7].h = 40;




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

#endif
