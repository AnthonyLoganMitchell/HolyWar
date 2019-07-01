#include "PlayerObject.h"


PlayerObject::PlayerObject()
{
}

PlayerObject::~PlayerObject()
{
    //dtor
    SDL_GameControllerClose(this->controller);
    delete(this->cursor);
}
