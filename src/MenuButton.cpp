#include "MenuButton.h"

MenuButton::MenuButton()
{
}

MenuButton::MenuButton(int scale,std::string name, SDL_Renderer* renderer)
{
    this->texture = new MenuTexture(scale,name,renderer);
    this->texture->loadMenuMedia(this->texture, renderer);
    this->is_highlighted = false;
}

MenuButton::~MenuButton()
{
    this->texture->Free_Texture();
}
