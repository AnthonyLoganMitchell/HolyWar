#ifndef MAINMENUOPTIONS_H
#define MAINMENUOPTIONS_H
#include "MenuTexture.h"
#include "MenuButton.h"

class MainMenuOptions
{
    public:
        MainMenuOptions(SDL_Renderer*);
        virtual ~MainMenuOptions();
        MenuTexture *menuBackground;
        MenuTexture *menuLogo;

        MenuButton  *menuStart;
        MenuButton  *menuBattle;
        MenuButton  *menuOptions;
};

#endif // MAINMENUOPTIONS_H
