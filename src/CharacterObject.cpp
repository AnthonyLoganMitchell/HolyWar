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
}

CharacterObject::~CharacterObject()
{

}

void CharacterObject::InitializeCharacter(std::string Name,SDL_Renderer* renderer)
{
    if(Name == "Horus")
    {
        CharacterTexture* char_ptr = new CharacterTexture(9,0,0,0,0,0,Name,renderer);
        this->char_textures = char_ptr;
        char_ptr = NULL;
        delete(char_ptr);
    }
}

void CharacterObject::Move()
{
    this->posX += this->fluct_velx;
    this->posY += this->fluct_vely;
}
