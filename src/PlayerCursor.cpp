#include "PlayerCursor.h"


PlayerCursor::PlayerCursor(int x,int y,SDL_Renderer* renderer)
{
    this->PosX = x;
    this->PosY = y;
    this->Texture = new GeneralTexture(1,"Pentagram",renderer);
}

PlayerCursor::~PlayerCursor()
{
    //dtor
}

void PlayerCursor::Move()
{
    this->PosX += this->VelX;
    this->PosY += this->VelY;

}
