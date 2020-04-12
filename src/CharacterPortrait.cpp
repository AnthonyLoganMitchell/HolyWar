/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
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
