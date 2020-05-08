/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "MenuButton.h"

MenuButton::MenuButton() {
}

MenuButton::MenuButton(int scale,std::string name, SDL_Renderer* renderer) {
    this->texture = new GeneralTexture(scale,name,renderer);
    this->texture->loadMedia(this->texture, renderer);
    this->is_highlighted = false;
}

MenuButton::~MenuButton() {
    this->texture->Free_Texture();
}
