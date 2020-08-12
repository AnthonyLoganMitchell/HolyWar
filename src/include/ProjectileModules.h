/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef PROJECTILEMODULES_H
#define PROJECTILEMODULES_H
#include "Projectile.h"
#include <vector>
class ProjectileModules {
    public:
    static void RunProjectiles(int,std::vector<Projectile*>*,SDL_Renderer*);
    private:

};
#endif