#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H
#include "CharacterTexture.h"
#include <string>
class CharacterObject
{
public:
    CharacterObject(std::string,int8_t,SDL_Renderer*);
    virtual ~CharacterObject();
    void InitializeCharacter(std::string Name,SDL_Renderer*);
    void Move();
    void CalculateGravity();
    const int moveVelX = 13;
    const int moveVelY = 30;
    int posX, fluct_velx;
    int posY,fluct_vely;
    CharacterTexture* char_textures;
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
