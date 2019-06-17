#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include "MenuTexture.h"


class MenuButton
{
    public:
        MenuButton();
        MenuButton(int,std::string , SDL_Renderer*);
        virtual ~MenuButton();
        MenuTexture* texture;
        template<class T>
        static T (*func)();
        bool is_option;
        bool is_highlighted;
};

#endif // MENUBUTTON_H
