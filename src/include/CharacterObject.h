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
    void Move();
    void CalculateGravity();
    void InitializeHitBoxes(int);
    const int moveVelX = 13;
    const int moveVelY = 30;
    int posX, fluct_velx;
    int posY,fluct_vely;
    CharacterTexture* char_textures;
    //////////////////////////
    Hitbox* self;          ///
    Hitbox* attack;        /// {Hitbox objects and offsets}
    int  selfHitBoxOffset; ///
    int  attackHitBoxOffset;//
    //////////////////////////
    bool isJumping;
    bool isFalling;
    bool isMovingLeft;
    bool isMovingRight;
    bool isColliding;
    bool isAttackingReg;
    bool isHoldingReg;
    bool isHoldingStrong;
    int  regAttackCount;
    int  StrongAttackCount;
    int  jumpBlock;
    Uint32 regAttackLastPress;
    Uint32 strongAttackLastPress;
    std::string lastDirection;
    //TODO: Future bools to add.
    //isJumpingAttackReg/isJumpingAttackStrong/isJumpingDownAttack/IsJumpingUpAttack
    //Have to create textures for each of these...
    int8_t health;
    std::string name;

};
#endif // CHARACTEROBJECT_H
