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
