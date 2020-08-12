/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "Projectile.h"
#include "ProjectileTexture.h"
#include <string.h>
Projectile::Projectile(std::string owner, std::string proj_name, std::string owner_direction, int owner_pos_x, int owner_pos_y,SDL_Renderer* renderer) {
    this->owner_name = owner;
    this->base_texture = NULL;
    this->hit_texture = NULL;
    this->attackBox = NULL;
    this->links = NULL;
    this->projectile_name = proj_name;
    this->isGravity = false;
    this->hasLinks = false;
    this->isColliding = false;
    this->isInitialRun = false;
    this->chargeTime = 0;
    this->direction = owner_direction;
    this->fluct_velx = 0;
    this->fluct_vely = 0;
    this->posY = owner_pos_y;
    this->posX = owner_pos_x;
    this->right_x_offset= 0;
    this->left_x_offset = 0;    
    this->InitializeProjectile(this->projectile_name,renderer);
}

bool Projectile::InitializeProjectile(std::string name,SDL_Renderer* renderer) {
    if (name == "horus_beam") {
        this->links = new (std::vector<ProjectileLinks*>);
        this->hasLinks = true;
        //Horus has multidimensional texture. Each rect in Core::Projectiles has 7 clips.
        ProjectileTexture* proj_ptr = new ProjectileTexture(7,name,renderer);
        proj_ptr->ClipMod = 20;
        proj_ptr->isMultiDimTexture = true;
        this->base_texture = proj_ptr;
        //NOTE: Holy shit for future development. These Projectile pointers have to be made NULL before delete is called on them.
        proj_ptr=NULL;
        delete(proj_ptr);
    }
return true;
}
void Projectile::Move(int Tick) {


    if(this->hasLinks) {

    } else {
        if(!this->isColliding) {
            if(this->isGravity) {
                if (Tick % 35 == 0) {
                    this->CalculateGravity();
                }
            }
        }
        if (Tick % 2 == 0) {
            this->posY += this->fluct_vely;
            this->posX += this->fluct_velx;
        }
    }


}

void Projectile::CalculateGravity() {
    this->fluct_vely+=1;
}
