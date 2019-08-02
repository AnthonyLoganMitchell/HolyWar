#ifndef CHARACTERPORTRAIT_H
#define CHARACTERPORTRAIT_H
#include "GeneralTexture.h"
#include "string"

class CharacterPortrait
{
    public:
        CharacterPortrait(int,std::string,std::string,SDL_Renderer*);
        virtual ~CharacterPortrait();
        GeneralTexture* avatar;
        std::string CharacterName;

    private:
};

#endif // CHARACTERPORTRAIT_H
