#include "PlayerObject.h"


PlayerObject::PlayerObject(int id,int x,int y, SDL_Renderer* renderer)
{
    this->cursor = new PlayerCursor(x,y,renderer);
    this->isActive = false;
    this->ID = id;
    this->CharacterSelected = false;
    this->CharacterName="";
}

PlayerObject::~PlayerObject()
{
    //dtor
    SDL_GameControllerClose(this->controller);
    delete(this->cursor);
}
