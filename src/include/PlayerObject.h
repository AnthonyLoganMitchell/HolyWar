#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "PlayerCursor.h"
#include "SDL.h"



class PlayerObject
{
    public:
        PlayerObject();
        virtual ~PlayerObject();
        PlayerCursor* cursor;
        SDL_GameController* controller;
        //Character Texture

    protected:

    private:
};

#endif // PLAYEROBJECT_H
