#include "State.h"
#include "MainMenuOptions.h"

State::State()
{
    //cto
}

State::~State()
{
    //dtor
    delete(this->mainMenuOps);
}
