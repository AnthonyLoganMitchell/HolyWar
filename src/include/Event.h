#ifndef EVENT_H_
#define EVENT_H_

class Event()
{
public:
    Event();
    virtual ~Event();
    SDL_Event *e;
private:
};
#endif // EVENT_H_
