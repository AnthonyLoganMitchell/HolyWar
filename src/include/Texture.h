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
		//Gets image dimensions
		int getWidth();
		int getHeight();
		void SetWidth(int x);
		void SetHeight(int x);
		int framesCount;
		private:
	   	int Width;
		int Height;
};


Texture::Texture()
{
	//Initialize
	texture    = NULL;
	Width     = 0;
	Height    = 0;
	window     = NULL;
	renderer   = NULL;
	std::string name       = NULL;
}
Texture::Texture(int x,std::string n)
{
    texture     = NULL;
	Width      = 0;
	Height     = 0;
	window      = NULL;
	renderer    = NULL;
	name        = n;
	spriteClips = new SDL_Rect[x];

}
void Texture::SetWidth(int x)
{
    Width = x;
}
void Texture::SetHeight(int x)
{
    Height = x;
}
int Texture::getWidth()
{
	return Width;
}

int Texture::getHeight()
{
	return Height;
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
