/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "CharacterObject.h"
#include "CharacterTexture.h"

CharacterObject::CharacterObject(std::string Name,int8_t Health,SDL_Renderer* renderer)
{
    this->name=Name;
    this->health = Health;
    this->InitializeCharacter(Name,renderer);
    this->fluct_velx =0;
    this->fluct_vely =0;
    this->posX=0;
    this->posY=0;
    this->isJumping = false;
    this->isMovingLeft = false;
    this->isMovingRight = false;
    this->isFalling = true;
    this->isHoldingReg = false;
    this->isHoldingStrong =false;
    this->isColliding = false;
    this->isAttackingReg = false;
    this->regAttackCount = 0;
    this->StrongAttackCount = 0;
    this->jumpBlock = 0;
    this->regAttackLastPress = SDL_GetTicks();
    this->strongAttackLastPress = SDL_GetTicks();
    this->lastDirection = "LEFT";
}

CharacterObject::~CharacterObject()
{

}

void CharacterObject::InitializeCharacter(std::string Name,SDL_Renderer* renderer)
{
    //For Sanities sake while doing these.
    //TotalClip numbers parameter structure in CharacterTextures.
    //(IdleClips,JumpingClips,FallingClips,MovementClips,RegularAttackClips,RegularAttackClips2,StrongAttackClips,Name,renderer)
    if(Name == "Horus")
    {
        CharacterTexture* char_ptr = new CharacterTexture(18,11,6,17,14,16,13,0,Name,renderer);
        this->char_textures = char_ptr;
        this->char_textures->idleMod = 4;
        this->char_textures->jumpingMod = 2;
        this->char_textures->moveMod = 2;
        this->char_textures->attackRegMod = 1;
        this->char_textures->attackRegMod2 = 1;
        this->char_textures->fallingMod = 2;
        this->char_textures->attackRegJumpingMod=1;
        char_ptr = NULL;
        delete(char_ptr);
    }
}

void CharacterObject::Move()
{

    if(!this->isColliding)
    {
        if(this->isJumping || this->isFalling)
        {
            this->CalculateGravity();
        }
        if(this->fluct_vely >=0)
        {
            this->isFalling = true;
            this->isJumping = false;
        }
    }
    this->posY += this->fluct_vely;
    this->posX += this->fluct_velx;
}

void CharacterObject::CalculateGravity()
{
    this->fluct_vely+=2;
}
