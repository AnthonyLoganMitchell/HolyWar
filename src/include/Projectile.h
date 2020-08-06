/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Hitbox.h"
#include "ProjectileTexture.h"
#include <iostream>
class Projectile {
    public:
        Projectile(std::string, std::string);
        ProjectileTexture* base_texture;
        ProjectileTexture* moving_texture;
        ProjectileTexture* hit_texture;
        void Move(int);
        void CalculateGravity();
        bool InitializeProjectile(std::string);
        std::string owner_name;
        std::string projectile_name;
        bool isGravity;
        bool isHeadLink;
        bool hasLinks;
        bool isColliding;
        int chargeTime;
        int projMod;
        int posX, fluct_velx;
        int posY,fluct_vely;
        int right_x_offset;
        int left_x_offset;      
        Hitbox* attackBox;
    private:
};
#endif