/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef LEVEL_H
#define LEVEL_H
#include "vector"
#include "GeneralTexture.h"
#include "string"
#include "SDL.h"
class Level
{
public:
    Level(std::string,SDL_Renderer*);
    virtual ~Level();
    void InitLevelObjects(std::string,SDL_Renderer*);
    std::vector<GeneralTexture*> *textures;
    std::vector<GeneralTexture*> *platforms;

};
#endif // LEVEL_H
