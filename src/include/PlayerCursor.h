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

    protected:

    private:
         int PosX, PosY;
         int VelX, VelY;
};

#endif // PLAYERCURSOR_H
