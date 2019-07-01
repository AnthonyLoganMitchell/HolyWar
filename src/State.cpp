#include "State.h"

State::State()
{
    //ctor
}

State::~State()
{
    //dtor
    delete(this->mainMenuOps);
}
