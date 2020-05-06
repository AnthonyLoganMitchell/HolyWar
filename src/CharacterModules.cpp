/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterModules.h"


void CharacterModules::RunCharacters(int CharScale,int PlatformScale,int Tick,std::vector<PlayerObject*>* players, SDL_Renderer* renderer)
{
    for(std::vector<PlayerObject*>::iterator i = players->begin(); i!= players->end(); i++)
    {
        CharacterObject* p = (*i)->character;

        //Test block for visualizing hit boxes.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if((*i)->character->selfBox->isAlpha)
        {
            (*i)->character->selfBox->RePosition((*i)->character->posX+(*i)->character->selfHitBoxOffsetX,\
                                                 (*i)->character->posY+(*i)->character->selfHitBoxOffsetY);
            SDL_SetRenderDrawColor(renderer,0,0,0xFF,0);
            SDL_RenderDrawRect(renderer,(*i)->character->selfBox->rect);
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
        }
        if((*i)->character->attackBox->isAlpha)
        {
            (*i)->character->attackBox->RePosition((*i)->character->posX+(*i)->character->attackHitBoxOffsetX,\
                                                   (*i)->character->posY+(*i)->character->attackHitBoxOffsetY);
            SDL_SetRenderDrawColor(renderer,0xFF,0,0,0);
            SDL_RenderDrawRect(renderer,(*i)->character->attackBox->rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF );
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //This block will reposition hitboxs every iteration.
        //This will remain here for now.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        (*i)->character->selfBox->RePosition((*i)->character->posX+(*i)->character->selfHitBoxOffsetX,\
                                             (*i)->character->posY+(*i)->character->selfHitBoxOffsetY);
        (*i)->character->attackBox->RePosition((*i)->character->posX+(*i)->character->attackHitBoxOffsetX,\
                                               (*i)->character->posY+(*i)->character->attackHitBoxOffsetY);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //IDLE
        if(!p->isJumping && !p->isFalling && !p->isWalkingLeft && !p->isWalkingRight && !p->isRunningLeft && !p->isRunningRight && !p->isAttackingReg)
        {
            CharacterModules::RunIdleModule(p,CharScale,Tick,renderer);
        }
        //Walk/Run
        else if(!p->isJumping && !p->isFalling && (p->isWalkingLeft || p->isWalkingRight || p->isRunningLeft || p->isRunningRight) && !p->isAttackingReg)
        {
            //TODO: Add condition here the determines run or walk modules.
            CharacterModules::RunMoveWalkModule(p,CharScale,Tick,renderer);
        }
        //Jump
        else if((p->isJumping && !p->isFalling) && !p->isAttackingReg)
        {
            CharacterModules::RunJumpingModule(p,CharScale,Tick,renderer);
        }
        //FallTransition
        else if((p->isJumping && p->isFalling) && !p->isAttackingReg)
        {
            CharacterModules::RunJumpFallTransitionModule(p,CharScale,Tick,renderer);
        }
        //Fall
        else if((!p->isJumping && p->isFalling) && !p->isAttackingReg)
        {
            CharacterModules::RunFallingModule(p,CharScale,Tick,renderer);
        }
        //(up/down/left/right) Stationary/Jumping/Falling/Running Regular Attacks.
        else if(p->isAttackingReg)
        {
            CharacterModules::RunRegularAttackModule(p,CharScale,Tick,renderer);
        }
        //TODO:// Add Strong attack animation section here.




        //Logic for controlling hitbox offsets based on last direction faced
        if(p->lastDirection == "LEFT")
        {
            p->attackHitBoxOffsetX=p->left_x_offset_attack;
            p->selfHitBoxOffsetX = p->left_x_offset_self;
        }
        else if (p->lastDirection == "RIGHT")
        {
            p->attackHitBoxOffsetX = p->right_x_offset_attack;
            p->selfHitBoxOffsetX = p->right_x_offset_self;
        }
    }
}

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

void CharacterModules::RunMoveWalkModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetMoveingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if(p->isWalkingLeft)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->movementClips[p->char_textures->GetFrameCount()],"M",SDL_FLIP_NONE);
    }
    else if (p->isWalkingRight)
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
    if(p->isWalkingLeft || p->isRunningLeft)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
    }
    else if(p->isWalkingRight || p->isRunningRight)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
    }
    else if(!p->isWalkingLeft && !p->isWalkingRight && !p->isRunningLeft && !p->isRunningRight)
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

    if (p->isWalkingLeft || p->isRunningLeft)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    }
    else if(p->isWalkingRight || p->isRunningRight)
    {
        p->char_textures->render(p->char_textures,renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    }
    else if(!p->isWalkingLeft && !p->isWalkingRight && !p->isRunningLeft && !p->isRunningRight)
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

void CharacterModules::SetInitialCharacterPositions(Level* stage, std::vector<PlayerObject*>* players)
{
    for(std::vector<PlayerObject*>::iterator i = players->begin(); i!= players->end(); i++)
    {
        for (std::vector<GeneralTexture*>::iterator j = stage->platforms->begin(); j != stage->platforms->end(); j++)
        {
            if(!(*j)->isOccupied && (*j)->isStartingPlatform)
            {
                (*i)->character->posX = (*j)->xposition;
                (*i)->character->posY = (*j)->yposition - (*i)->character->char_textures->GetHeight();
                (*j)->isOccupied = true;
                break;
            }
            if(j == stage->platforms->end())
            {
                (*i)->character->posX = 0;
                (*i)->character->posY = 0;
                break;
            }
        }
    }
}
