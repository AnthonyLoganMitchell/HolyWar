/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterModules.h"

void CharacterModules::RunRegularAttackModule(CharacterObject* p,int CharScale,int Tick,SDL_Renderer* renderer)
{
    if(!p->isFalling && !p->isFalling)
    {
        if(p->regAttackCount == 0)
        {
            if(p->char_textures->GetFrameCount() >= p->char_textures->GetRegularAttackClipCount())
            {
                p->char_textures->SetFrameCount(0);
                p->isAttackingReg = false;
            }
        }
        else if(p->regAttackCount == 1)
        {
            if(p->char_textures->GetFrameCount() >= p->char_textures->GetRegularAttackClipCount2())
            {
                p->char_textures->SetFrameCount(0);
                p->isAttackingReg = false;
            }
        }

        if(p->regAttackCount == 0)
        {

            if (p->lastDirection == "LEFT")
            {
                p->char_textures->render(p->char_textures,renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips[p->char_textures->GetFrameCount()],"A",SDL_FLIP_NONE);
            }
            else if (p->lastDirection == "RIGHT")
            {
                p->char_textures->render(p->char_textures,renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips[p->char_textures->GetFrameCount()],"A",SDL_FLIP_HORIZONTAL);
            }
        }
        else if(p->regAttackCount == 1)
        {

            if (p->lastDirection == "LEFT")
            {
                p->char_textures->render(p->char_textures,renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips2[p->char_textures->GetFrameCount()],"A2",SDL_FLIP_NONE);
            }
            else if (p->lastDirection == "RIGHT")
            {
                p->char_textures->render(p->char_textures,renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips2[p->char_textures->GetFrameCount()],"A2",SDL_FLIP_HORIZONTAL);
            }
        }

        if(p->regAttackCount == 0)
        {
            if(Tick%p->char_textures->attackRegMod == 0)
            {
                p->char_textures->TickFrameCount();
            }
        }
        else if(p->regAttackCount == 1)
        {
            if(Tick%p->char_textures->attackRegMod2 == 0)
            {
                p->char_textures->TickFrameCount();
            }
        }
    }
    else
    {
        if(p->char_textures->GetFrameCount() >= p->char_textures->GetJumpingRegularAttackClipCount())
        {
            p->char_textures->SetFrameCount(0);
            p->isAttackingReg = false;
        }
        if (p->lastDirection == "LEFT")
        {
            p->char_textures->render(p->char_textures,renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->attackRegularJumpingClips[p->char_textures->GetFrameCount()],"JA",SDL_FLIP_NONE);
        }
        else if (p->lastDirection == "RIGHT")
        {
            p->char_textures->render(p->char_textures,renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->attackRegularJumpingClips[p->char_textures->GetFrameCount()],"JA",SDL_FLIP_HORIZONTAL);
        }
        if(Tick%p->char_textures->attackRegJumpingMod == 0)
        {
            p->char_textures->TickFrameCount();
        }
        p->Move(Tick);
    }
}

void CharacterModules::RunIdleModule(CharacterObject* p,int CharScale,int Tick,SDL_Renderer* renderer)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetIdleClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if(p->lastDirection == "LEFT")
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->idleClips[p->char_textures->GetFrameCount()],"I",SDL_FLIP_NONE);
    }
    else if (p->lastDirection == "RIGHT")
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->idleClips[p->char_textures->GetFrameCount()],"I",SDL_FLIP_HORIZONTAL);
    }

    if(Tick%p->char_textures->idleMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunMoveModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetMoveingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if(p->isMovingLeft)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->movementClips[p->char_textures->GetFrameCount()],"M",SDL_FLIP_NONE);
    }
    else if (p->isMovingRight)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->movementClips[p->char_textures->GetFrameCount()],"M",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->moveMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunFallingModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetFallingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if (p->lastDirection == "LEFT")
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    }
    else if (p->lastDirection == "RIGHT")
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->fallingMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunJumpingModule(CharacterObject *p, int CharScale, int Tick,SDL_Renderer* renderer)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetJumpingClipCount())
    {
        p->char_textures->SetFrameCount(p->char_textures->GetJumpingClipCount()/2);
    }
    if(p->isMovingLeft)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
    }
    else if(p->isMovingRight)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
    }
    else if(!p->isMovingLeft && !p->isMovingRight)
    {
        if(p->lastDirection == "RIGHT")
        {
            p->char_textures->render(p->char_textures,renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
        }
        else if(p->lastDirection == "LEFT")
        {
            p->char_textures->render(p->char_textures,renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
        }
    }
    if(Tick%p->char_textures->jumpingMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}
void CharacterModules::RunJumpFallTransitionModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer)
{
    if(p->char_textures->GetFrameCount() == p->char_textures->GetFallingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }

    if (p->isMovingLeft)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    }
    else if(p->isMovingRight)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    }
    else if(!p->isMovingLeft && !p->isMovingRight)
    {
        if (p->lastDirection == "LEFT")
        {
            p->char_textures->render(p->char_textures,renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
        }
        else if (p->lastDirection == "RIGHT")
        {
            p->char_textures->render(p->char_textures,renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
        }
    }
    if(Tick%p->char_textures->fallingMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}
