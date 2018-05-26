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
        string name;
		Texture();
		Texture(int x,string);
		//Loads image at specified path
		bool loadFromFile( string path );
		//Gets image dimensions
		int getWidth();
		int getHeight();
		void SetWidth(int x);
		void SetHeight(int x);
		private:
	   	int Width;
		int Height;
};


Texture::Texture()
{
	//Initialize
	texture     = NULL;
	Width       = 0;
	Height      = 0;
	window      = NULL;
	renderer    = NULL;
	string name = NULL;
	spriteClips = NULL;
}
Texture::Texture(int x,string n)
{
    texture     = NULL;
	Width       = 0;
	Height      = 0;
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




#endif
