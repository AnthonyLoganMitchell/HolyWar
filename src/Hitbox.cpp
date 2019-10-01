#include "Hitbox.h"
//TODO:// Start here on hitboxes
Hitbox::Hitbox(int x,int y,int offsetx,int offsety)
{
    //ctor
    this->direction="";
    this->posX=x;
    this->posY=y;
    this->xoffset=offsetx;
    this->yoffset=offsety;
    this->isAlpha = false;
    this->isAttacking = false;
    this->isSelf = false;
    this->isColliding =false;
    this->rect = new (SDL_Rect);
}

Hitbox::~Hitbox()
{
    //dtor
}

int Hitbox::GetHeight()
{
 return this->height;
}

int Hitbox::GetWidth()
{
    return this->width;
}
