/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include <string>
#include "SDL.h"
class PlayerCursor;
class CharacterTexture;
class CharacterObject;
class SDL_Renderer;

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
