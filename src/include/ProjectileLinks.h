/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef PROJECTILELINKS_H
#define PROJECTILELINKS_H
class ProjectileLinks {
    public:
        ProjectileLinks(int,int,int,int);
        ~ProjectileLinks();
        int xPos;
        int yPos;
        int rectIndex;
        int linkTick;
    private:
};
#endif