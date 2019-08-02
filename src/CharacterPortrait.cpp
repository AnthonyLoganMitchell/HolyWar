#include "CharacterPortrait.h"

CharacterPortrait::CharacterPortrait(int clip_no,std::string name,SDL_Renderer* renderer)
{
    //ctor
    this->isHover = false;
    this->isSelected = false;
    this->avatar = new GeneralTexture(clip_no,name,renderer);
}

CharacterPortrait::~CharacterPortrait()
{
    this->avatar->Free_Texture();
    delete(this);
}
