#include "MenuTexture.h"
//Fix this constructor.
/*MenuTexture::MenuTexture()
{

}*/

bool MenuTexture::loadMenuFromFile( std::string path, MenuTexture* t, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
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

bool MenuTexture::loadMenuMedia(MenuTexture *t, SDL_Renderer* renderer)
{

    //Loading success flag
    bool success = true;
    //Load sprite sheet texture for menus here
    if(t->name == "<Insert Menu Texture here>" && !this->loadMenuFromFile("<Insert menu file path here>",t,renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {


    }
    return success;
}

int MenuTexture::GetWidth()
{
    return this->width;
}

int MenuTexture::GetHeight()
{
   return this->height;
}

void MenuTexture::SetWidth(int x)
{
    this->width = x;
}

void MenuTexture::SetHeight(int x)
{
    this->height = x;
}

void MenuTexture::SetFrameCount(int x)
{
    this->frameCount = x;
}

int MenuTexture::GetFrameCount()
{
    return this->frameCount;
}

void MenuTexture::Free_Texture()
{
    //Free texture if it exists
    if( this->texture != NULL )
    {
        this->texture = NULL;
        SDL_DestroyTexture( this->texture );
    }
}
