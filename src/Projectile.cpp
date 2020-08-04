/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "Projectile.h"
#include <string.h>
Projectile::Projectile(std::string owner, std::string proj_name) {
    this->owner_name = owner;
    this->moving_texture = NULL;
    this->hit_texture = NULL;
    this->attackBox = NULL;
    this->projectile_name = proj_name;
    this->isGravity = false;
    this->isHeadLink = false;
    this->hasLinks = false;
    this->chargeTime = 0;
    //Mod always has to be > 0
    this->projMod = 1;
    this->posX = 0;
    this->fluct_velx = 0;
    this->posY = 0;
    this->fluct_vely = 0;
    this->right_x_offset= 0;
    this->left_x_offset = 0;    
}

bool Projectile::InitializeProjectile() {
return true;
}
void Projectile::Move(int Tick) {

}