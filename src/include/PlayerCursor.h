/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef PLAYERCURSOR_H
#define PLAYERCURSOR_H

class GeneralTexture;
class SDL_Renderer;
class PlayerCursor
{
    public:
        PlayerCursor(int,int,SDL_Renderer*);
        static const int CURSOR_VEL = 10;
        GeneralTexture* Texture;
        virtual ~PlayerCursor();
        void Move();
        void ResetPos();
        int VelX, VelY, default_x, default_y;
        int PosX, PosY;
        bool isColliding;


};

#endif // PLAYERCURSOR_H
