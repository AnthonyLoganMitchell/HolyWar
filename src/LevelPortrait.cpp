/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "LevelPortrait.h"
#include "SDL.h"
#include "GeneralTexture.h"

LevelPortrait::LevelPortrait(std::string small,std::string big, std::string level_name,SDL_Renderer* renderer) {
    this->level_avatar_small = new GeneralTexture(1,small,renderer);
    this->level_avatar_big = new GeneralTexture(1,big,renderer);
    this->LevelName = level_name;
}

std::vector<LevelPortrait*>* LevelPortrait::InitLevelPortraits(SDL_Renderer* renderer) {
    std::vector<LevelPortrait*> *lp_vec = new std::vector<LevelPortrait*>;
    LevelPortrait *lp = new LevelPortrait("MountainPrototypeSmall","MountainPrototypeBig","mountain_top",renderer);
    lp_vec->push_back(lp);
    lp = NULL;
    delete(lp);
    if (sizeof(lp_vec)>0) {
        return lp_vec;
    }
    return NULL;
}

LevelPortrait::~LevelPortrait() {
    this->level_avatar_small->Free_Texture();
    this->level_avatar_big->Free_Texture();
}
