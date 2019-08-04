#include "CharacterPortrait.h"

CharacterPortrait::CharacterPortrait(int clip_no,std::string name,std::string char_name,SDL_Renderer* renderer)
{
    //ctor
    this->avatar = new GeneralTexture(clip_no,name,renderer);
    this->CharacterName = char_name;
}

CharacterPortrait::~CharacterPortrait()
{
    this->avatar->Free_Texture();
}
