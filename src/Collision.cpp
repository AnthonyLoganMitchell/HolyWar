/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///

#include "Collision.h"
void Collision::RunCollisionModule(int CharScale,int PlatformScale, int SCREEN_WIDTH, Level* stage,std::vector<PlayerObject*>* players)
{
    for(std::vector<GeneralTexture*>::iterator i = stage->platforms->begin(); i!= stage->platforms->end(); i++)
    {
        for(std::vector<PlayerObject*>::iterator j = players->begin(); j!= players->end(); j++)
        {
            if(Collision::CollisionObjectCharacter((*i),PlatformScale,(*j)->character,CharScale))
            {
                (*j)->character->isColliding = true;
                (*j)->character->isFalling = false;
                (*j)->character->isJumping = false;
                (*j)->character->fluct_vely =0;
                (*j)->character->posY = (*i)->GetYPos()- (*j)->character->char_textures->idleClips[0].h*CharScale;
                (*j)->character->jumpBlock = 0;

            }
            else if (!(*j)->character->isColliding)
            {
                (*j)->character->isFalling = true;
                (*j)->character->isColliding = false;
            }
            //Could cause issues in the future with combat collision momentum, need bools here
            //to determine weather or not the character has been struck by another player and is riding the momentum.
            //This is temporary hack to keep from going off screen.
            if((*j)->character->posX <= -((*j)->character->char_textures->idleClips[0].w))
            {
                (*j)->character->posX = SCREEN_WIDTH - ((*j)->character->char_textures->idleClips[0].w/2);
            }
            else if ((*j)->character->posX+(*j)->character->char_textures->idleClips[0].w >= SCREEN_WIDTH+(*j)->character->char_textures->idleClips[0].w)
            {
                (*j)->character->posX = 0-(*j)->character->char_textures->idleClips[0].w/2-35;
            }
        }
    }
}

bool Collision::CollisionObjectCharacter(GeneralTexture* A, int a_scale, CharacterObject* B, int b_scale)
{
    int rect_1_top = A->GetYPos();
    int rect_1_bottom = A->GetYPos()+A->GetHeight()*a_scale;
    int rect_1_left = A->GetXPos();
    int rect_1_right = A->GetXPos()+A->GetWidth()*a_scale;

    int rect_2_top = B->posY;
    int rect_2_bottom = B->posY+B->char_textures->idleClips[0].h*b_scale;
    int rect_2_left = B->posX;
    int rect_2_right = B->posX+B->char_textures->idleClips[0].w*b_scale;

    if (rect_1_bottom <= rect_2_top)
    {
        return false;
    }
    if (rect_1_top >= rect_2_bottom)
    {
        return false;
    }
    if (rect_1_right <= rect_2_left)
    {
        return false;
    }
    if (rect_1_left >= rect_2_right)
    {
        return false;
    }
    return true;
}

bool Collision::CursorCollisionDetect(PlayerCursor* A,SDL_Rect* B)
{
    int rect_1_top = A->PosY+2;
    int rect_1_bottom = A->PosY+A->Texture->GetHeight()+2;
    int rect_1_left = A->PosX+2;
    int rect_1_right = A->PosX+A->Texture->GetWidth()+2;

    int rect_2_top = B->y;
    int rect_2_bottom = B->y+B->h;
    int rect_2_left = B->x;
    int rect_2_right = B->x+B->w;

    if (rect_1_bottom <= rect_2_top)
    {
        return false;
    }
    if (rect_1_top >= rect_2_bottom)
    {
        return false;
    }
    if (rect_1_right <= rect_2_left)
    {
        return false;
    }
    if (rect_1_left >= rect_2_right)
    {
        return false;
    }
    return true;

}
