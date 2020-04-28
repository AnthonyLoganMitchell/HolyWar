/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterTexture.h"

CharacterTexture::CharacterTexture(int totalIdleClips,int totalJumpingClips,int totalFallingClips,int totalMovementClips,int totalRegularAttackClips,\
                                   int totalRegularAttackClips2,int totalRegularJumpingAttackClips,int totalStrongAttackClips,std::string n,SDL_Renderer* rend) : Texture()
{
    this->idleTexture = NULL;
    this->attackRegularTexture = NULL;
    this->movementTexture = NULL;
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

    this->movementClipCount = totalMovementClips-1;
    this->movementClips = new SDL_Rect[totalMovementClips];

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
    this->moveMod = 1;
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
    else if(t_type == "M")
    {
        t->movementTexture = newTexture;
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
    else if(t_type == "S")
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
            t->idleClips[0].x =1;
            t->idleClips[0].y =1;
            t->idleClips[0].w =79;
            t->idleClips[0].h =65;

            t->idleClips[1].x =81;
            t->idleClips[1].y =1;
            t->idleClips[1].w =79;
            t->idleClips[1].h =65;

            t->idleClips[2].x =161;
            t->idleClips[2].y =1;
            t->idleClips[2].w =79;
            t->idleClips[2].h =65;

            t->idleClips[3].x =241;
            t->idleClips[3].y =1;
            t->idleClips[3].w =79;
            t->idleClips[3].h =65;

            t->idleClips[4].x =321;
            t->idleClips[4].y =1;
            t->idleClips[4].w =79;
            t->idleClips[4].h =65;

            t->idleClips[5].x =401;
            t->idleClips[5].y =1;
            t->idleClips[5].w =79;
            t->idleClips[5].h =65;

            t->idleClips[6].x =481;
            t->idleClips[6].y =1;
            t->idleClips[6].w =79;
            t->idleClips[6].h =65;

            t->idleClips[7].x =561;
            t->idleClips[7].y =1;
            t->idleClips[7].w =79;
            t->idleClips[7].h =65;

            t->idleClips[8].x =641;
            t->idleClips[8].y =1;
            t->idleClips[8].w =79;
            t->idleClips[8].h =65;

            t->idleClips[9].x =721;
            t->idleClips[9].y =1;
            t->idleClips[9].w =79;
            t->idleClips[9].h =65;

            t->idleClips[10].x =801;
            t->idleClips[10].y =1;
            t->idleClips[10].w =79;
            t->idleClips[10].h =65;

            t->idleClips[11].x =881;
            t->idleClips[11].y =1;
            t->idleClips[11].w =79;
            t->idleClips[11].h =65;

            t->idleClips[12].x =961;
            t->idleClips[12].y =1;
            t->idleClips[12].w =79;
            t->idleClips[12].h =65;

            t->idleClips[13].x =1041;
            t->idleClips[13].y =1;
            t->idleClips[13].w =79;
            t->idleClips[13].h =65;

            t->idleClips[14].x =1121;
            t->idleClips[14].y =1;
            t->idleClips[14].w =79;
            t->idleClips[14].h =65;

            t->idleClips[15].x =1201;
            t->idleClips[15].y =1;
            t->idleClips[15].w =79;
            t->idleClips[15].h =65;

            t->idleClips[16].x =1281;
            t->idleClips[16].y =1;
            t->idleClips[16].w =79;
            t->idleClips[16].h =65;

            t->idleClips[17].x =1361;
            t->idleClips[17].y =1;
            t->idleClips[17].w =79;
            t->idleClips[17].h =65;
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_movement_prototype.png", t, renderer,"M"))
        {
            printf( "Failed to load sprite sheet texture! horus_movement_prototype.png\n" );
            return false;
        }
        else
        {
            t->movementClips[0].x =1;
            t->movementClips[0].y =1;
            t->movementClips[0].w =80;
            t->movementClips[0].h =65;

            t->movementClips[1].x =81;
            t->movementClips[1].y =1;
            t->movementClips[1].w =80;
            t->movementClips[1].h =65;

            t->movementClips[2].x =161;
            t->movementClips[2].y =1;
            t->movementClips[2].w =80;
            t->movementClips[2].h =65;

            t->movementClips[3].x =241;
            t->movementClips[3].y =1;
            t->movementClips[3].w =80;
            t->movementClips[3].h =65;

            t->movementClips[4].x =321;
            t->movementClips[4].y =1;
            t->movementClips[4].w =80;
            t->movementClips[4].h =65;

            t->movementClips[5].x =401;
            t->movementClips[5].y =1;
            t->movementClips[5].w =80;
            t->movementClips[5].h =65;

            t->movementClips[6].x =481;
            t->movementClips[6].y =1;
            t->movementClips[6].w =80;
            t->movementClips[6].h =65;

            t->movementClips[7].x =561;
            t->movementClips[7].y =1;
            t->movementClips[7].w =80;
            t->movementClips[7].h =65;

            t->movementClips[8].x =641;
            t->movementClips[8].y =1;
            t->movementClips[8].w =80;
            t->movementClips[8].h =65;

            t->movementClips[9].x =721;
            t->movementClips[9].y =1;
            t->movementClips[9].w =80;
            t->movementClips[9].h =65;

            t->movementClips[10].x =801;
            t->movementClips[10].y =1;
            t->movementClips[10].w =80;
            t->movementClips[10].h =65;

            t->movementClips[11].x =881;
            t->movementClips[11].y =1;
            t->movementClips[11].w =80;
            t->movementClips[11].h =65;

            t->movementClips[12].x =961;
            t->movementClips[12].y =1;
            t->movementClips[12].w =80;
            t->movementClips[12].h =65;

            t->movementClips[13].x =1041;
            t->movementClips[13].y =1;
            t->movementClips[13].w =80;
            t->movementClips[13].h =65;

            t->movementClips[14].x =1121;
            t->movementClips[14].y =1;
            t->movementClips[14].w =80;
            t->movementClips[14].h =65;

            t->movementClips[15].x =1201;
            t->movementClips[15].y =1;
            t->movementClips[15].w =80;
            t->movementClips[15].h =65;

            t->movementClips[16].x =1281;
            t->movementClips[16].y =1;
            t->movementClips[16].w =80;
            t->movementClips[16].h =65;
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_jump_prototype.png", t, renderer,"J"))
        {
            printf( "Failed to load sprite sheet texture! horus_jump_prototype.png\n" );
            return false;
        }
        else
        {
            t->jumpingClips[0].x =1;
            t->jumpingClips[0].y =1;
            t->jumpingClips[0].w =80;
            t->jumpingClips[0].h =65;

            t->jumpingClips[1].x =81;
            t->jumpingClips[1].y =1;
            t->jumpingClips[1].w =80;
            t->jumpingClips[1].h =65;

            t->jumpingClips[2].x =161;
            t->jumpingClips[2].y =1;
            t->jumpingClips[2].w =80;
            t->jumpingClips[2].h =65;

            t->jumpingClips[3].x =241;
            t->jumpingClips[3].y =1;
            t->jumpingClips[3].w =80;
            t->jumpingClips[3].h =65;

            t->jumpingClips[4].x =321;
            t->jumpingClips[4].y =1;
            t->jumpingClips[4].w =80;
            t->jumpingClips[4].h =65;

            t->jumpingClips[5].x =401;
            t->jumpingClips[5].y =1;
            t->jumpingClips[5].w =80;
            t->jumpingClips[5].h =65;

            t->jumpingClips[6].x =481;
            t->jumpingClips[6].y =1;
            t->jumpingClips[6].w =80;
            t->jumpingClips[6].h =65;

            t->jumpingClips[7].x =561;
            t->jumpingClips[7].y =1;
            t->jumpingClips[7].w =80;
            t->jumpingClips[7].h =65;

            t->jumpingClips[8].x =641;
            t->jumpingClips[8].y =1;
            t->jumpingClips[8].w =80;
            t->jumpingClips[8].h =65;

            t->jumpingClips[9].x =721;
            t->jumpingClips[9].y =1;
            t->jumpingClips[9].w =80;
            t->jumpingClips[9].h =65;

            t->jumpingClips[10].x =801;
            t->jumpingClips[10].y =1;
            t->jumpingClips[10].w =80;
            t->jumpingClips[10].h =65;
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_falling_prototype.png", t, renderer, "F"))
        {
            printf( "Failed to load sprite sheet texture! horus_falling_prototype.png\n" );
            return false;
        }
        else
        {
            t->fallingClips[0].x =1;
            t->fallingClips[0].y =1;
            t->fallingClips[0].w =85;
            t->fallingClips[0].h =65;

            t->fallingClips[1].x =86;
            t->fallingClips[1].y =1;
            t->fallingClips[1].w =85;
            t->fallingClips[1].h =65;

            t->fallingClips[2].x =171;
            t->fallingClips[2].y =1;
            t->fallingClips[2].w =85;
            t->fallingClips[2].h =65;

            t->fallingClips[3].x =256;
            t->fallingClips[3].y =1;
            t->fallingClips[3].w =85;
            t->fallingClips[3].h =65;

            t->fallingClips[4].x =341;
            t->fallingClips[4].y =1;
            t->fallingClips[4].w =85;
            t->fallingClips[4].h =65;

            t->fallingClips[5].x =426;
            t->fallingClips[5].y =1;
            t->fallingClips[5].w =85;
            t->fallingClips[5].h =65;
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_reg_attack_1_prototype.png", t, renderer, "A"))
        {
            printf( "Failed to load sprite sheet texture! horus_reg_attack_1_prototype.png\n" );
            return false;
        }
        else
        {
            t->attackRegularClips[0].x =1;
            t->attackRegularClips[0].y =1;
            t->attackRegularClips[0].w =85;
            t->attackRegularClips[0].h =65;

            t->attackRegularClips[1].x =86;
            t->attackRegularClips[1].y =1;
            t->attackRegularClips[1].w =85;
            t->attackRegularClips[1].h =65;

            t->attackRegularClips[2].x =171;
            t->attackRegularClips[2].y =1;
            t->attackRegularClips[2].w =85;
            t->attackRegularClips[2].h =65;

            t->attackRegularClips[3].x =256;
            t->attackRegularClips[3].y =1;
            t->attackRegularClips[3].w =85;
            t->attackRegularClips[3].h =65;

            t->attackRegularClips[4].x =341;
            t->attackRegularClips[4].y =1;
            t->attackRegularClips[4].w =85;
            t->attackRegularClips[4].h =65;

            t->attackRegularClips[5].x =426;
            t->attackRegularClips[5].y =1;
            t->attackRegularClips[5].w =85;
            t->attackRegularClips[5].h =65;

            t->attackRegularClips[6].x =511;
            t->attackRegularClips[6].y =1;
            t->attackRegularClips[6].w =85;
            t->attackRegularClips[6].h =65;

            t->attackRegularClips[7].x =596;
            t->attackRegularClips[7].y =1;
            t->attackRegularClips[7].w =85;
            t->attackRegularClips[7].h =65;

            t->attackRegularClips[8].x =681;
            t->attackRegularClips[8].y =1;
            t->attackRegularClips[8].w =85;
            t->attackRegularClips[8].h =65;

            t->attackRegularClips[9].x =766;
            t->attackRegularClips[9].y =1;
            t->attackRegularClips[9].w =85;
            t->attackRegularClips[9].h =65;

            t->attackRegularClips[10].x =851;
            t->attackRegularClips[10].y =1;
            t->attackRegularClips[10].w =85;
            t->attackRegularClips[10].h =65;

            t->attackRegularClips[11].x =936;
            t->attackRegularClips[11].y =1;
            t->attackRegularClips[11].w =85;
            t->attackRegularClips[11].h =65;

            t->attackRegularClips[12].x =1021;
            t->attackRegularClips[12].y =1;
            t->attackRegularClips[12].w =85;
            t->attackRegularClips[12].h =65;

            t->attackRegularClips[13].x =1106;
            t->attackRegularClips[13].y =1;
            t->attackRegularClips[13].w =85;
            t->attackRegularClips[13].h =65;
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_reg_attack_2_prototype.png", t, renderer,"A2"))
        {
            printf( "Failed to load sprite sheet texture! horus_reg_attack_2_prototype.png\n" );
            return false;
        }
        else
        {
            t->attackRegularClips2[0].x =1;
            t->attackRegularClips2[0].y =1;
            t->attackRegularClips2[0].w =85;
            t->attackRegularClips2[0].h =65;

            t->attackRegularClips2[1].x =86;
            t->attackRegularClips2[1].y =1;
            t->attackRegularClips2[1].w =85;
            t->attackRegularClips2[1].h =65;

            t->attackRegularClips2[2].x =171;
            t->attackRegularClips2[2].y =1;
            t->attackRegularClips2[2].w =85;
            t->attackRegularClips2[2].h =65;

            t->attackRegularClips2[3].x =256;
            t->attackRegularClips2[3].y =1;
            t->attackRegularClips2[3].w =85;
            t->attackRegularClips2[3].h =65;

            t->attackRegularClips2[4].x =341;
            t->attackRegularClips2[4].y =1;
            t->attackRegularClips2[4].w =85;
            t->attackRegularClips2[4].h =65;

            t->attackRegularClips2[5].x =426;
            t->attackRegularClips2[5].y =1;
            t->attackRegularClips2[5].w =85;
            t->attackRegularClips2[5].h =65;

            t->attackRegularClips2[6].x =511;
            t->attackRegularClips2[6].y =1;
            t->attackRegularClips2[6].w =85;
            t->attackRegularClips2[6].h =65;

            t->attackRegularClips2[7].x =596;
            t->attackRegularClips2[7].y =1;
            t->attackRegularClips2[7].w =85;
            t->attackRegularClips2[7].h =65;

            t->attackRegularClips2[8].x =681;
            t->attackRegularClips2[8].y =1;
            t->attackRegularClips2[8].w =85;
            t->attackRegularClips2[8].h =65;

            t->attackRegularClips2[9].x =766;
            t->attackRegularClips2[9].y =1;
            t->attackRegularClips2[9].w =85;
            t->attackRegularClips2[9].h =65;

            t->attackRegularClips2[10].x =851;
            t->attackRegularClips2[10].y =1;
            t->attackRegularClips2[10].w =85;
            t->attackRegularClips2[10].h =65;

            t->attackRegularClips2[11].x =936;
            t->attackRegularClips2[11].y =1;
            t->attackRegularClips2[11].w =85;
            t->attackRegularClips2[11].h =65;

            t->attackRegularClips2[12].x =1021;
            t->attackRegularClips2[12].y =1;
            t->attackRegularClips2[12].w =85;
            t->attackRegularClips2[12].h =65;

            t->attackRegularClips2[13].x =1106;
            t->attackRegularClips2[13].y =1;
            t->attackRegularClips2[13].w =85;
            t->attackRegularClips2[13].h =65;

            t->attackRegularClips2[14].x =1191;
            t->attackRegularClips2[14].y =1;
            t->attackRegularClips2[14].w =85;
            t->attackRegularClips2[14].h =65;

            t->attackRegularClips2[15].x =1276;
            t->attackRegularClips2[15].y =1;
            t->attackRegularClips2[15].w =85;
            t->attackRegularClips2[15].h =65;
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_jumping_regular_attack_prototype.png", t, renderer,"JA"))
        {
            printf( "Failed to load sprite sheet texture! horus_jumping_regular_attack_prototype.png\n" );
            return false;
        }
        else
        {
            t->attackRegularJumpingClips[0].x =1;
            t->attackRegularJumpingClips[0].y =1;
            t->attackRegularJumpingClips[0].w =85;
            t->attackRegularJumpingClips[0].h =65;

            t->attackRegularJumpingClips[1].x =86;
            t->attackRegularJumpingClips[1].y =1;
            t->attackRegularJumpingClips[1].w =85;
            t->attackRegularJumpingClips[1].h =65;

            t->attackRegularJumpingClips[2].x =171;
            t->attackRegularJumpingClips[2].y =1;
            t->attackRegularJumpingClips[2].w =85;
            t->attackRegularJumpingClips[2].h =65;

            t->attackRegularJumpingClips[3].x =256;
            t->attackRegularJumpingClips[3].y =1;
            t->attackRegularJumpingClips[3].w =85;
            t->attackRegularJumpingClips[3].h =65;

            t->attackRegularJumpingClips[4].x =341;
            t->attackRegularJumpingClips[4].y =1;
            t->attackRegularJumpingClips[4].w =85;
            t->attackRegularJumpingClips[4].h =65;

            t->attackRegularJumpingClips[5].x =426;
            t->attackRegularJumpingClips[5].y =1;
            t->attackRegularJumpingClips[5].w =85;
            t->attackRegularJumpingClips[5].h =65;

            t->attackRegularJumpingClips[6].x =511;
            t->attackRegularJumpingClips[6].y =1;
            t->attackRegularJumpingClips[6].w =85;
            t->attackRegularJumpingClips[6].h =65;

            t->attackRegularJumpingClips[7].x =596;
            t->attackRegularJumpingClips[7].y =1;
            t->attackRegularJumpingClips[7].w =85;
            t->attackRegularJumpingClips[7].h =65;

            t->attackRegularJumpingClips[8].x =681;
            t->attackRegularJumpingClips[8].y =1;
            t->attackRegularJumpingClips[8].w =85;
            t->attackRegularJumpingClips[8].h =65;

            t->attackRegularJumpingClips[9].x =766;
            t->attackRegularJumpingClips[9].y =1;
            t->attackRegularJumpingClips[9].w =85;
            t->attackRegularJumpingClips[9].h =65;

            t->attackRegularJumpingClips[10].x =851;
            t->attackRegularJumpingClips[10].y =1;
            t->attackRegularJumpingClips[10].w =85;
            t->attackRegularJumpingClips[10].h =65;

            t->attackRegularJumpingClips[11].x =936;
            t->attackRegularJumpingClips[11].y =1;
            t->attackRegularJumpingClips[11].w =85;
            t->attackRegularJumpingClips[11].h =65;

            t->attackRegularJumpingClips[12].x =1021;
            t->attackRegularJumpingClips[12].y =1;
            t->attackRegularJumpingClips[12].w =85;
            t->attackRegularJumpingClips[12].h =65;
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
int CharacterTexture::GetMoveingClipCount()
{
    return this->movementClipCount;
}
int CharacterTexture::GetRegularAttackClipCount()
{
    return this->attackRegularClipCount;
}
int CharacterTexture::GetRegularAttackClipCount2()
{
    return this->attackRegularClipCount2;
}

int CharacterTexture::GetJumpingRegularAttackClickCount()
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
            SDL_RenderCopyEx(renderer,t->movementTexture,clip,&renderQuad,0.0,NULL,flip);
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
        else if(t_type == "S")
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
