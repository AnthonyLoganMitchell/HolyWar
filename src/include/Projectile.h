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
#include <vector>
#include <string>
class Hitbox;
class ProjectileTexture;
class ProjectileLinks;
class SDL_Renderer;
class Projectile {
    public:
        Projectile(std::string, std::string, std::string, int, int, SDL_Renderer*);
        ProjectileTexture* base_texture;
        ProjectileTexture* hit_texture;
        void Move(int);
        void CalculateGravity();
        bool InitializeProjectile(std::string,SDL_Renderer*);
        std::string owner_name;
        std::string projectile_name;
        std::string direction;
        std::vector<ProjectileLinks*>* links;
        bool isGravity;
        bool hasLinks;
        bool isColliding;
        bool isInitialRun;
        bool isActive;
        int chargeTime;
        int posX, fluct_velx;
        int posY,fluct_vely;
        int char_offset_x;
        int char_offset_y;
        int rightXOffset;
        int leftXOffset;     
        int upYOffset;
        int downYOffset; 
        int linkRate;
        Hitbox* attackBox;
    private:
};
#endif