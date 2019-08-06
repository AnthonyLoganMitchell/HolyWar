#include "CharacterPortrait.h"

CharacterPortrait::CharacterPortrait(int clip_no,std::string id_name,std::string char_name,SDL_Renderer* renderer)
{
    //ctor
    this->avatar = new GeneralTexture(clip_no,id_name,renderer);
    this->CharacterName = char_name;
}

CharacterPortrait::~CharacterPortrait()
{
    this->avatar->Free_Texture();
}
