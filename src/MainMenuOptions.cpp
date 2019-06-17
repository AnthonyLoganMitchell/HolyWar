#include "MainMenuOptions.h"

MainMenuOptions::MainMenuOptions(SDL_Renderer* renderer)
{
    this->menuBackground = new MenuTexture(1,"SplashBackground",renderer);
    this->menuLogo = new MenuTexture(1,"MainMenuLogo",renderer);
    this->menuStart = new MenuButton(1,"MenuStartButton",renderer);
    this->menuBattle = new MenuButton(1,"MenuBattleButton",renderer);
    this->menuOptions = new MenuButton(1,"MenuOptionsButton",renderer);
    //this->menuOptions = new MenuButton(1,"MenuQuitButton",renderer);
}

MainMenuOptions::~MainMenuOptions()
{
    //dtor
}
