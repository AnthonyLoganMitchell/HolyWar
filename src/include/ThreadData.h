#ifndef THREADDATA_H
#define THREADDATA_H
#include "SDL.h"
#include "vector"
#include "Interaction.h"
class ThreadData
{
public:
    virtual ~ThreadData();
    SDL_mutex* parse_mutex;
    std::vector<Interaction*> *interact;
    bool kill_thread;
};
#endif // THREADDATA_H
