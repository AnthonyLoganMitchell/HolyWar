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
    void CalculateGravity(Uint32);
    const int moveVelX = 15;
    const int moveVelY = 30;
    int posX, fluct_velx;
    int posY,fluct_vely;
    CharacterTexture* char_textures;
    bool isHoldingJump;
    bool isFalling;
    bool isColliding;
    Uint32 TimeHeld;
    int8_t health;
    std::string name;

};
#endif // CHARACTEROBJECT_H
