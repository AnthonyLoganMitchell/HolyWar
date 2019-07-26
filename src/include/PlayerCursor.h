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
        int VelX, VelY;
        int PosX, PosY;


};

#endif // PLAYERCURSOR_H
