#ifndef EVENT_H_
#define EVENT_H_
#include "ThreadData.h"
#include "State.h"
#include "PlayerObject.h"
class Event
{
public:
   static void ParseEvents(ThreadData*,SDL_mutex*,State*,std::vector<PlayerObject*>*);

private:
};
#endif // EVENT_H_
