#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "PlayerCursor.h"
#include "SDL.h"
#include "CharacterTexture.h"
class PlayerObject
{
    public:
        PlayerObject(int,int,int,SDL_Renderer*);
        virtual ~PlayerObject();
        PlayerCursor* cursor;
        SDL_GameController* controller;
        CharacterTexture* Character;
        int ID;
        std::string CharacterName;
        bool isActive;
        bool CharacterSelected;

};

#endif // PLAYEROBJECT_H
