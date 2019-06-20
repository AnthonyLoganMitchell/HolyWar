#ifndef MAINMENUOPTIONS_H
#define MAINMENUOPTIONS_H
#include "GeneralTexture.h"
#include "MenuButton.h"

class MainMenuOptions
{
    public:
        MainMenuOptions(SDL_Renderer*);
        virtual ~MainMenuOptions();
        GeneralTexture *menuBackground;
        GeneralTexture *menuLogo;

        MenuButton  *menuStart;
        MenuButton  *menuBattle;
        MenuButton  *menuOptions;
        MenuButton  *menuQuit;
};

#endif // MAINMENUOPTIONS_H
