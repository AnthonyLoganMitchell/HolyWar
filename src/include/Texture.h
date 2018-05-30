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
		Texture(int x,string,int xPos,int yPos);
		//Loads image at specified path
		bool loadFromFile( string path );
		//Gets image dimensions
		int GetWidth();
		int GetHeight();
		int GetSpriteCount();

		void SetWidth(int x);
		void SetHeight(int x);
		void SetFrameCount(int x);
		void TickFrameCount();
		int GetFrameCount();
		void Free_Texture();
		int xposition;
        int yposition;
		private:
       	int width;
		int height;
		int frameCount;
		int spriteCount;
		bool isInitialized;
};


Texture::Texture()
{
	//Initialize
	texture         = NULL;
	width           = 0;
	height          = 0;
	window          = NULL;
	renderer        = NULL;
	string name     = NULL;
	spriteClips     = NULL;
	xposition       = 0;
	yposition       = 0;
	spriteCount     = 0;
	frameCount      = 0;
	isInitialized   =true;

}
Texture::Texture(int x,string n,int xPos , int yPos)
{
    texture     = NULL;
	width       = 0;
	height      = 0;
	window      = NULL;
	renderer    = NULL;
	name        = n;
	frameCount  = 0;
    xposition   = xPos;
    yposition   = yPos;
	spriteCount = x-1;
	spriteClips = new SDL_Rect[x];


}





void Texture::TickFrameCount()
{
    frameCount++;

}
int Texture::GetSpriteCount()
{
    return spriteCount;
}
void Texture::SetFrameCount(int x)
{
    frameCount = x;
}
int Texture::GetFrameCount()
{
    return frameCount;
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
