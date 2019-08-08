#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "PlayerCursor.h"
#include "SDL.h"
#include "CharacterTexture.h"
#include "CharacterObject.h"
class PlayerObject
{
    public:
        PlayerObject(int,int,int,SDL_Renderer*);
        virtual ~PlayerObject();
        PlayerCursor* cursor;
        SDL_GameController* controller;
        CharacterObject* character;
        int ID;
        std::string CharacterName;
        bool isActive;
        bool CharacterSelected;
        bool levelSelected;
        bool isReady;

};

#endif // PLAYEROBJECT_H
