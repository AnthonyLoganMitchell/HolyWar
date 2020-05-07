/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterTexture.h"

CharacterTexture::CharacterTexture(int totalIdleClips,int totalJumpingClips,int totalFallingClips,int totalWalkingClips,int totalRunningClips,int totalRegularAttackClips,\
                                   int totalRegularAttackClips2,int totalRegularJumpingAttackClips,int totalStrongAttackClips,std::string n,SDL_Renderer* rend) : Texture()
{
    this->idleTexture = NULL;
    this->attackRegularTexture = NULL;
    this->walkingTexture = NULL;
    this->fallingTexture = NULL;
    this->attackStrongTexture = NULL;
    this->attackRegularJumpingTexture = NULL;
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

    this->walkingClipCount = totalWalkingClips-1;
    this->walkingClips = new SDL_Rect[totalWalkingClips];

    this->runningClipCount =  totalRunningClips -1;
    this->RunningClips = new SDL_Rect[totalRunningClips];

    this->attackRegularClipCount = totalRegularAttackClips-1;
    this->attackRegularClips = new SDL_Rect[totalRegularAttackClips];

    this->attackRegularClipCount2 = totalRegularAttackClips2-1;
    this->attackRegularClips2 = new SDL_Rect[totalRegularAttackClips2];

    this->attackRegularJumpingClipCount = totalRegularJumpingAttackClips-1;
    this->attackRegularJumpingClips = new SDL_Rect[totalRegularJumpingAttackClips];

    this->attackStrongClipCount = totalStrongAttackClips-1;
    this->attackStrongClips = new SDL_Rect[totalStrongAttackClips];
    //THESE HAVE TO BE == 1
    //Cant divide by zero....
    this->idleMod =1;
    this->jumpingMod =1;
    this->walkMod = 1;
    this->runMod = 1;
    this->fallingMod = 1;
    this->attackRegMod =1;
    this->attackRegMod2 =1;
    this->attackRegJumpingMod=1;
    this->attackStrongMod =1;
    this->loadCharacterMedia(this,rend);
}
CharacterTexture::~CharacterTexture()
{
    //TODO: Delete all textures on the heap.

}

bool CharacterTexture::loadCharacterFromFile(std::string path, CharacterTexture* t, SDL_Renderer* renderer,std::string t_type)
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
    if(t_type == "I")
    {
        t->idleTexture = newTexture;
        load_flag = true;
    }
    else if( t_type == "J")
    {
        t->jumpingTexture = newTexture;
        load_flag = true;
    }
    else if(t_type =="F")
    {
        t->fallingTexture = newTexture;
        load_flag = true;
    }
    else if(t_type == "W")
    {
        t->walkingTexture = newTexture;
        load_flag = true;
    }
    else if(t_type == "R")
    {
        t->runningTexture = newTexture;
        load_flag = true;
    }
    else if(t_type == "A")
    {
        t->attackRegularTexture = newTexture;
        load_flag = true;
    }
    else if(t_type == "A2")
    {
        t->attackRegularTexture2 = newTexture;
        load_flag = true;
    }
    else if (t_type == "JA")
    {
        t->attackRegularJumpingTexture = newTexture;
        load_flag = true;
    }
    else if(t_type == "S1")
    {
        t->attackStrongTexture = newTexture;
        load_flag = true;
    }
    return load_flag;
}

