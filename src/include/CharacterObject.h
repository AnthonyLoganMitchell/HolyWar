/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H
#include "CharacterTexture.h"
#include <string>
#include "Hitbox.h"
class CharacterObject
{
public:
    CharacterObject(std::string,int8_t,SDL_Renderer*);
    virtual ~CharacterObject();
    void InitializeCharacter(std::string Name,SDL_Renderer*);
    void Move(int);
    void CalculateGravity();
    void InitializeHitBoxes(int);
    const int moveVelX = 1;
    const int runMoveVelX = 2;
    const int moveVelY = 5;


    int posX, fluct_velx;
    int posY,fluct_vely;
    CharacterTexture* char_textures;
    //////////////////////////////////{Hitbox objects and offsets}
    Hitbox* selfBox;               ///
    Hitbox* attackBox;             ///
    int right_x_offset_attack;     ///
    int left_x_offset_attack;      ///
    int right_x_offset_self;       ///
    int left_x_offset_self;        ///
    int selfHitBoxOffsetX;         ///
    int selfHitBoxOffsetY;         ///
    int selfHitBoxOffsetWidth;     ///
    int selfHitBoxOffsetHeight;    ///
    int attackHitBoxOffsetX;       ///
    int attackHitBoxOffsetY;       ///
    int attackHitBoxOffsetWidth;   ///
    int attackHitBoxOffsetHeight;  ///
    //////////////////////////////////
    bool isJumping;
    bool isFalling;
    bool isMovingLeft;
    bool isMovingRight;
    bool isColliding;
    bool isAttackingReg;
    bool isHoldingReg;
    bool isHoldingStrong;
    bool isRunning;
    bool wasRunningWhenJump;

    int  regAttackCount;
    int  StrongAttackCount;
    int  jumpBlock;

    //Timing variables
    ///////////////////////////////
    Uint32 regAttackLastPress;   //
    Uint32 strongAttackLastPress;//
    Uint32 leftPress;            //
    Uint32 rightPress;           //
    Uint32 upPress;              //
    Uint32 downPress;            //
    ///////////////////////////////
    std::string lastDirection;
    //TODO: Future bools to add.
    //isJumpingAttackReg/isJumpingAttackStrong/isJumpingDownAttack/IsJumpingUpAttack
    //Have to create textures for each of these...
    int8_t health;
    std::string name;

};
#endif // CHARACTEROBJECT_H
