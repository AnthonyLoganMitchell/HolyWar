#include "PlayerCursor.h"


PlayerCursor::PlayerCursor(int x,int y,SDL_Renderer* renderer)
{
    this->PosX = x;
    this->PosY = y;

}


PlayerCursor::~PlayerCursor()
{
    //dtor
    this->Texture->Free_Texture();
}

void PlayerCursor::Move()
{
    this->PosX += this->VelX;
    this->PosY += this->VelY;

}
