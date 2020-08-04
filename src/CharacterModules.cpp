/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterModules.h"


void CharacterModules::RunCharacters(int CharScale,int PlatformScale,int Tick,std::vector<PlayerObject*>* players, SDL_Renderer* renderer) {
    for(std::vector<PlayerObject*>::iterator i = players->begin(); i!= players->end(); i++) {
        CharacterObject* p = (*i)->character;

        //IDLE
        if(!p->isJumping && !p->isFalling && !p->isMovingLeft  && !p->isMovingRight && !p->isAttackingReg) {
            CharacterModules::RunIdleModule(p,CharScale,Tick,renderer);
        }
        //Walk/Run
        else if(!p->isJumping && !p->isFalling && (p->isMovingLeft || p->isMovingRight) && !p->isAttackingReg) {
            if (p->isWalking) {
                CharacterModules::RunMoveWalkModule(p,CharScale,Tick,renderer);
            } else if (p->isRunning) {
                CharacterModules::RunMoveRunningModule(p,CharScale,Tick,renderer);
            }
        }
        //Jump
        else if((p->isJumping && !p->isFalling) && !p->isAttackingReg) {
            CharacterModules::RunJumpingModule(p,CharScale,Tick,renderer);
        }
        //FallTransition
        else if((p->isJumping && p->isFalling) && !p->isAttackingReg) {
            CharacterModules::RunJumpFallTransitionModule(p,CharScale,Tick,renderer);
        }
        //Fall
        else if((!p->isJumping && p->isFalling) && !p->isAttackingReg) {
            CharacterModules::RunFallingModule(p,CharScale,Tick,renderer);
        }
        //(up/down/left/right) Stationary/Jumping/Falling/Running Regular Attacks.
        else if(p->isAttackingReg) {
            CharacterModules::RunRegularAttackModule(p,CharScale,Tick,renderer);
        }
        //TODO:// Add Strong attack animation section here.

        //TODO:// Special attacks animations
        else if (p->isSpecialAttackOpen) {
            //TODO:Actually call RunSpecialOpenAttack
            CharacterModules::RunSpecialOpenAttack(p,CharScale,Tick,renderer);
        }

        //TODO:// Damage taken animations
        //Position Character HitBoxes.
        CharacterModules::PositionHitBoxes(p,renderer);
    }
}

void CharacterModules::RunSpecialOpenAttack(CharacterObject* p,int CharScale, int Tick, SDL_Renderer* renderer) {
    if(!p->isFalling && !p->isJumping) {
        if(p->char_textures->GetFrameCount() > p->char_textures->GetSpecialOpenAttackClipCount() && !p->isHoldingSpecialOpen) {
            p->char_textures->SetFrameCount(0);
        }
        



    } else {
        //We might allow jumping/falling special attacks one day...
    }
}



void CharacterModules::RunRegularAttackModule(CharacterObject* p,int CharScale,int Tick,SDL_Renderer* renderer) {
    if(p->regAttackCount == 0) {
        if(p->char_textures->GetFrameCount() > p->char_textures->GetRegularAttackClipCount()) {
            p->char_textures->SetFrameCount(0);
            p->isAttackingReg = false;
        }
    } else if(p->regAttackCount == 1) {
        if(p->char_textures->GetFrameCount() > p->char_textures->GetRegularAttackClipCount2()) {
            p->char_textures->SetFrameCount(0);
            p->isAttackingReg = false;
        }
    }
    if(!p->isFalling && !p->isJumping) {

        if(p->regAttackCount == 0) {

            if (p->lastDirection == "LEFT") {
                p->char_textures->render(renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips[p->char_textures->GetFrameCount()],"A",SDL_FLIP_NONE);
            } else if (p->lastDirection == "RIGHT") {
                p->char_textures->render(renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips[p->char_textures->GetFrameCount()],"A",SDL_FLIP_HORIZONTAL);
            }
        } else if(p->regAttackCount == 1) {

            if (p->lastDirection == "LEFT") {
                p->char_textures->render(renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips2[p->char_textures->GetFrameCount()],"A2",SDL_FLIP_NONE);
            } else if (p->lastDirection == "RIGHT") {
                p->char_textures->render(renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips2[p->char_textures->GetFrameCount()],"A2",SDL_FLIP_HORIZONTAL);
            }
        }

        if(p->regAttackCount == 0) {
            if(Tick%p->char_textures->attackRegMod == 0) {
                p->char_textures->TickFrameCount();
            }
        } else if(p->regAttackCount == 1) {
            if(Tick%p->char_textures->attackRegMod2 == 0) {
                p->char_textures->TickFrameCount();
            }
        }
    } else {
        if(p->char_textures->GetFrameCount() >= p->char_textures->GetJumpingRegularAttackClipCount()) {
            p->char_textures->SetFrameCount(0);
            p->isAttackingReg = false;
        }
        if (p->lastDirection == "LEFT") {
            p->char_textures->render(renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->attackRegularJumpingClips[p->char_textures->GetFrameCount()],"JA",SDL_FLIP_NONE);
        } else if (p->lastDirection == "RIGHT") {
            p->char_textures->render(renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->attackRegularJumpingClips[p->char_textures->GetFrameCount()],"JA",SDL_FLIP_HORIZONTAL);
        }
        if(Tick%p->char_textures->attackRegJumpingMod == 0) {
            p->char_textures->TickFrameCount();
        }
        p->Move(Tick);
    }
}

