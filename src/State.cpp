#include "State.h"
#include "MainMenuOptions.h"

State::State()
{
    //cto
    this->levelName="";
}

State::~State()
{
    //dtor
    delete(this->mainMenuOps);
}
