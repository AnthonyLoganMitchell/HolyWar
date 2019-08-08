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
    const int moveVelX = 12;
    const int moveVelY = 12;
    int posX, fluct_velx;
    int posY,fluct_vely;
    CharacterTexture* char_textures;
    int8_t health;
    std::string name;

};
#endif // CHARACTEROBJECT_H
