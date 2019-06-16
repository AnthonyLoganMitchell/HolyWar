#include "MenuButton.h"

MenuButton::MenuButton()
{
}

MenuButton::MenuButton(int scale,std::string name, SDL_Renderer* renderer)
{
    this->texture = new MenuTexture(scale,name);
    this->texture->loadMenuMedia(this->texture, renderer);
}

MenuButton::~MenuButton()
{
    this->texture->Free_Texture();
}
