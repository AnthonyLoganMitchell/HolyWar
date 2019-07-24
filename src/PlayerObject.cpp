#include "PlayerObject.h"


PlayerObject::PlayerObject(int x,int y, SDL_Renderer* renderer)
{
    this->cursor = new PlayerCursor(x,y,renderer);
    this->isActive = false;
}

PlayerObject::~PlayerObject()
{
    //dtor
    SDL_GameControllerClose(this->controller);
    delete(this->cursor);
}
