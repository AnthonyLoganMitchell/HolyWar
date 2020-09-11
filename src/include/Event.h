/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#ifndef EVENT_H_
#define EVENT_H_
#include <vector>
class ThreadData;
class State;
class PlayerObject;
class SDL_mutex;
class Event
{
public:
    static void ParseEvents(ThreadData*,SDL_mutex*,State*,std::vector<PlayerObject*>*);
    static int EventHandler(void*);
private:
};
#endif // EVENT_H_
