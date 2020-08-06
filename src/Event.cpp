/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "Event.h"

void Event::ParseEvents(ThreadData* data,SDL_mutex* parse_mutex,State* state,std::vector<PlayerObject*>* players) {
    if (SDL_LockMutex(parse_mutex) == 0 && data->interact->size() > 0) {
        //On Main Menu states//
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (!state->transition) {
            if (state->onMainMenuStart) {
                for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++) {
                    if((*i)->button_event == SDL_CONTROLLER_BUTTON_START) {
                        state->onMainMenuStart =false;
                        state->onOptionSelection = true;
                        state->mainMenuOps->menuBattle->is_highlighted = true;
                        state->mainMenuOps->menuOptions->is_highlighted = false;
                    }
                }

            } else if (state->onOptionSelection) {
                for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++) {
                    if((*i)->button_event == SDL_CONTROLLER_BUTTON_B) {
                        state->onMainMenuStart = true;
                        state->onOptionSelection = false;
                        state->mainMenuOps->menuStart->is_highlighted = true;
                        state->mainMenuOps->menuBattle->is_highlighted = false;
                        state->mainMenuOps->menuOptions->is_highlighted = false;
                        state->mainMenuOps->menuQuit->is_highlighted = false;

                    } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED) {
                        if(state->mainMenuOps->menuBattle->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = false;
                            state->mainMenuOps->menuOptions->is_highlighted= true;
                            state->mainMenuOps->menuQuit->is_highlighted = false;
                        } else if(state->mainMenuOps->menuOptions->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = false;
                            state->mainMenuOps->menuOptions->is_highlighted= false;
                            state->mainMenuOps->menuQuit->is_highlighted = true;
                        } else if(state->mainMenuOps->menuQuit->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = false;
                            state->mainMenuOps->menuOptions->is_highlighted= false;
                            state->mainMenuOps->menuQuit->is_highlighted = true;
                        }
                    } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED) {
                        if(state->mainMenuOps->menuBattle->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = true;
                            state->mainMenuOps->menuOptions->is_highlighted= false;
                            state->mainMenuOps->menuQuit->is_highlighted = false;
                        } else if(state->mainMenuOps->menuOptions->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = true;
                            state->mainMenuOps->menuOptions->is_highlighted= false;
                            state->mainMenuOps->menuQuit->is_highlighted = false;
                        } else if(state->mainMenuOps->menuQuit->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = false;
                            state->mainMenuOps->menuOptions->is_highlighted= true;
                            state->mainMenuOps->menuQuit->is_highlighted = false;
                        }
                    } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED) {
                        if(state->mainMenuOps->menuBattle->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = true;
                            state->mainMenuOps->menuOptions->is_highlighted= false;
                            state->mainMenuOps->menuQuit->is_highlighted = false;
                            state->transition=true;


                        } else if(state->mainMenuOps->menuOptions->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = false;
                            state->mainMenuOps->menuOptions->is_highlighted= true;
                            state->mainMenuOps->menuQuit->is_highlighted = false;

                        } else if(state->mainMenuOps->menuQuit->is_highlighted) {
                            state->mainMenuOps->menuBattle->is_highlighted = false;
                            state->mainMenuOps->menuOptions->is_highlighted= false;
                            state->mainMenuOps->menuQuit->is_highlighted = true;
                            state->quit_program = true;
                        }
                    }
                }
            }
            //CharacterSelection stat//
            /////////////////////////////////////////////////////////////////////////////////////////
            else if (state->onCharacterSelection) {
                for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++) {
                    for(std::vector<PlayerObject*>::iterator j = players->begin(); j!= players->end(); j++) {
                        if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED) {
                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = (*j)->cursor->CURSOR_VEL;
                            }


                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = -(*j)->cursor->CURSOR_VEL;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX = -(*j)->cursor->CURSOR_VEL;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX = (*j)->cursor->CURSOR_VEL;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_START && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller && (*j)->isActive == false) {
                                (*j)->isActive =true;
                            }
                            for(std::vector<PlayerObject*>::iterator j = players->begin(); j!= players->end(); j++) {
                                if(!(*j)->isReady && (*j)->isActive) {
                                    break;
                                }
                                if(j == players->end()-1 && (*j)->isReady) {
                                    state->onCharacterSelection=false;
                                    state->onLevelSelection = true;
                                }
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED) {
                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->CharacterSelected = true;
                            }
                        }
                        //SDL_RELEASED

                        else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = 0;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = 0;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX = 0;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX =0;
                            }

                        }
                    }

                }
            }
            //LevelSelection state//
            /////////////////////////////////////////////////////////////////////////////////////////
            else if (state->onLevelSelection) {
                for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++) {
                    for(std::vector<PlayerObject*>::iterator j = players->begin(); j!= players->end(); j++) {
                        if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED) {
                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = (*j)->cursor->CURSOR_VEL;
                            }


                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = -(*j)->cursor->CURSOR_VEL;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX = -(*j)->cursor->CURSOR_VEL;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX = (*j)->cursor->CURSOR_VEL;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_START && (*i)->pressed == SDL_PRESSED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller && (*j)->isActive == false) {
                                (*j)->isActive =true;
                            }
                            if (state->levelName!="") {
                                state->onLevelSelection =false;
                                state->onRunningMatch = true;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED) {
                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->levelSelected = true;
                            }
                        }
                        //SDL_RELEASED

                        else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = 0;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelY = 0;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX = 0;
                            }

                        } else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_RELEASED) {

                            if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                (*j)->cursor->VelX =0;
                            }

                        }
                    }

                }
            }
            //RunningMatch state//
            /////////////////////////////////////////////////////////////////////////////////////////
            else if (state->onRunningMatch) {
                for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++) {
                    for(std::vector<PlayerObject*>::iterator j = players->begin(); j!= players->end(); j++) {
                        switch((*i)->button_event) {
                            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                                if ((*i)->pressed == SDL_PRESSED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        
                                    }
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        
                                    }
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_DPAD_UP: 
                                if ((*i)->pressed == SDL_PRESSED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        
                                    }
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        
                                    }
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                                if ((*i)->pressed == SDL_PRESSED) {
                                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                            Uint32 now = SDL_GetTicks();
                                            if (now -(*j)->character->leftLastPress < 250) {
                                                (*j)->character->isRunning = true;
                                                (*j)->character->isMovingLeft = true;
                                                (*j)->character->isWalking = false;
                                                (*j)->character->isAttackingReg = false;
                                                (*j)->character->lastDirection = "LEFT";
                                                (*j)->character->fluct_velx = -(*j)->character->runMoveVelX;
                                                (*j)->character->char_textures->SetFrameCount(0);
                                                (*j)->character->leftLastPress = now;

                                             } else {
                                                (*j)->character->isRunning = false;
                                                (*j)->character->isMovingLeft = true;
                                                (*j)->character->isWalking = true;
                                                (*j)->character->isAttackingReg = false;
                                                (*j)->character->lastDirection = "LEFT";
                                                (*j)->character->fluct_velx = -(*j)->character->moveVelX;
                                                (*j)->character->char_textures->SetFrameCount(0);
                                                (*j)->character->leftLastPress = now;
                                            }
                                        }
                                    
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        (*j)->character->isMovingLeft = false;
                                        (*j)->character->isWalking = false;
                                        (*j)->character->isRunning = false;
                                        (*j)->character->fluct_velx = 0;
                                    }
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                                if ((*i)->pressed == SDL_PRESSED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        Uint32 now = SDL_GetTicks();
                                        if (now -(*j)->character->rightLastPress < 250) {
                                            (*j)->character->isRunning = true;
                                            (*j)->character->isMovingRight = true;
                                            (*j)->character->isWalking = false;
                                            (*j)->character->isAttackingReg = false;
                                            (*j)->character->lastDirection = "RIGHT";
                                            (*j)->character->fluct_velx = (*j)->character->runMoveVelX;
                                            (*j)->character->char_textures->SetFrameCount(0);
                                            (*j)->character->rightLastPress = now;

                                        } else {
                                            (*j)->character->isRunning = false;
                                            (*j)->character->isMovingRight = true;
                                            (*j)->character->isWalking = true;
                                            (*j)->character->isAttackingReg = false;
                                            (*j)->character->lastDirection = "RIGHT";
                                            (*j)->character->fluct_velx = (*j)->character->moveVelX;
                                            (*j)->character->char_textures->SetFrameCount(0);
                                            (*j)->character->rightLastPress = now;

                                        }
                                        
                                    }
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        (*j)->character->isMovingRight = false;
                                        (*j)->character->isWalking = false;
                                        (*j)->character->isRunning = false;
                                        (*j)->character->fluct_velx = 0;
                                    }
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_START:
                                if ((*i)->pressed == SDL_PRESSED) {
                                    state->quit_program=true;
                                    state->onRunningMatch=false;
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_A:
                                if ((*i)->pressed == SDL_PRESSED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        if((!(*j)->character->isAttackingReg && !(*j)->character->isHoldingRegSmashOpen)) {
                                            (*j)->character->char_textures->SetFrameCount(0);
                                            Uint32 now = SDL_GetTicks();
                                            if ( (now - (*j)->character->regAttackLastPress) <= 750) {
                                                (*j)->character->regAttackCount++;
                                                (*j)->character->regAttackLastPress = now;
                                            } else {
                                                (*j)->character->regAttackCount = 0;
                                                (*j)->character->regAttackLastPress = now;
                                            }
                                            //TODO:// This is a temporary block To reset counter if it goes over amount Attack count.
                                            ////////////////////////////////////////////
                                            if ((*j)->character->regAttackCount > 1) { //
                                                                                       //
                                                (*j)->character->regAttackCount =0;    //
                                            }                                          //
                                            ////////////////////////////////////////////
                                            (*j)->character->isAttackingReg = true;
                                        }
                                        //(*j)->character->char_textures->SetFrameCount(0); 
                                    }
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        
                                    }
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_B:
                                if ((*i)->pressed == SDL_PRESSED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        if((*j)->character->jumpBlock < 2) {
                                            (*j)->character->isJumping = true;
                                            (*j)->character->isColliding = false;
                                            (*j)->character->isFalling = false;
                                            (*j)->character->isAttackingReg = false;
                                            (*j)->character->char_textures->SetFrameCount(0);
                                            (*j)->character->fluct_vely = -(*j)->character->moveVelY;
                                            (*j)->character->jumpBlock++;
                                        }
                                    }
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        (*j)->character->isJumping = false;
                                        if(!(*j)->character->isColliding) {
                                            (*j)->character->isFalling = true;
                                        }
                                    }
                                }
                            break;
                            case SDL_CONTROLLER_BUTTON_X:
                                if ((*i)->pressed == SDL_PRESSED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        Uint32 now = SDL_GetTicks();
                                        if ((now - (*j)->character->leftLastPress) < 250) {
                                            (*j)->character->isHoldingSpecialLeft = true;
                                        } else if ((now - (*j)->character->rightLastPress) < 250) {
                                            (*j)->character->isHoldingSpecialRight = true;
                                        } else if ((now - (*j)->character->upLastPress) < 250) {
                                            (*j)->character->isHoldingSpecialUp = true;
                                        } else if ((now - (*j)->character->downLastPress) < 250) {
                                            (*j)->character->isHoldingSpecialDown = true;
                                        } else {
                                            (*j)->character->isHoldingSpecialOpen = true;
                                            (*j)->character->isSpecialAttackOpen = true;
                                        }
                                        (*j)->character->moveInitialRun = true;
                                    }
                                } else if ((*i)->pressed == SDL_RELEASED) {
                                    if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller) {
                                        (*j)->character->isHoldingSpecialLeft = false;
                                        (*j)->character->isHoldingSpecialRight = false;
                                        (*j)->character->isHoldingSpecialUp = false;
                                        (*j)->character->isHoldingSpecialDown = false;
                                        (*j)->character->isHoldingSpecialOpen = false;
                                    }
                                }
                            break;
                        }
                    }
                }
            }

            //Clear interactions off of the heap
            for (Interaction* i : *data->interact) {
                delete (i);
            }
            data->interact->clear();
        }
    }
    SDL_UnlockMutex(parse_mutex);
}

int Event::EventHandler(void* data) {
    SDL_Event event;
    ThreadData *channel = (ThreadData*)data;
    bool quit = false;
    while (!quit) {
        while( SDL_WaitEvent(&event) != 0) {
            Interaction *inter = new Interaction();
            if(event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP) {
                if (SDL_LockMutex(channel->parse_mutex) == 0) {
                    inter->button_event = event.cbutton.button;
                    inter->controller_id = event.cbutton.which;
                    inter->pressed = event.cbutton.state;
                    channel->interact->push_back(inter);
                    SDL_UnlockMutex(channel->parse_mutex);
                } else {
                    std::cout << "Event::ParseEvents() - "<< SDL_TryLockMutex(channel->parse_mutex) <<std::endl;
                }
            }
        }
    }
    return 0;
}
