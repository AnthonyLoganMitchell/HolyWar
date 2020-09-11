#ifndef HITBOX_H
#define HITBOX_H
#include <string>
class SDL_Rect;
class Hitbox
{
    public:
        Hitbox(int,int,int,int);
        virtual ~Hitbox();
        int GetWidth();
        int GetHeight();
        void RePosition(int,int);

        std::string direction;
        int posX,posY;
        SDL_Rect* rect;
        bool isAttacking;
        bool isSelf;
        bool isAlpha;
        bool isColliding;
        bool isTangible;
        int width;
        int height;
    private:
};

#endif // HITBOX_H
