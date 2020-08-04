/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/

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
    int selfHitBoxOffXL;           ///
    int selfHitBoxOffXR;           ///
    int selfHitBoxOffY;            ///
    int selfHitBoxOffWidth;        ///
    int selfHitBoxOffHeight;       ///
    int attackHitBoxOffXL;         ///
    int attackHitBoxOffXR;         ///
    int attackHitBoxOffY;          ///
    int attackHitBoxOffWidth;      ///
    int attackHitBoxOffHeight;     ///
    //////////////////////////////////
    
    bool isJumping;
    bool isFalling;

    bool isWalking;
    bool isRunning;
    bool isMovingLeft;
    bool isMovingRight;

    bool isColliding;
    bool isAttackingReg;
    bool isAttackingStrong;
    bool isSpecialAttackOpen;

    bool isHoldingRegAttack;
    bool isHoldingStrongAttack;
    
    bool isHoldingSpecialOpen;
    bool isHoldingSpecialLeft;
    bool isHoldingSpecialRight;
    bool isHoldingSpecialUp;
    bool isHoldingSpecialDown;

    bool isHoldingDPadLeft;
    bool isHoldingDPadRight;
    bool isHoldingDPadUp;
    bool isHoldingDPadDown;

    bool wasRunningWhenJump;

    int  regAttackCount;
    int  StrongAttackCount;
    int  jumpBlock;


    //Timing variables
    ///////////////////////////////
    Uint32 regAttackLastPress;    //
    Uint32 strongAttackLastPress; //
    Uint32 specialAttackLastPress;//
    Uint32 leftLastPress;         //
    Uint32 rightLastPress;        //
    Uint32 upLastPress;           //
    Uint32 downLastPress;         //
    ///////////////////////////////
    std::string lastDirection;

    //TODO: Future bools to add.
    //isJumpingAttackStrong/isJumpingDownAttackReg/IsJumpingUpAttackReg
    //Have to create textures for each of these...

    int8_t health;
    std::string name;

};
#endif // CHARACTEROBJECT_H
