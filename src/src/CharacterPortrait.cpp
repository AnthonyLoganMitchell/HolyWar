#include "CharacterPortrait.h"

CharacterPortrait::CharacterPortrait()
{
    //ctor
    this->isHover = false;
    this->isSelected = false;

}

CharacterPortrait::~CharacterPortrait()
{
    this->avatar->Free_Texture();
    delete(this);
}