void CharacterModules::RunIdleModule(CharacterObject* p,int CharScale,int Tick,SDL_Renderer* renderer) {
    if(p->char_textures->GetFrameCount() > p->char_textures->GetIdleClipCount()) {
        p->char_textures->SetFrameCount(0);
    }
    if(p->lastDirection == "LEFT") {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->idleClips[p->char_textures->GetFrameCount()],"I",SDL_FLIP_NONE);
    } else if (p->lastDirection == "RIGHT") {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->idleClips[p->char_textures->GetFrameCount()],"I",SDL_FLIP_HORIZONTAL);
    }

    if(Tick%p->char_textures->idleMod == 0) {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunMoveWalkModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer) {
    if(p->char_textures->GetFrameCount() > p->char_textures->GetWalkingClipCount()) {
        p->char_textures->SetFrameCount(0);
    }
    if(p->isMovingLeft) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->walkingClips[p->char_textures->GetFrameCount()],"W",SDL_FLIP_NONE);
    } else if (p->isMovingRight) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->walkingClips[p->char_textures->GetFrameCount()],"W",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->walkMod == 0) {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunMoveRunningModule(CharacterObject* p, int CharScale, int Tick, SDL_Renderer* renderer) {
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetRunningClipCount()) {
        p->char_textures->SetFrameCount(0);
    }
    if(p->isMovingLeft) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->runningClips[p->char_textures->GetFrameCount()],"R",SDL_FLIP_NONE);
    } else if (p->isMovingRight) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->runningClips[p->char_textures->GetFrameCount()],"R",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->runMod == 0) {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunFallingModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer) {
    if(p->char_textures->GetFrameCount() > p->char_textures->GetFallingClipCount()) {
        p->char_textures->SetFrameCount(0);
    }
    if (p->lastDirection == "LEFT") {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    } else if (p->lastDirection == "RIGHT") {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->fallingMod == 0) {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::RunJumpingModule(CharacterObject *p, int CharScale, int Tick,SDL_Renderer* renderer) {
    if(p->char_textures->GetFrameCount() > p->char_textures->GetJumpingClipCount()) {
        p->char_textures->SetFrameCount(p->char_textures->GetJumpingClipCount()/2);
    }
    if(p->isMovingLeft) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
    } else if(p->isMovingRight) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
    } else if(!p->isMovingLeft && !p->isMovingRight) {
        if(p->lastDirection == "RIGHT") {
            p->char_textures->render(renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
        } else if(p->lastDirection == "LEFT") {
            p->char_textures->render(renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
        }
    }
    if(Tick%p->char_textures->jumpingMod == 0) {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}
void CharacterModules::RunJumpFallTransitionModule(CharacterObject* p, int CharScale, int Tick,SDL_Renderer* renderer) {
    if(p->char_textures->GetFrameCount() == p->char_textures->GetFallingClipCount()) {
        p->char_textures->SetFrameCount(0);
    }

    if (p->isMovingLeft) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    } else if(p->isMovingRight) {
        p->char_textures->render(renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    } else if(!p->isMovingLeft && !p->isMovingRight) {
        if (p->lastDirection == "LEFT") {
            p->char_textures->render(renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
        } else if (p->lastDirection == "RIGHT") {
            p->char_textures->render(renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
        }
    }
    if(Tick%p->char_textures->fallingMod == 0) {
        p->char_textures->TickFrameCount();
    }
    p->Move(Tick);
}

void CharacterModules::SetInitialCharacterPositions(Level* stage, std::vector<PlayerObject*>* players) {
    for(std::vector<PlayerObject*>::iterator i = players->begin(); i!= players->end(); i++) {
        for (std::vector<GeneralTexture*>::iterator j = stage->platforms->begin(); j != stage->platforms->end(); j++) {
            if(!(*j)->isOccupied && (*j)->isStartingPlatform) {
                (*i)->character->posX = (*j)->xposition;
                (*i)->character->posY = (*j)->yposition - (*i)->character->char_textures->GetHeight();
                (*j)->isOccupied = true;
                break;
            }
            if(j == stage->platforms->end()) {
                (*i)->character->posX = 0;
                (*i)->character->posY = 0;
                break;
            }
        }
    }
}

void CharacterModules::PositionHitBoxes(CharacterObject* p,SDL_Renderer* renderer) {
    //Logic for controlling hitbox offsets based on last direction faced
    if(p->lastDirection == "LEFT") {
        p->selfBox->RePosition(p->posX+p->selfHitBoxOffXL,p->posY+p->selfHitBoxOffY);
        p->attackBox->RePosition(p->posX+p->attackHitBoxOffXL,p->posY+p->attackHitBoxOffY);
    } else if (p->lastDirection == "RIGHT") {
        p->selfBox->RePosition(p->posX+p->selfHitBoxOffXR,p->posY+p->selfHitBoxOffY);
        p->attackBox->RePosition(p->posX+p->attackHitBoxOffXR,p->posY+p->attackHitBoxOffY);
    }
    //This block will reposition hitboxs every iteration.
    //This will remain here for now.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    p->selfBox->RePosition(p->posX+p->selfHitBoxOffsetX,p->posY+p->selfHitBoxOffsetY);
    p->attackBox->RePosition(p->posX+p->attackHitBoxOffsetX,p->posY+p->attackHitBoxOffsetY);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Test block for visualizing hit boxes for testing.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(p->selfBox->isAlpha) {
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,0);
        SDL_RenderDrawRect(renderer,p->selfBox->rect);
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
    }
    if(p->attackBox->isAlpha) {
        SDL_SetRenderDrawColor(renderer,0xFF,0,0,0);
        SDL_RenderDrawRect(renderer,p->attackBox->rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
