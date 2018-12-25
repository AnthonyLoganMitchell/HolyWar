#include "Texture.h"

CharacterTexture::CharacterTexture(int totalClips, std::string n, int xPos, int yPos)
{
    texture       = NULL;
    width         = 0;
    height        = 0;
    name          = n;
    frameCount    = 0;
    xposition     = xPos;
    yposition     = yPos;
    spriteCount   = totalClips-1;
    idleClips   = new SDL_Rect[totalClips];
    isInitialized = false;

}
bool CharacterTexture::loadFromFile( std::string path, CharacterTexture* t, SDL_Renderer* renderer)
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

bool CharacterTexture::loadCharacterMedia(CharacterTexture *t, SDL_Renderer* renderer)
{
    //Loading success flag
    bool success = true;
    //Load sprite sheet texture
    if(t->name == "jesus" && !this->loadFromFile("rec/Holy_War_Jesus-Sheet-strip.png",t,renderer))
    {

        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        //Set top left sprite
        t-> idleClips[ 0 ].x = 2;
        t-> idleClips[ 0 ].y = 0;
        t-> idleClips[ 0 ].w = 38;
        t-> idleClips[ 0 ].h = 40;

        t-> idleClips[1].x = 43;
        t-> idleClips[1].y = 0;
        t-> idleClips[1].w = 38;
        t-> idleClips[1].h = 40;

        t-> idleClips[2].x = 84;
        t-> idleClips[2].y = 0;
        t-> idleClips[2].w = 38;
        t-> idleClips[2].h = 40;

        t-> idleClips[3].x = 125;
        t-> idleClips[3].y = 0;
        t-> idleClips[3].w = 38;
        t-> idleClips[3].h = 40;

        t-> idleClips[4].x = 166;
        t-> idleClips[4].y = 0;
        t-> idleClips[4].w = 38;
        t-> idleClips[4].h = 40;

        t-> idleClips[5].x = 207;
        t-> idleClips[5].y = 0;
        t-> idleClips[5].w = 38;
        t-> idleClips[5].h = 40;

        t-> idleClips[6].x = 248;
        t-> idleClips[6].y = 0;
        t-> idleClips[6].w = 38;
        t-> idleClips[6].h = 40;

        t-> idleClips[7].x = 289;
        t-> idleClips[7].y = 0;
        t-> idleClips[7].w = 38;
        t-> idleClips[7].h = 40;
    }
    return success;
}

void CharacterTexture::TickFrameCount()
{
    frameCount++;

}

int CharacterTexture::GetSpriteCount()
{
    return spriteCount;
}

void CharacterTexture::SetFrameCount(int x)
{
    frameCount = x;
}

int CharacterTexture::GetFrameCount()
{
    return frameCount;
}

void CharacterTexture::SetWidth(int x)
{
    this->width = x;
}

void CharacterTexture::SetHeight(int x)
{
    this->height = x;
}

int CharacterTexture::GetWidth()
{
    return width;
}

int CharacterTexture::GetHeight()
{
    return height;
}

void CharacterTexture::Free_Texture()
{
    //Free texture if it exists
    if( this != NULL )
    {
        this->texture = NULL;
        SDL_DestroyTexture( this->texture );
    }
}

void CharacterTexture::InitTexture()
{
    this->isInitialized = true;
}

CharacterTexture *CharacterTexture::initCharacterTexture(std::string name)
{
    CharacterTexture *temp = new CharacterTexture(9,name,320,240);
    return temp;
}

bool CharacterTexture::deleteTexture(CharacterTexture *v)
{
    delete v;
    return true;
}

void CharacterTexture::render(CharacterTexture *t,SDL_Renderer* renderer, int x, int y,int size, SDL_Rect* clip )
{
    //Set rendering space and render to screen
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
