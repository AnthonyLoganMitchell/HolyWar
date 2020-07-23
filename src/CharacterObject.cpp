/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterObject.h"
#include "CharacterTexture.h"

CharacterObject::CharacterObject(std::string Name,int8_t Health,SDL_Renderer* renderer) {
    this->name=Name;
    this->health = Health;
    this->selfHitBoxOffsetX = 0;
    this->selfHitBoxOffsetY = 0;
    this->selfHitBoxOffsetWidth = 0;
    this->selfHitBoxOffsetHeight = 0;
    this->attackHitBoxOffsetX = 0;
    this->attackHitBoxOffsetY = 0;
    this->attackHitBoxOffsetWidth = 0;
    this->attackHitBoxOffsetHeight = 0;
    this->right_x_offset_attack = 0;
    this->left_x_offset_attack = 0;
    this->right_x_offset_self = 0;
    this->left_x_offset_self = 0;
    this->InitializeCharacter(Name,renderer);
    this->fluct_velx = 0;
    this->fluct_vely = 0;
    this->posX = 0;
    this->posY = 0;
    this->isJumping = false;

    this->isWalking = false;
    this->isRunning = false;
    this->isMovingLeft = false;
    this->isMovingRight = false;

    this->isFalling = true;
    this->isHolding = false;

    this->isColliding = false;
    this->isSpecialAttackOpen = false;
    this->isAttackingReg = false;
    this->isSpecialOpen = false;
    this->wasRunningWhenJump = false;
    this->regAttackCount = 0;
    this->StrongAttackCount = 0;
    this->jumpBlock = 0;

    this->regAttackLastPress = 0;
    this->strongAttackLastPress = 0;
    this->upPress = 0;
    this->downPress = 0;
    this->leftPress = 0;
    this->rightPress = 0;


    this->lastDirection = "LEFT";
    this->attackBox = NULL;
    this->selfBox = NULL;
}

CharacterObject::~CharacterObject() {

}

void CharacterObject::InitializeHitBoxes(int scale) {
    //TODO:// Delete from memory later
    this->attackBox = new Hitbox(this->posX,\
                                 this->posY,\
                                 (this->char_textures->idleClips[0].w*scale)+this->attackHitBoxOffsetWidth,\
                                 (this->char_textures->idleClips[0].h*scale)+this->attackHitBoxOffsetHeight);
    //TODO:// Delete from memory later
    this->selfBox = new Hitbox(this->posX,\
                               this->posY, \
                               (this->char_textures->idleClips[0].w*scale)+this->selfHitBoxOffsetWidth,\
                               (this->char_textures->idleClips[0].h*scale)+this->selfHitBoxOffsetHeight);


    //TEMP://
    //This block is for testing hitboxes
    this->selfBox->isAlpha = true;
    this->attackBox->isAlpha = true;
}

void CharacterObject::InitializeCharacter(std::string Name,SDL_Renderer* renderer) {
    //TODO:// In future this all needs moved out to json||xml and read in from disk.
    //NOTE:// For future development, remember that attackHitBoxOffsetX and
    //selfHitBoxOffsetX are both controlled within the CharacterModules::RunCharacters function.


    //For Sanities sake while doing these.
    //(IdleClips,JumpingClips,FallingClips,WalkingClips,RegularAttackClips,RegularAttackClips2,RegularJumpingAttackclips,StrongAttackClips,Name,renderer)
    if(Name == "Horus") {
        int idle = 18;
        int jumping = 11;
        int falling = 6;
        int walking = 17;
        int running = 12;
        int regAttack1= 14;
        int regAttack2= 16;
        int regJumpAttack = 13;
        int strongAttack1 = 0;
        int specialOpenAttack = 28;
        int specialOpenAttackCharacter = 9;

        CharacterTexture* char_ptr = new CharacterTexture(idle,jumping,falling,\
                walking, running, regAttack1,\
                regAttack2, regJumpAttack, strongAttack1,\
                specialOpenAttack, specialOpenAttackCharacter, Name, renderer);
        this->char_textures = char_ptr;

        //Modulation adjustments for frame speeds.
        ////////////////////////////////////////////
        this->char_textures->idleMod = 50;
        this->char_textures->jumpingMod = 20;
        this->char_textures->walkMod = 30;
        this->char_textures->runMod = 25;
        this->char_textures->attackRegMod = 11;
        this->char_textures->attackRegMod2 = 11;
        this->char_textures->fallingMod = 40;
        this->char_textures->attackRegJumpingMod=20;
        this->char_textures->attackSpecialOpenMod = 8;
        /////////////////////////////////////////////

        //Grounded attack/self hitbox offsets.
        ///////////////////////////////////
        this->right_x_offset_attack = 75;
        this->left_x_offset_attack = 5;
        this->right_x_offset_self = 45;
        this->left_x_offset_self = 15;
        ///////////////////////////////////

        //TODO://
        //These are for jumping attacks/self
        // Add up_y_offset_attack/self
        // Add down_y_offset_attack/self

        /////////////////////////////////////////////

        this->attackHitBoxOffsetHeight = -50;
        this->attackHitBoxOffsetY = 40;
        this->attackHitBoxOffsetWidth = -76;
        this->selfHitBoxOffsetHeight = -25;
        this->selfHitBoxOffsetY = 25;
        this->selfHitBoxOffsetWidth = -60;


        /////////////////////////////////////////////
        char_ptr->SetWidth(90);
        char_ptr->SetHeight(90);
        char_ptr = NULL;
        delete(char_ptr);
    }
}

void CharacterObject::Move(int Tick) {

    if(!this->isColliding) {
        if(this->isJumping || this->isFalling) {
            if (Tick % 35 == 0) {
                this->CalculateGravity();
            }
        }
        if(this->fluct_vely >=0) {
            this->isFalling = true;
            this->isJumping = false;
        }
    }
    if (Tick % 2 == 0) {
        this->posY += this->fluct_vely;
        this->posX += this->fluct_velx;
    }
}

void CharacterObject::CalculateGravity() {
    this->fluct_vely+=1;
}
