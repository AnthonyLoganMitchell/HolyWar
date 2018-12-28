#include "MenuTexture.h"
#include <string>
//Fix this constructor.
MenuTexture::MenuTexture(int totalClips, std::string texName, int xpos, int ypos)
{
    this->textureClipCount = totalClips -1;
    this->name = texName;
    this->xposition = xpos;
    this->yposition = ypos;
    this->animation = new SDL_Rect[totalClips];

}

//TODO: Next thing on list is to create the render function here for menuTextures. See CharacterTexture.cpp
void MenuTexture::render(MenuTexture *t,SDL_Renderer* renderer, int x, int y,int size, SDL_Rect* clip )
{
    //Set rendering space and render to screen
    std::cout << t->GetWidth() << ": " << t->GetHeight() << std::endl;
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
bool MenuTexture::loadMenuTextureFromFile( std::string path, MenuTexture* t, SDL_Renderer* renderer)
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
    if(t->name == "MainMenuLogo" && !this->loadMenuTextureFromFile("rec/Holy_War_Menu_Strip.png",t,renderer))
    {
        printf( "Failed to load sprite sheet texture: Holy_War_Menu_Strip.png\n" );
        success = false;
    }
    else
    {
        t->animation[0].x =0;
        t->animation[0].y =0;
        t->animation[0].h =39;
        t->animation[0].w =266;

    }

    if(t->name == "MainMenuTorch" && !this->loadMenuTextureFromFile("rec/Menu_Torch.png",t,renderer))
    {
        printf("Failed to load sprite sheet texture: Menu_Torch.png\n");
        success = false;
    }
    else
    {
        t->animation[0].x = 0;
        t->animation[0].y = 0;
        t->animation[0].h = 39;
        t->animation[0].w = 38;

        t->animation[1].x = 39;
        t->animation[1].y = 0;
        t->animation[1].h = 39;
        t->animation[1].w = 38;

        t->animation[2].x = 77;
        t->animation[2].y = 0;
        t->animation[2].h = 39;
        t->animation[2].w = 38;

        t->animation[3].x = 115;
        t->animation[3].y = 0;
        t->animation[3].h = 39;
        t->animation[3].w = 38;

        t->animation[4].x = 153;
        t->animation[4].y = 0;
        t->animation[4].h = 39;
        t->animation[4].w = 38;

        t->animation[5].x = 191;
        t->animation[5].y = 0;
        t->animation[5].h = 39;
        t->animation[5].w = 38;

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
void MenuTexture::SetXPos(int x)
{
    this->xposition = x;
}

void MenuTexture::SetYPos(int y)
{
    this->yposition = y;
}

int MenuTexture::GetXPos()
{
    return this->xposition;
}
int MenuTexture::GetYPos()
{
    return this->yposition;
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
