#include "PlayerCursor.h"


PlayerCursor::PlayerCursor(int x,int y,SDL_Renderer* renderer)
{
    this->PosX = x;
    this->PosY = y;
    this->default_x = x;
    this->default_y = y;
    this->isColliding = false;
    this->VelX =0;
    this->VelY =0;
    this->Texture = new GeneralTexture(1,"PentagramCursor",renderer);

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

void PlayerCursor::ResetPos()
{

}
