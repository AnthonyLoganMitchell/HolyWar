#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include "GeneralTexture.h"


class MenuButton
{
    public:
        MenuButton();
        MenuButton(int,std::string , SDL_Renderer*);
        virtual ~MenuButton();
        GeneralTexture* texture;
        //template<class T>
        //static T (*func)();
        bool is_highlighted;
};

#endif // MENUBUTTON_H
