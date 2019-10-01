/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
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
