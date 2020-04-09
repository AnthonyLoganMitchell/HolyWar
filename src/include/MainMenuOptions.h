/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
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
