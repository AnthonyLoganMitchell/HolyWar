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
        CharacterTexture* char_ptr = new CharacterTexture(18,11,0,17,0,0,Name,renderer);
        this->char_textures = char_ptr;
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
