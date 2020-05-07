/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#ifndef   CHARACTERMODULES_H
#define   CHARACTERMODULES_H
#include "CharacterObject.h"
#include "Level.h"
#include <vector>
#include "PlayerObject.h"
class CharacterModules {

public:
    static void RunCharacters(int,int,int,std::vector<PlayerObject*>*,SDL_Renderer*);
    static void RunRegularAttackModule(CharacterObject*,int,int,SDL_Renderer*);
    static void RunIdleModule(CharacterObject*,int,int,SDL_Renderer*);
    static void RunMoveWalkModule(CharacterObject*,int,int,SDL_Renderer*);
    static void RunMoveRunningModule(CharacterObject*,int,int,SDL_Renderer*);
    static void RunFallingModule(CharacterObject*,int,int,SDL_Renderer*);
    static void RunJumpingModule(CharacterObject*,int,int,SDL_Renderer*);
    static void RunJumpFallTransitionModule(CharacterObject*,int,int,SDL_Renderer*);

    static void PositionHitBoxes(CharacterObject*,SDL_Renderer*);
    static void SetInitialCharacterPositions(Level*,std::vector<PlayerObject*>*);
private:

};
#endif
