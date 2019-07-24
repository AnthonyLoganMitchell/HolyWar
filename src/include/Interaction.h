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
