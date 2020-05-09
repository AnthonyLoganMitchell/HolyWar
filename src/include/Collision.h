/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///

#ifndef COLLISION_H
#define COLLISION_H
#include "Level.h"
#include "vector"
#include "PlayerObject.h"
#include "GeneralTexture.h"
#include "CharacterObject.h"
#include "PlayerCursor.h"
class Collision
{
public:
static void RunCollisionModule(int,int,int,Level*,std::vector<PlayerObject*>*);
static bool CollisionObjectCharacter(GeneralTexture*,int,CharacterObject*,int);
static bool CursorCollisionDetect(PlayerCursor*,SDL_Rect*);
private:

};
#endif // COLLISION_H
