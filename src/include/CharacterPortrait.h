#ifndef CHARACTERPORTRAIT_H
#define CHARACTERPORTRAIT_H
#include "GeneralTexture.h"

class CharacterPortrait
{
    public:
        CharacterPortrait(int,std::string,SDL_Renderer*);
        virtual ~CharacterPortrait();
        GeneralTexture* avatar;
        bool isHover;
        bool isSelected;

    private:
};

#endif // CHARACTERPORTRAIT_H
