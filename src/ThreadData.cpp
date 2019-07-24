#include "ThreadData.h"

ThreadData::~ThreadData()
{
    SDL_DestroyMutex(this->parse_mutex);
    delete(this->interact);
}