bool CharacterTexture::loadCharacterMedia(CharacterTexture *t, SDL_Renderer* renderer)
{
    //Loading success flag
    //Load sprite sheet texture
    if(t->name == "jesus")
    {
        if(!this->loadCharacterFromFile("../../rec/animations/characters/jesus/jesus-idle.png", t, renderer,"I"))
        {
            printf( "Failed to load sprite sheet texture! jesus-idle.png\n" );
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
    if(t->name == "Horus")
    {
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_idle.png", t, renderer,"I"))
        {
            printf( "Failed to load sprite sheet texture! horus_idle.png\n" );
            return false;
        }
        else
        {
            int width = 79;
            int x_pos = 1;
            for (int i =0; i<18; i++)
            {
                t->idleClips[i].x = x_pos;
                t->idleClips[i].y =1;
                t->idleClips[i].w =79;
                t->idleClips[i].h =65;
                x_pos = x_pos + width + 1;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_walk.png", t, renderer,"W"))
        {
            printf( "Failed to load sprite sheet texture! horus_walk.png\n" );
            return false;
        }
        else
        {
            int width = 80;
            int x_pos = 1;
            for (int i = 0; i<17; i++)
            {
                t->walkingClips[i].x = x_pos;
                t->walkingClips[i].y =1;
                t->walkingClips[i].w =80;
                t->walkingClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_jump.png", t, renderer,"J"))
        {
            printf( "Failed to load sprite sheet texture! horus_jump.png\n" );
            return false;
        }
        else
        {
            int width = 80;
            int x_pos = 1;
            for (int i = 0; i<11; i++)
            {
                t->jumpingClips[i].x = x_pos;
                t->jumpingClips[i].y =1;
                t->jumpingClips[i].w =80;
                t->jumpingClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_falling.png", t, renderer, "F"))
        {
            printf( "Failed to load sprite sheet texture! horus_falling.png\n" );
            return false;
        }
        else
        {
            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<6; i++)
            {
                t->fallingClips[i].x = x_pos;
                t->fallingClips[i].y =1;
                t->fallingClips[i].w =85;
                t->fallingClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_reg_attack_1.png", t, renderer, "A"))
        {
            printf( "Failed to load sprite sheet texture! horus_reg_attack_1.png\n" );
            return false;
        }
        else
        {

            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<14; i++)
            {
                t->attackRegularClips[i].x = x_pos;
                t->attackRegularClips[i].y =1;
                t->attackRegularClips[i].w =85;
                t->attackRegularClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_reg_attack_2.png", t, renderer,"A2"))
        {
            printf( "Failed to load sprite sheet texture! horus_reg_attack_2.png\n" );
            return false;
        }
        else
        {
            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<16; i++)
            {
                t->attackRegularClips2[i].x = x_pos;
                t->attackRegularClips2[i].y =1;
                t->attackRegularClips2[i].w =85;
                t->attackRegularClips2[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_jumping_regular_attack.png", t, renderer,"JA"))
        {
            printf( "Failed to load sprite sheet texture! horus_jumping_regular_attack.png\n" );
            return false;
        }
        else
        {
            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<13; i++)
            {
                t->attackRegularJumpingClips[i].x = x_pos;
                t->attackRegularJumpingClips[i].y =1;
                t->attackRegularJumpingClips[i].w =85;
                t->attackRegularJumpingClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        return true;
    }
    return false;
}

int CharacterTexture::GetIdleClipCount()
{
    return this->idleClipCount;
}
int CharacterTexture::GetJumpingClipCount()
{
    return this->jumpingClipCount;
}
int CharacterTexture::GetFallingClipCount()
{
    return this->fallingClipCount;
}
int CharacterTexture::GetWalkingClipCount()
{
    return this->walkingClipCount;
}
int CharacterTexture::GetRunningClipCount()
{
    return this->runningClipCount;
}
int CharacterTexture::GetRegularAttackClipCount()
{
    return this->attackRegularClipCount;
}
int CharacterTexture::GetRegularAttackClipCount2()
{
    return this->attackRegularClipCount2;
}

int CharacterTexture::GetJumpingRegularAttackClipCount()
{
    return this->attackRegularJumpingClipCount;
}
int CharacterTexture::GetStrongClipCount()
{
    return this->attackStrongClipCount;
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

void CharacterTexture::render(CharacterTexture *t,SDL_Renderer* renderer, int x, int y,int scale, int offset_width, int offset_height, SDL_Rect* clip, std::string t_type, SDL_RendererFlip flip)
{
    if (scale < 1)
    {
        scale = 1;
    }
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, t->GetWidth(), t->GetHeight() };
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = (clip->w*scale)+offset_width;
        renderQuad.h = (clip->h*scale)+offset_height;
    }
    //Render to screen
        if(t_type == "I")
        {
            SDL_RenderCopyEx(renderer,t->idleTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "J")
        {
            SDL_RenderCopyEx(renderer,t->jumpingTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "F")
        {
            SDL_RenderCopyEx(renderer,t->fallingTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "M")
        {
            SDL_RenderCopyEx(renderer,t->walkingTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "R")
        {
            SDL_RenderCopyEx(renderer,t->runningTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "A")
        {
            SDL_RenderCopyEx(renderer,t->attackRegularTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "A2")
        {
            SDL_RenderCopyEx(renderer,t->attackRegularTexture2,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "JA")
        {
            SDL_RenderCopyEx(renderer,t->attackRegularJumpingTexture,clip,&renderQuad,0.0,NULL,flip);
        }
        else if(t_type == "S1")
        {
            SDL_RenderCopyEx(renderer,t->attackStrongTexture,clip,&renderQuad,0.0,NULL,flip);
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
