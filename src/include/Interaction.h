/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef INTERACTION_H
#define INTERACTION_H
#include <SDL.h>


class Interaction
{
    public:
        Interaction();
        ~Interaction();
        SDL_JoystickID controller_id;
        uint8_t button_event;
        uint8_t pressed;
    private:
};

#endif // INTERACTION_H
