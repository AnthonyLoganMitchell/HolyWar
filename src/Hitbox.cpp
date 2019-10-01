#include "Hitbox.h"
//TODO:// Start here on hitboxes
Hitbox::Hitbox(int x,int y,int W,int H)
{
    //ctor
    this->direction="";
    this->posX=x;
    this->posY=y;
    this->xoffset=0;
    this->yoffset=0;
    this->isAlpha = false;
    this->isAttacking = false;
    this->isSelf = false;
    this->isColliding =false;
    this->isTangible = false;
    this->width = W;
    this->height = H;
    this->rect = new (SDL_Rect);
    this->rect->x=this->posX;
    this->rect->y=this->posY;
    this->rect->w=this->width;
    this->rect->h=this->height;
}

Hitbox::~Hitbox()
{

}

void Hitbox::RePosition(int X, int Y)
{
this->rect->x=X;
this->rect->y=Y;
}
int Hitbox::GetHeight()
{
 return this->height;
}

int Hitbox::GetWidth()
{
    return this->width;
}
