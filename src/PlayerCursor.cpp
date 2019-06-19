#include "PlayerCursor.h"

PlayerCursor::PlayerCursor(int x,int y)
{
    this->PosX = x;
    this->PosY = y;
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
