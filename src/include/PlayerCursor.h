#ifndef PLAYERCURSOR_H
#define PLAYERCURSOR_H
#include "GeneralTexture.h"


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
