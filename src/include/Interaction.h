#ifndef INTERACTION_H
#define INTERACTION_H
#include <SDL.h>


class Interaction
{
    public:
        Interaction();
        ~Interaction();
        int controller_id;
        uint8_t button_event;
    private:
};

#endif // INTERACTION_H
