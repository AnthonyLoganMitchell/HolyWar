#ifndef LEVELPORTRAIT_H
#define LEVELPORTRAIT_H
#include <string>
#include "SDL.h"
#include "GeneralTexture.h"
class LevelPortrait
{
    public:
        LevelPortrait(std::string,std::string, std::string, SDL_Renderer*);
        GeneralTexture *level_avatar_small;
        GeneralTexture *level_avatar_big;
        std::string LevelName;
        virtual ~LevelPortrait();
};
#endif // LEVELPORTRAIT_H
