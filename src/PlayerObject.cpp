#include "PlayerObject.h"
#include "PlayerCursor.h"

PlayerObject::PlayerObject(int x, int y)
{
    this->cursor = new PlayerCursor(x,y);
}

PlayerObject::~PlayerObject()
{
    //dtor
}
