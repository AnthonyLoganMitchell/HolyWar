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
    this->isHoldingJump = false;
    this->isFalling = true;
    this->TimeHeld = 0;
    this->isColliding = false;
}

CharacterObject::~CharacterObject()
{

}

void CharacterObject::InitializeCharacter(std::string Name,SDL_Renderer* renderer)
{
    if(Name == "Horus")
    {
        CharacterTexture* char_ptr = new CharacterTexture(9,0,0,17,0,0,Name,renderer);
        this->char_textures = char_ptr;
        char_ptr = NULL;
        delete(char_ptr);
    }
}

void CharacterObject::Move()
{
    Uint32 prev = this->TimeHeld;
    Uint32 now = SDL_GetTicks() - prev;
    if(this->isHoldingJump || this->isFalling)
    {
        this->CalculateGravity(now);
        this->posY += this->fluct_vely;
    }
    this->posX += this->fluct_velx;
}

void CharacterObject::CalculateGravity(Uint32 time)
{
    this->fluct_vely+=2;
}
