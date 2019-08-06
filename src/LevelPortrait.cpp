#include "LevelPortrait.h"

LevelPortrait::LevelPortrait(std::string small,std::string big, std::string level_name,SDL_Renderer* renderer)
{
    this->level_avatar_small = new GeneralTexture(1,small,renderer);
    this->level_avatar_big = new GeneralTexture(1,big,renderer);
    this->LevelName = level_name;
}
LevelPortrait::~LevelPortrait()
{
    this->level_avatar_small->Free_Texture();
    this->level_avatar_big->Free_Texture();
}
