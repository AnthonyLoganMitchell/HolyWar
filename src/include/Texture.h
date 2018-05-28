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
		int GetWidth();
		int GetHeight();
		void SetWidth(int x);
		void SetHeight(int x);
		void Free_Texture();
		private:
	   	int width;
		int height;
		int frameCount;
};


Texture::Texture()
{
	//Initialize
	texture     = NULL;
	width       = 0;
	height      = 0;
	window      = NULL;
	renderer    = NULL;
	string name = NULL;
	spriteClips = NULL;
}
Texture::Texture(int x,string n)
{
    texture     = NULL;
	width       = 0;
	height      = 0;
	window      = NULL;
	renderer    = NULL;
	name        = n;
	spriteClips = new SDL_Rect[x];

}
void Texture::SetWidth(int x)
{
    width = x;
}
void Texture::SetHeight(int x)
{
    height = x;
}
int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}

void Texture::Free_Texture()
{
	//Free texture if it exists
	if( this != NULL )
	{
		this->texture = NULL;
		SDL_DestroyTexture( this->texture );


	}
}


#endif
