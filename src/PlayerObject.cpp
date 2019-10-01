/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "PlayerObject.h"
#include "CharacterObject.h"

PlayerObject::PlayerObject(int id,int x,int y, SDL_Renderer* renderer)
{

    this->cursor = new PlayerCursor(x,y,renderer);
    this->isActive = false;
    this->ID = id;
    this->CharacterSelected = false;
    this->CharacterName="";
    this->isReady = false;
    this->levelSelected = false;

}

PlayerObject::~PlayerObject()
{
    //dtor
    SDL_GameControllerClose(this->controller);
    delete(this->cursor);
}


