#ifndef THREADDATA_H
#define THREADDATA_H
class ThreadData
{
public:
    SDL_mutex* parse_mutex;
    std::vector<Interaction*> *interact;
    bool kill_thread;
};
#endif // THREADDATA_H
