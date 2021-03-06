/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef LEVELPORTRAIT_H
#define LEVELPORTRAIT_H
#include <string>
#include "SDL.h"
#include "GeneralTexture.h"
#include <vector>
class LevelPortrait
{
    public:
        LevelPortrait(std::string,std::string, std::string, SDL_Renderer*);
        static std::vector<LevelPortrait*>* InitLevelPortraits(SDL_Renderer*);
        virtual ~LevelPortrait();

        GeneralTexture *level_avatar_small;
        GeneralTexture *level_avatar_big;
        std::string LevelName;
};
#endif // LEVELPORTRAIT_H
