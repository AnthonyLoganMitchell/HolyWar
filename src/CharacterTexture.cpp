#include "CharacterTexture.h"

CharacterTexture::CharacterTexture(int totalIdleClips, int totalJumpingClips, int totalFallingClips, int totalMovementClips, \
                                   int totalRegularAttackClips, int totalStrongAttackClips, std::string n) : Texture()
{
    this->idleTexture = NULL;
    this->name        = n;
    this->frameCount  = 0;
    this->xposition   = 0;
    this->yposition   = 0;

    this->idleClipCount = totalIdleClips-1;
    this->idleClips   = new SDL_Rect[totalIdleClips];

    this->jumpingClipCount = totalJumpingClips-1;
    this->jumpingClips = new SDL_Rect[totalJumpingClips];

    this->fallingClipCount = totalFallingClips-1;
    this->fallingClips = new SDL_Rect[totalFallingClips];

    this->movementClipCount = totalMovementClips-1;
    this->movementClips = new SDL_Rect[totalMovementClips];

    this->attackRegularClipCount = totalRegularAttackClips-1;
    this->attackRegularClips = new SDL_Rect[totalRegularAttackClips];

    this->strongAttackClipCount = totalStrongAttackClips-1;
    this->strongAttackClips = new SDL_Rect[totalStrongAttackClips];

}
CharacterTexture::~CharacterTexture()
{
    //TODO: Delete all textures on the heap.

}

bool CharacterTexture::loadCharacterFromFile(std::string path, CharacterTexture* t, SDL_Renderer* renderer,char t_type)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    bool load_flag = false;
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
    switch(t_type)
    {
    case 'I':
        t->idleTexture = newTexture;
        load_flag =true;
        break;

    case 'J':
        t->jumpingTexture = newTexture;
        load_flag =true;
        break;

    case 'F':
        t->fallingTexture = newTexture;
        load_flag =true;
        break;

    case 'M':
        t->movementTexture = newTexture;
        load_flag =true;
        break;

    case 'A':
        t->attackRegularTexture = newTexture;
        load_flag =true;
        break;

    case 'S':
        t->strongAttackTexture = newTexture;
        load_flag =true;
        break;
    }
    return load_flag;
}

bool CharacterTexture::loadCharacterMedia(CharacterTexture *t, SDL_Renderer* renderer)
{
    //Loading success flag
    //Load sprite sheet texture
    if(t->name == "jesus")
    {
        if(!this->loadCharacterFromFile("rec/animations/jesus-idle.png", t, renderer,'I'))
        {
            printf( "Failed to load sprite sheet texture!\n" );
            return false;
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

        //TODO: Load more of jesus's textures here before return. (movement,attacking,jumping,falling,ect...)
        return true;
    }//End of jesus textures.
    return false;
}

int CharacterTexture::GetIdleClipCount()
{
    return idleClipCount;
}

void CharacterTexture::SetFrameCount(int x)
{
    this->frameCount = x;
}

int CharacterTexture::GetFrameCount()
{
    return this->frameCount;
}

void CharacterTexture::TickFrameCount()
{
    frameCount++;
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
    if( this->idleTexture != NULL )
    {
        this->idleTexture = NULL;
        SDL_DestroyTexture( this->idleTexture);
    }
}

void CharacterTexture::render(CharacterTexture *t,SDL_Renderer* renderer, int x, int y,int size, SDL_Rect* clip, char t_type)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, t->GetWidth(), t->GetHeight() };
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w*size;
        renderQuad.h = clip->h*size;
    }
    //Render to screen
    switch(t_type)
    {
    case 'I':
        SDL_RenderCopy( renderer,t->idleTexture, clip, &renderQuad );
        break;

    case 'J':
        SDL_RenderCopy( renderer, t->jumpingTexture, clip, &renderQuad );
        break;

    case 'F':
        SDL_RenderCopy( renderer, t->fallingTexture, clip, &renderQuad );
        break;

    case 'M':
        SDL_RenderCopy( renderer, t->movementTexture, clip, &renderQuad );
        break;

    case 'A':
        SDL_RenderCopy( renderer, t->attackRegularTexture, clip, &renderQuad );
        break;

    case 'S':
        SDL_RenderCopy( renderer, t->strongAttackTexture, clip, &renderQuad );
        break;
    }
}

int CharacterTexture::GetXPos()
{
    return this->xposition;
}

int CharacterTexture::GetYPos()
{
    return this->yposition;
}

void CharacterTexture::SetXPos(int x)
{
    this->xposition = x;
}

void CharacterTexture::SetYPos(int y)
{
    this->yposition = y;
}
