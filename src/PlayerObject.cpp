#include "PlayerObject.h"


PlayerObject::PlayerObject(int x, int y,SDL_Renderer* renderer)
{
    this->cursor = new PlayerCursor(x,y,renderer);
}

PlayerObject::~PlayerObject()
{
    //dtor
}
