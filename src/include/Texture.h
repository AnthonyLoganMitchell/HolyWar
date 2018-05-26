#ifndef   TEXTURE_H_
#define   TEXTURE_H_
#include "Globals.h"
#include <stdio.h>
#include <string>

class Texture
{
	public:
        SDL_Texture* texture;
        SDL_Rect* spriteClips;
        std::string name;
		//Initializes variables
		Texture();
		Texture(int x,std::string);
		//Deallocates memory
		~Texture();
		bool init();

        bool SetRenderDrawColor();
        void renderPresent();
        void renderClear();
		//Loads image at specified path
		bool loadFromFile( std::string path );

		void close();

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x , int y ,int size , SDL_Rect& clip);

		//Gets image dimensions
		int getWidth();
		int getHeight();
		int framesCount;
	   	int mWidth;
		int mHeight;
};


Texture::Texture()
{
	//Initialize
	texture    = NULL;
	mWidth     = 0;
	mHeight    = 0;
	window     = NULL;
	renderer   = NULL;
	std::string name       = NULL;
}
Texture::Texture(int x,std::string n)
{
    texture     = NULL;
	mWidth      = 0;
	mHeight     = 0;
	window      = NULL;
	renderer    = NULL;
	name        = n;
	spriteClips = new SDL_Rect[x];

}






void Texture::render( int x , int y ,int size , SDL_Rect& clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( &clip != NULL )
	{
		renderQuad.w = clip.w*size;
		renderQuad.h = clip.h*size;
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

bool Texture::SetRenderDrawColor(){
    if(!SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF )){
        printf("RenderDrawColor failed:SDL_ERROR:%s\n",SDL_GetError());
        return false;
    }else{
        return true;
    }

}
void close(Texture *t)
{
	//Free loaded images
	free(t->texture);
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
