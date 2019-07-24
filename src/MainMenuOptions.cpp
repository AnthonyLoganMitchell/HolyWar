#include "MainMenuOptions.h"

MainMenuOptions::MainMenuOptions(SDL_Renderer* renderer)
{
    this->menuBackground = new GeneralTexture(1,"SplashBackground",renderer);
    this->menuLogo = new GeneralTexture(1,"MainMenuLogo",renderer);
    this->menuStart = new MenuButton(1,"MenuStartButton",renderer);
    this->menuBattle = new MenuButton(1,"MenuBattleButton",renderer);
    this->menuOptions = new MenuButton(1,"MenuOptionsButton",renderer);
    this->menuQuit = new MenuButton(1,"MenuQuitButton",renderer);
}

MainMenuOptions::~MainMenuOptions()
{
    //dtor
    this->menuBackground->Free_Texture();
    this->menuLogo->Free_Texture();
    this->menuStart->texture->Free_Texture();
    this->menuBattle->texture->Free_Texture();
    this->menuOptions->texture->Free_Texture();
    this->menuQuit->texture->Free_Texture();
}
