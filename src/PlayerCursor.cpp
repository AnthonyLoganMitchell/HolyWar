/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "PlayerCursor.h"


PlayerCursor::PlayerCursor(int x,int y,SDL_Renderer* renderer) {
    this->PosX = x;
    this->PosY = y;
    this->default_x = x;
    this->default_y = y;
    this->isColliding = false;
    this->VelX =0;
    this->VelY =0;
    this->Texture = new GeneralTexture(1,"PentagramCursor",renderer);

}


PlayerCursor::~PlayerCursor() {
    //dtor
    this->Texture->Free_Texture();
}

void PlayerCursor::Move() {
    this->PosX += this->VelX;
    this->PosY += this->VelY;

}

void PlayerCursor::ResetPos() {

}
