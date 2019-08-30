#include "Core.h"
#include "MainMenuOptions.h"
#include "Level.h"
#include <vector>
#include <string>


Core::Core()
{
    this->window = NULL;
    this->renderer = NULL;
    this->quit_program =NULL;
    this->state = new(State);
    this->state->onMainMenuStart = true;
    this->state->onOptionSelection = false;
    this->state->onLevelSelection = false;
    this->state->onCharacterSelection = false;
    this->state->onRunningMatch = false;
    this->data= new(ThreadData);
    this->data->interact = new(std::vector<Interaction*>);
    this->players = new(std::vector<PlayerObject*>);
}
void Core::renderPresent()
{
    SDL_RenderPresent(renderer);
}
void Core::renderClear()
{
    SDL_RenderClear(renderer);
}

bool Core::CoreInit()
{
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ))
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        //Create window
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto Width = DM.w;
        auto Height = DM.h;
        SCREEN_WIDTH = Width;
        SCREEN_HEIGHT= Height;
        std::cout<<"screen_width: "<<SCREEN_WIDTH<<" "<<"screen_height: "<<SCREEN_HEIGHT<<std::endl;
        window = SDL_CreateWindow( "HolyWar", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Full screen the window.
            int res = SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
            if(res != 0)
            {
                printf("Could not fullscreen program. Error: %s\n",SDL_GetError());
            }

            //Create renderer for window
            this->renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( this->renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {

                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ))
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }

            //Add sdl2 controller mapping database.

            int maps = SDL_GameControllerAddMappingsFromFile("rec/controller_maps/gamecontrollerdb.txt");
            if (maps == -1)
            {
                std::cout << "Warning: No joystick mappings loaded from database!" << std::endl;

            }
            if( SDL_NumJoysticks() < 1 )
            {
                printf( "Warning: No joysticks connected!\n" );
            }
            else
            {
                //std::cout << SDL_NumJoysticks() << std::endl;
                //Load new players and joystick pointers to each player.

                //TODO: This process needs to query the player when a new controller type is detected that is not in controller database.
                //Will need deferred process that will activate after other controllers are initialized so player can select controller type
                //(eg. playstation/xbox/gamecube/ ect...)
                //If other controllers are recognized user can use neighboring controller to select controller type from user request.
                //Making it easier on us to dynamically create entry in database, but in the off-chance the users only controller is not recognized
                //Will have to have alternative solution(Not solved).


                for(int i = 0; i <SDL_NumJoysticks(); i++)
                {
                    PlayerObject* newPlayer = new PlayerObject(i,this->SCREEN_WIDTH/2+i,SCREEN_HEIGHT/2,this->renderer);
                    newPlayer->controller = SDL_GameControllerOpen(i);
                    if (SDL_IsGameController(i))
                    {
                        this->players->push_back(newPlayer);
                    }
                    else
                    {
                        SDL_Joystick* js = SDL_JoystickOpen(i);
                        char temp[1024];
                        SDL_JoystickGUID GUID = SDL_JoystickGetGUID(js);
                        SDL_JoystickGetGUIDString(GUID,temp,sizeof(temp));
                        std::cout << temp << std::endl;

                    }
                }
                std::cout<< "Num_controllers: "<<this->players->size() << std::endl;
            }
        }
    }
    return success;
}

void  Core::RunMainMenu(SDL_mutex* mutex)
{
    this->state->transition = false;
    this->state->onMainMenuStart = true;
    this->state->onOptionSelection= false;
    this->state->mainMenuOps = new MainMenuOptions(this->renderer);

    //Textures
    GeneralTexture* logo       = this->state->mainMenuOps->menuLogo;
    logo->loadMedia(logo,this->renderer);
    GeneralTexture* background = this->state->mainMenuOps->menuBackground;
    background->loadMedia(background,this->renderer);


    //Buttons
    MenuButton* StartButton = this->state->mainMenuOps->menuStart;
    MenuButton* BattleButton = this->state->mainMenuOps->menuBattle;
    BattleButton->is_highlighted = true;
    MenuButton* OptionsButton = this->state->mainMenuOps->menuOptions;
    OptionsButton->is_highlighted = false;
    MenuButton* QuitButton = this->state->mainMenuOps->menuQuit;
    QuitButton->is_highlighted=false;

    StartButton->texture->loadMedia(StartButton->texture, this->renderer);
    BattleButton->texture->loadMedia(BattleButton->texture,this->renderer);
    OptionsButton->texture->loadMedia(OptionsButton->texture,this->renderer);
    QuitButton->texture->loadMedia(QuitButton->texture, this->renderer);



    int logoXPos = 0;
    logoXPos = this->SCREEN_WIDTH/2-430;
    bool alphaFlag = true;
    while ((this->state->onMainMenuStart || this->state->onOptionSelection) && !this->quit_program)
    {
        if (alphaFlag)  //TODO: add short circuit here for user pressing start to skip into Alpha blend.
        {
            for (int i=0; i<256; i++)
            {
                this->ParseEvents(this->data,mutex);
                this->renderClear();
                background->render(background, this->renderer,0,0,2,0,0,NULL);
                background->SetAlpha(i);
                logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,0,0,NULL);
                logo->SetAlpha(i);
                this->renderPresent();
                SDL_Delay(20);
            }
        }
        this->ParseEvents(this->data,mutex);
        alphaFlag = false;
        this->renderClear();
        background->render(background, this->renderer,0,0,2,0,0,NULL);
        logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,0,0,NULL);
        if(this->state->onMainMenuStart)
        {
            StartButton->texture->render(StartButton->texture,this->renderer,logoXPos+320,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
        }
        if (this->state->onOptionSelection)
        {
            if(BattleButton->is_highlighted)
            {
                BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,5,0,0,NULL);
                OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,0,0,NULL);
                QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,0,0,NULL);
            }
            if (OptionsButton->is_highlighted)
            {
                BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
                OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,5,0,0,NULL);
                QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,0,0,NULL);
            }
            if (QuitButton->is_highlighted)
            {
                BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
                OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,0,0,NULL);
                QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,5,0,0,NULL);
            }

        }
        this->renderPresent();
        SDL_Delay(30);

        if(this->state->transition)
        {
            for(int i = 255; i>=0; i--)
            {
                this->ParseEvents(this->data,mutex);
                alphaFlag = false;
                this->renderClear();
                background->SetAlpha(i);
                background->render(this->state->mainMenuOps->menuBackground, this->renderer,0,0,2,0,0,NULL);
                logo->SetAlpha(i);
                logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,0,0,NULL);
                if (this->state->onOptionSelection)
                {
                    if(BattleButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,5,0,0,NULL);
                        BattleButton->texture->SetAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,0,0,NULL);
                        OptionsButton->texture->SetAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,0,0,NULL);
                        QuitButton->texture->SetAlpha(i);
                    }
                    if (OptionsButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
                        BattleButton->texture->SetAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,5,0,0,NULL);
                        OptionsButton->texture->SetAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,0,0,NULL);
                        QuitButton->texture->SetAlpha(i);
                    }
                    if (QuitButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
                        BattleButton->texture->SetAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,0,0,NULL);
                        OptionsButton->texture->SetAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,5,0,0,NULL);
                        QuitButton->texture->SetAlpha(i);
                    }

                }
                this->renderPresent();
                SDL_Delay(10);
            }
            this->state->onMainMenuStart= false;
            this->state->onOptionSelection = false;
            this->state->transition = false;
            this->state->onCharacterSelection = true;
        }
    }
}

void Core::RunCharacterSelect(SDL_mutex* mutex)
{

    GeneralTexture* background = this->state->mainMenuOps->menuBackground;
    GeneralTexture* playerNumber = new GeneralTexture(10,"NumberStrip",this->renderer);
    GeneralTexture* cs_menu_midground = new GeneralTexture(1,"CharacterSelectMenu",this->renderer);
    std::vector<CharacterPortrait*> *avatars = this->InitCharacterPortraits(this->renderer);
    int idleMod =0;
    if(sizeof(avatars) > 0)
    {
        std::cout<<"Successfully loaded Avatars:"<<std::endl;
    }
    else
    {
        std::cout<<"Error: failed to load avatars."<<std::endl;
        exit(EXIT_FAILURE);
    }
    bool alphaFlag = true;
    int def_x_pos = 200;
    int def_y_pos = 500;
    int char_box_y_pos = 125;

    SDL_Rect *exp_rec = new (SDL_Rect);
    exp_rec->h= 85;
    exp_rec->w= 120;
    exp_rec->x= def_x_pos;
    exp_rec->y= def_y_pos;

    SDL_Rect *CharBox = new (SDL_Rect);
    CharBox->h = 270;
    CharBox->w = 300;
    CharBox->x = def_x_pos;
    CharBox->y = char_box_y_pos;

    while(this->state->onCharacterSelection)
    {

        if (alphaFlag)  //TODO: add short circuit here for user pressing start to skip into Alpha blend.
        {
            for (int i=0; i<256; i++)
            {
                this->ParseEvents(this->data,mutex);
                this->renderClear();
                background->SetAlpha(i);
                background->render(background, this->renderer,0,0,2,0,0,NULL);
                cs_menu_midground->SetAlpha(i);
                cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);
                this->renderPresent();
                SDL_Delay(1);
            }
            alphaFlag = false;
            SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0); // Testing rectangle.
        }


        this->renderClear();
        this->ParseEvents(this->data,mutex);
        background->render(background, this->renderer,0,0,2,0,0,NULL);
        cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);

        for(std::vector<CharacterPortrait*>::iterator i = avatars->begin(); i!= avatars->end(); i++)
        {
            //This section aligns the characterPortrait with its encapsulating square position.
            if(exp_rec->x+ exp_rec->w <= cs_menu_midground->GetXPos()+cs_menu_midground->GetWidth())
            {
                SDL_RenderDrawRect(this->renderer,exp_rec);
                int offset_x= ((exp_rec->w-((*i)->avatar->GetWidth()/(*i)->avatar->textureClipCount+1))/2)+5;
                int offset_y=   exp_rec->h-(*i)->avatar->GetHeight()-10;
                (*i)->avatar->render((*i)->avatar,this->renderer,exp_rec->x,exp_rec->y,1,offset_x,offset_y, &(*i)->avatar->animation[0]);
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*j)->isActive)
                    {
                        if(this->CursorCollisionDetect((*j)->cursor,exp_rec))
                        {

                            if((*j)->ID+1 == 1)
                            {
                                SDL_SetRenderDrawColor(this->renderer,255,0,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 2)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 3)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 4)
                            {
                                SDL_SetRenderDrawColor(this->renderer,204,204,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->CharacterSelected)
                            {
                                (*j)->CharacterName = (*i)->CharacterName;
                                (*j)->isReady = true;
                                //std::cout<<"Character: "<<(*i)->CharacterName<<" selected!"<<std::endl;
                                (*j)->CharacterSelected = false;
                            }
                        }
                        else
                        {
                            (*j)->cursor->isColliding = false;
                        }

                    }


                }
                exp_rec->x = exp_rec->x+exp_rec->w+30;
            }
            else
            {
                exp_rec->x=def_x_pos;
                exp_rec->y= exp_rec->y+exp_rec->h+50;
                SDL_RenderDrawRect(this->renderer,exp_rec);
                int offset_x = ((exp_rec->w-((*i)->avatar->GetWidth()/(*i)->avatar->textureClipCount+1))/2)+5;
                int offset_y=   exp_rec->h-(*i)->avatar->GetHeight()-10;
                (*i)->avatar->render((*i)->avatar,this->renderer,exp_rec->x,exp_rec->y,1,offset_x,offset_y, &(*i)->avatar->animation[0]);
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*j)->isActive)
                    {
                        if(this->CursorCollisionDetect((*j)->cursor,exp_rec))
                        {
                            if((*j)->ID+1 == 1)
                            {
                                SDL_SetRenderDrawColor(this->renderer,255,0,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 2)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 3)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 4)
                            {
                                SDL_SetRenderDrawColor(this->renderer,204,204,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }

                            if ((*j)->CharacterSelected)
                            {
                                (*j)->CharacterName = (*i)->CharacterName;
                                (*j)->isReady = true;
                                //std::cout<<"Character: "<<(*i)->CharacterName<<" selected!"<<std::endl;
                                (*j)->CharacterSelected = false;
                            }

                        }
                        else
                        {
                            (*j)->cursor->isColliding = false;
                        }
                    }
                }
            }
            SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0);
            for(int j = 0; j<4; j++)
            {

                SDL_RenderDrawRect(this->renderer, CharBox);
                for(std::vector<PlayerObject*>::iterator k = this->players->begin(); k!= this->players->end(); k++)
                {
                    if ((*k)->CharacterName == (*i)->CharacterName && j == (*k)->ID)
                    {
                        int offset_x = ((CharBox->w-((((*i)->avatar->GetWidth()*3))/(*i)->avatar->textureClipCount+1))/2)+10;
                        int offset_y =   CharBox->h-(((*i)->avatar->GetHeight()*3))-15;
                        (*i)->avatar->render((*i)->avatar,this->renderer,CharBox->x,CharBox->y,3,offset_x,offset_y, &(*i)->avatar->animation[(*i)->avatar->GetFrameCount()]);
                        if(idleMod % 7 == 0)
                        {
                            (*i)->avatar->TickFrameCount();
                        }
                        if ((*i)->avatar->GetFrameCount() == (*i)->avatar->textureClipCount)
                        {
                            (*i)->avatar->ResetFrameCount();
                        }
                    }
                }
                CharBox->x = CharBox->x+CharBox->w+100;

            }

        }
        //Render and move players cursor texture.
        for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
        {
            if ((*i)->isActive)
            {
                (*i)->cursor->Texture->render((*i)->cursor->Texture,this->renderer,(*i)->cursor->PosX,(*i)->cursor->PosY,3,0,0,NULL);
                playerNumber->render(playerNumber,this->renderer,(*i)->cursor->PosX+(*i)->cursor->Texture->GetWidth()*3, \
                                     (*i)->cursor->PosY+(*i)->cursor->Texture->GetHeight()*3,2,0,0, &playerNumber->animation[(*i)->ID+1]);
                (*i)->cursor->Move();
            }

        }

        this->renderPresent();
        exp_rec->x = def_x_pos;
        exp_rec->y = def_y_pos;
        CharBox->x = def_x_pos;
        SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0);
        idleMod++;
        if (idleMod == 20000)
        {
            idleMod =0;
        }
        SDL_Delay(25);
    }
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
    for (int i=255; i>=0; i--)
    {
        this->ParseEvents(this->data,mutex);
        this->renderClear();
        background->SetAlpha(i);
        background->render(background, this->renderer,0,0,2,0,0,NULL);
        cs_menu_midground->SetAlpha(i);
        cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);
        this->renderPresent();
        SDL_Delay(5);
    }
    playerNumber->Free_Texture();
    cs_menu_midground->Free_Texture();
    delete(exp_rec);
    delete(CharBox);
    for(CharacterPortrait* i : *avatars)
    {
        delete(i);
    }


}

void Core::RunLevelSelect(SDL_mutex* mutex)
{

    bool alphaFlag = true;
    GeneralTexture* cs_menu_midground = new GeneralTexture(1,"CharacterSelectMenu",this->renderer);
    GeneralTexture* playerNumber = new GeneralTexture(10,"NumberStrip",this->renderer);
    GeneralTexture* background = this->state->mainMenuOps->menuBackground;
    std::vector<LevelPortrait*> *avatars = this->InitLevelPortraits(this->renderer);
    if (sizeof(avatars) > 0)
    {
        std::cout<<"Succesfully loaded Level avatars."<<std::endl;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
    {
        if ((*i)->isActive)
        {
            (*i)->cursor->ResetPos();
        }
    }
    int def_x_pos = 200;
    int def_y_pos = 500;
    int level_box_y_pos = 115;
    SDL_Rect *exp_rec = new (SDL_Rect);
    exp_rec->h= 85;
    exp_rec->w= 120;
    exp_rec->x= def_x_pos;
    exp_rec->y= def_y_pos;

    SDL_Rect *LevelBox = new (SDL_Rect);
    LevelBox->h = 275;
    LevelBox->w = 600;
    LevelBox->x = cs_menu_midground->GetXPos()+(cs_menu_midground->GetWidth()*3/8);
    LevelBox->y = level_box_y_pos;
    while(this->state->onLevelSelection)
    {
        if (alphaFlag)  //TODO: add short circuit here for user pressing start to skip into Alpha blend.
        {
            for (int i=0; i<256; i++)
            {
                this->ParseEvents(this->data,mutex);
                this->renderClear();
                background->SetAlpha(i);
                background->render(background, this->renderer,0,0,2,0,0,NULL);
                cs_menu_midground->SetAlpha(i);
                cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);
                this->renderPresent();
                SDL_Delay(1);
            }
            alphaFlag = false;
        }
        SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0);
        this->ParseEvents(this->data,mutex);
        this->renderClear();
        background->render(background, this->renderer,0,0,2,0,0,NULL);
        cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);
        for(std::vector<LevelPortrait*>::iterator i = avatars->begin(); i!= avatars->end(); i++)
        {
            if(exp_rec->x+ exp_rec->w <= cs_menu_midground->GetXPos()+cs_menu_midground->GetWidth())
            {
                SDL_RenderDrawRect(this->renderer,exp_rec);
                (*i)->level_avatar_small->render((*i)->level_avatar_small,this->renderer,exp_rec->x,exp_rec->y,1,0,0, NULL);
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*j)->isActive)
                    {
                        if(this->CursorCollisionDetect((*j)->cursor,exp_rec))
                        {

                            if((*j)->ID+1 == 1)
                            {
                                SDL_SetRenderDrawColor(this->renderer,255,0,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 2)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 3)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 4)
                            {
                                SDL_SetRenderDrawColor(this->renderer,204,204,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->levelSelected)
                            {
                                this->state->levelName = (*i)->LevelName;
                                for(std::vector<PlayerObject*>::iterator k = this->players->begin(); k!= this->players->end(); k++)
                                {
                                    (*k)->isReady = true;
                                }
                                (*j)->levelSelected = false;
                            }

                        }
                        else
                        {
                            (*j)->cursor->isColliding = false;
                        }

                    }
                }
                exp_rec->x = exp_rec->x+exp_rec->w+30;
            }
            else
            {
                exp_rec->x=def_x_pos;
                exp_rec->y= exp_rec->y+exp_rec->h+50;
                SDL_RenderDrawRect(this->renderer,exp_rec);
                (*i)->level_avatar_small->render((*i)->level_avatar_small,this->renderer,exp_rec->x,exp_rec->y,1,0,0, NULL);
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*j)->isActive)
                    {
                        if(this->CursorCollisionDetect((*j)->cursor,exp_rec))
                        {
                            if((*j)->ID+1 == 1)
                            {
                                SDL_SetRenderDrawColor(this->renderer,255,0,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 2)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 3)
                            {
                                SDL_SetRenderDrawColor(this->renderer,0,0,255,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->ID+1 == 4)
                            {
                                SDL_SetRenderDrawColor(this->renderer,204,204,0,0);
                                SDL_RenderDrawRect(this->renderer,exp_rec);
                                (*j)->cursor->isColliding = true;
                            }
                            if ((*j)->levelSelected)
                            {
                                this->state->levelName = (*i)->LevelName;
                                for(std::vector<PlayerObject*>::iterator k = this->players->begin(); k!= this->players->end(); k++)
                                {
                                    (*k)->isReady = true;
                                }
                            }

                        }
                        else
                        {
                            (*j)->cursor->isColliding = false;
                        }
                    }
                }
            }
        }
        for(std::vector<LevelPortrait*>::iterator i = avatars->begin(); i!= avatars->end(); i++)
        {
            if(this->state->levelName == (*i)->LevelName)
            {
                (*i)->level_avatar_big->render((*i)->level_avatar_big,this->renderer,LevelBox->x,LevelBox->y,1,0,0,NULL);
            }
        }
        SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0);
        SDL_RenderDrawRect(this->renderer, LevelBox);
        for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
        {
            if ((*i)->isActive)
            {
                (*i)->cursor->Texture->render((*i)->cursor->Texture,this->renderer,(*i)->cursor->PosX,(*i)->cursor->PosY,3,0,0,NULL);
                playerNumber->render(playerNumber,this->renderer,(*i)->cursor->PosX+(*i)->cursor->Texture->GetWidth()*3, \
                                     (*i)->cursor->PosY+(*i)->cursor->Texture->GetHeight()*3,2,0,0, &playerNumber->animation[(*i)->ID+1]);
                (*i)->cursor->Move();
            }

        }
        this->renderPresent();
        SDL_Delay(25);
        exp_rec->x = def_x_pos;
        exp_rec->y = def_y_pos;
    }
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
    for (int i=255; i>=0; i--)
    {
        this->ParseEvents(this->data,mutex);
        this->renderClear();
        background->SetAlpha(i);
        background->render(background, this->renderer,0,0,2,0,0,NULL);
        cs_menu_midground->SetAlpha(i);
        cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);
        this->renderPresent();
        SDL_Delay(5);
    }
    playerNumber->Free_Texture();
    cs_menu_midground->Free_Texture();
    delete(exp_rec);
    delete(LevelBox);
    for(LevelPortrait* i : *avatars)
    {
        delete(i);
    }

}//

void Core::RunMatch(SDL_mutex* parse_mutex)
{
    int Tick =0;
    int CharScale = 2;
    int PlatformScale=2;
    if(this->state->levelName == "")
    {
        exit(EXIT_FAILURE);
    }
    Level* stage = new Level(this->state->levelName,this->renderer); //TODO: delete this from memory later.
    bool EntryAlphaFlag = true;
    for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
    {
        (*i)->character = new CharacterObject((*i)->CharacterName,100,this->renderer); //TODO: delete from memory later.
    }
    while(this->state->onRunningMatch)
    {
        if(EntryAlphaFlag)
        {
            for(int j = 0; j<256; j++)
            {
                this->ParseEvents(this->data,parse_mutex);
                this->renderClear();
                for(std::vector<GeneralTexture*>::iterator i = stage->textures->begin(); i!= stage->textures->end(); i++)
                {
                    (*i)->SetAlpha(j);
                    (*i)->render((*i),this->renderer,(*i)->GetXPos(),(*i)->GetYPos(),2,0,0,NULL);
                }
                for(std::vector<GeneralTexture*>::iterator i = stage->platforms->begin(); i!= stage->platforms->end(); i++)
                {
                    (*i)->SetAlpha(j);
                    (*i)->render((*i),this->renderer,(*i)->GetXPos(),(*i)->GetYPos(),PlatformScale,0,0,NULL);
                }
                this->renderPresent();
                SDL_Delay(5);

            }
            EntryAlphaFlag = false;
        }
        this->ParseEvents(this->data,parse_mutex);
        this->renderClear();

        for(std::vector<GeneralTexture*>::iterator i = stage->textures->begin(); i!= stage->textures->end(); i++)
        {
            (*i)->render((*i),this->renderer,(*i)->GetXPos(),(*i)->GetYPos(),2,0,0,NULL);
        }
        for(std::vector<GeneralTexture*>::iterator i = stage->platforms->begin(); i!= stage->platforms->end(); i++)
        {
            (*i)->render((*i),this->renderer,(*i)->GetXPos(),(*i)->GetYPos(),PlatformScale,0,0,NULL);
        }

        //This part controls the collision detection between characters and platform objects.
        this->RunCollisionModule(CharScale,PlatformScale,stage);
        //This part runs the entire physics and rendering systems for characters.
        this->RunCharacters(CharScale,PlatformScale,Tick);

        this->renderPresent();
        SDL_Delay(30);
        Tick++;
        if (Tick == 1000)
        {
            Tick =0;
        }
    }
}


void Core::RunCollisionModule(int CharScale,int PlatformScale, Level* stage)
{
    for(std::vector<GeneralTexture*>::iterator i = stage->platforms->begin(); i!= stage->platforms->end(); i++)
    {
        for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
        {
            if(this->CollisionObjectCharacter((*i),PlatformScale,(*j)->character,CharScale))
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
                (*j)->character->posX = this->SCREEN_WIDTH - ((*j)->character->char_textures->idleClips[0].w/2);
            }
            else if ((*j)->character->posX+(*j)->character->char_textures->idleClips[0].w >= this->SCREEN_WIDTH+(*j)->character->char_textures->idleClips[0].w)
            {
                (*j)->character->posX = 0-(*j)->character->char_textures->idleClips[0].w/2-35;
            }
        }
    }
}
void Core::RunCharacters(int CharScale,int PlatformScale,int Tick)
{
    for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
    {
        CharacterObject* p = (*i)->character;

        if(!p->isJumping && !p->isFalling && !p->isMovingLeft && !p->isMovingRight && !p->isAttackingReg)
        {
            this->RunIdleModule(p,CharScale,Tick);
        }
        else if(!p->isJumping && !p->isFalling && (p->isMovingRight || p->isMovingLeft) && !p->isAttackingReg)
        {
            this->RunMoveModule(p,CharScale,Tick);
        }
        else if(!p->isJumping && p->isFalling && (p->isMovingLeft || p->isMovingRight) && !p->isAttackingReg)
        {
            this->RunFallingModule(p,CharScale,Tick);
        }
        else if(p->isJumping && !p->isFalling && (p->isMovingLeft || p->isMovingRight) && !p->isAttackingReg)
        {
            this->RunJumpingModule(p,CharScale,Tick);
        }
        else if((p->isJumping || p->isFalling) && !p->isMovingLeft && !p->isMovingRight && !p->isAttackingReg)
        {
            this->RunJumpFallTransitionModule(p,CharScale,Tick);
        }
        else if(p->isJumping && p->isFalling && (p->isMovingLeft || p->isMovingRight) && !p->isAttackingReg)
        {
            this->RunJumpFallTransitionModule(p,CharScale,Tick);
        }
        //Attacking animations.
        else if(p->isAttackingReg)
        {
            this->RunRegularAttackModule(p,CharScale,Tick);
        }
    }
}


void Core::RunRegularAttackModule(CharacterObject* p,int CharScale,int Tick)
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
                p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips[p->char_textures->GetFrameCount()],"A",SDL_FLIP_NONE);
            }
            else if (p->lastDirection == "RIGHT")
            {
                p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips[p->char_textures->GetFrameCount()],"A",SDL_FLIP_HORIZONTAL);
            }
        }
        else if(p->regAttackCount == 1)
        {

            if (p->lastDirection == "LEFT")
            {
                p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                         p->posY,CharScale,0,0,&p->char_textures->attackRegularClips2[p->char_textures->GetFrameCount()],"A2",SDL_FLIP_NONE);
            }
            else if (p->lastDirection == "RIGHT")
            {
                p->char_textures->render(p->char_textures,this->renderer,p->posX, \
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
        if(p->char_textures->GetFrameCount() >= p->char_textures->GetJumpingRegularAttackClickCount())
        {
            p->char_textures->SetFrameCount(0);
            p->isAttackingReg = false;
        }
        if (p->lastDirection == "LEFT")
        {
            p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->attackRegularJumpingClips[p->char_textures->GetFrameCount()],"JA",SDL_FLIP_NONE);
        }
        else if (p->lastDirection == "RIGHT")
        {
            p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->attackRegularJumpingClips[p->char_textures->GetFrameCount()],"JA",SDL_FLIP_HORIZONTAL);
        }
        if(Tick%p->char_textures->attackRegJumpingMod == 0)
        {
            p->char_textures->TickFrameCount();
        }
        p->Move();
    }
}

void Core::RunIdleModule(CharacterObject* p,int CharScale,int Tick)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetIdleClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if(p->lastDirection == "LEFT")
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->idleClips[p->char_textures->GetFrameCount()],"I",SDL_FLIP_NONE);
    }
    else if (p->lastDirection == "RIGHT")
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->idleClips[p->char_textures->GetFrameCount()],"I",SDL_FLIP_HORIZONTAL);
    }

    if(Tick%p->char_textures->idleMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move();
}

void Core::RunMoveModule(CharacterObject* p, int CharScale, int Tick)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetMoveingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if(p->isMovingLeft)
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->movementClips[p->char_textures->GetFrameCount()],"M",SDL_FLIP_NONE);
    }
    else if (p->isMovingRight)
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->movementClips[p->char_textures->GetFrameCount()],"M",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->moveMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move();
}

void Core::RunFallingModule(CharacterObject* p, int CharScale, int Tick)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetFallingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }
    if (p->lastDirection == "LEFT")
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    }
    else if (p->lastDirection == "RIGHT")
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    }
    if(Tick%p->char_textures->fallingMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move();
}

void Core::RunJumpingModule(CharacterObject *p, int CharScale, int Tick)
{
    if(p->char_textures->GetFrameCount() >= p->char_textures->GetJumpingClipCount())
    {
        p->char_textures->SetFrameCount(p->char_textures->GetJumpingClipCount()/2);
    }
    if(p->isMovingLeft)
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
    }
    else if(p->isMovingRight)
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
    }
    else if(!p->isMovingLeft && !p->isMovingRight)
    {
        if(p->lastDirection == "RIGHT")
        {
            p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_HORIZONTAL);
        }
        else if(p->lastDirection == "LEFT")
        {
            p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->jumpingClips[p->char_textures->GetFrameCount()],"J",SDL_FLIP_NONE);
        }
    }
    if(Tick%p->char_textures->jumpingMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move();
}
void Core ::RunJumpFallTransitionModule(CharacterObject* p, int CharScale, int Tick)
{
    if(p->char_textures->GetFrameCount() == p->char_textures->GetFallingClipCount())
    {
        p->char_textures->SetFrameCount(0);
    }

    if (p->isMovingLeft)
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
    }
    else if(p->isMovingRight)
    {
        p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                 p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
    }
    else if(!p->isMovingLeft && !p->isMovingRight)
    {
        if (p->lastDirection == "LEFT")
        {
            p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_NONE);
        }
        else if (p->lastDirection == "RIGHT")
        {
            p->char_textures->render(p->char_textures,this->renderer,p->posX, \
                                     p->posY,CharScale,0,0,&p->char_textures->fallingClips[p->char_textures->GetFrameCount()],"F",SDL_FLIP_HORIZONTAL);
        }
    }
    if(Tick%p->char_textures->fallingMod == 0)
    {
        p->char_textures->TickFrameCount();
    }
    p->Move();
}
std::vector<CharacterPortrait*> *Core::InitCharacterPortraits(SDL_Renderer* renderer)
{
    //TODO: START HERE.
    std::vector<CharacterPortrait*> *cp_vec = new std::vector<CharacterPortrait*>;
    CharacterPortrait *cp = new CharacterPortrait(18,"HorusCharacterSelect","Horus",renderer);
    cp_vec->push_back(cp);
    cp = NULL;
    delete(cp);
    if (sizeof(cp_vec) > 0)
    {
        return cp_vec;
    }
    return NULL;
}

std::vector<LevelPortrait*> *Core::InitLevelPortraits(SDL_Renderer* renderer)
{
    std::vector<LevelPortrait*> *lp_vec = new std::vector<LevelPortrait*>;
    LevelPortrait *lp = new LevelPortrait("MountainPrototypeSmall","MountainPrototypeBig","mountain_top",renderer);
    lp_vec->push_back(lp);
    lp = NULL;
    delete(lp);
    if (sizeof(lp_vec)>0)
    {
        return lp_vec;
    }
    return NULL;
}

bool Core::CollisionObjectCharacter(GeneralTexture* A, int a_scale, CharacterObject* B, int b_scale)
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

bool Core::CursorCollisionDetect(PlayerCursor* A,SDL_Rect* B)
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

void Core::ParseEvents(ThreadData* data,SDL_mutex* parse_mutex)
{
    if (SDL_LockMutex(parse_mutex) == 0 && data->interact->size() > 0)
    {
        //On Main Menu states//
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (this->state->onMainMenuStart)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                if((*i)->button_event == SDL_CONTROLLER_BUTTON_START)
                {
                    this->state->onMainMenuStart =false;
                    this->state->onOptionSelection = true;
                    this->state->mainMenuOps->menuBattle->is_highlighted = true;
                    this->state->mainMenuOps->menuOptions->is_highlighted = false;
                }
            }

        }
        else if (this->state->onOptionSelection)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                if((*i)->button_event == SDL_CONTROLLER_BUTTON_B)
                {
                    this->state->onMainMenuStart = true;
                    this->state->onOptionSelection = false;
                    this->state->mainMenuOps->menuStart->is_highlighted = true;
                    this->state->mainMenuOps->menuBattle->is_highlighted = false;
                    this->state->mainMenuOps->menuOptions->is_highlighted = false;
                    this->state->mainMenuOps->menuQuit->is_highlighted = false;

                }
                else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED)
                {
                    if(this->state->mainMenuOps->menuBattle->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = false;
                        this->state->mainMenuOps->menuOptions->is_highlighted= true;
                        this->state->mainMenuOps->menuQuit->is_highlighted = false;
                    }
                    else if(this->state->mainMenuOps->menuOptions->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = false;
                        this->state->mainMenuOps->menuOptions->is_highlighted= false;
                        this->state->mainMenuOps->menuQuit->is_highlighted = true;
                    }
                    else if(this->state->mainMenuOps->menuQuit->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = false;
                        this->state->mainMenuOps->menuOptions->is_highlighted= false;
                        this->state->mainMenuOps->menuQuit->is_highlighted = true;
                    }
                }
                else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED)
                {
                    if(this->state->mainMenuOps->menuBattle->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = true;
                        this->state->mainMenuOps->menuOptions->is_highlighted= false;
                        this->state->mainMenuOps->menuQuit->is_highlighted = false;
                    }
                    else if(this->state->mainMenuOps->menuOptions->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = true;
                        this->state->mainMenuOps->menuOptions->is_highlighted= false;
                        this->state->mainMenuOps->menuQuit->is_highlighted = false;
                    }
                    else if(this->state->mainMenuOps->menuQuit->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = false;
                        this->state->mainMenuOps->menuOptions->is_highlighted= true;
                        this->state->mainMenuOps->menuQuit->is_highlighted = false;
                    }
                }
                else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED)
                {
                    if(this->state->mainMenuOps->menuBattle->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = true;
                        this->state->mainMenuOps->menuOptions->is_highlighted= false;
                        this->state->mainMenuOps->menuQuit->is_highlighted = false;
                        this->state->transition=true;


                    }
                    else if(this->state->mainMenuOps->menuOptions->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = false;
                        this->state->mainMenuOps->menuOptions->is_highlighted= true;
                        this->state->mainMenuOps->menuQuit->is_highlighted = false;

                    }
                    else if(this->state->mainMenuOps->menuQuit->is_highlighted)
                    {
                        this->state->mainMenuOps->menuBattle->is_highlighted = false;
                        this->state->mainMenuOps->menuOptions->is_highlighted= false;
                        this->state->mainMenuOps->menuQuit->is_highlighted = true;
                        this->quit_program = true;
                    }
                }
            }
        }
        //CharacterSelection stat//
        /////////////////////////////////////////////////////////////////////////////////////////
        else if ( this->state->onCharacterSelection)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = (*j)->cursor->CURSOR_VEL;
                        }


                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = -(*j)->cursor->CURSOR_VEL;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX = -(*j)->cursor->CURSOR_VEL;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX = (*j)->cursor->CURSOR_VEL;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_START && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller && (*j)->isActive == false)
                        {
                            (*j)->isActive =true;
                        }
                        for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                        {
                            if(!(*j)->isReady)
                            {
                                break;
                            }
                            if(j == this->players->end()-1 && (*j)->isReady)
                            {
                                this->state->onCharacterSelection=false;
                                this->state->onLevelSelection = true;
                            }
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->CharacterSelected = true;
                        }
                    }
                    //SDL_RELEASED

                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX =0;
                        }

                    }
                }

            }
        }
        //LevelSelection state//
        /////////////////////////////////////////////////////////////////////////////////////////
        else if (this->state->onLevelSelection)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = (*j)->cursor->CURSOR_VEL;
                        }


                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = -(*j)->cursor->CURSOR_VEL;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX = -(*j)->cursor->CURSOR_VEL;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX = (*j)->cursor->CURSOR_VEL;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_START && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller && (*j)->isActive == false)
                        {
                            (*j)->isActive =true;
                        }
                        if (this->state->levelName!="")
                        {
                            this->state->onLevelSelection =false;
                            this->state->onRunningMatch = true;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->levelSelected = true;
                        }
                    }
                    //SDL_RELEASED

                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX =0;
                        }

                    }
                }

            }
        }
        //RunningMatch state//
        /////////////////////////////////////////////////////////////////////////////////////////
        else if (this->state->onRunningMatch)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            //(*j)->character->fluct_vely = (*j)->character->moveVelX;
                        }


                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            /*(*j)->character->fluct_vely = -(*j)->character->moveVelY;
                            (*j)->character->char_textures->SetFrameCount(0);*/
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->character->isMovingLeft = true;
                            (*j)->character->isAttackingReg = false;
                            (*j)->character->lastDirection = "LEFT";
                            (*j)->character->fluct_velx = -(*j)->character->moveVelX;
                            (*j)->character->char_textures->SetFrameCount(0);
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_PRESSED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->character->isMovingRight = true;
                            (*j)->character->isAttackingReg = false;
                            (*j)->character->lastDirection = "RIGHT";
                            (*j)->character->fluct_velx = (*j)->character->moveVelX;
                            (*j)->character->char_textures->SetFrameCount(0);
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_START && (*i)->pressed == SDL_PRESSED)
                    {
                        this->quit_program=true;
                        this->state->onRunningMatch=false;
                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            if((!(*j)->character->isAttackingReg && !(*j)->character->isHoldingReg))
                            {
                                (*j)->character->char_textures->SetFrameCount(0);
                                Uint32 now = SDL_GetTicks();
                                if ( (now - (*j)->character->regAttackLastPress) <= 750)
                                {
                                    (*j)->character->regAttackCount++;
                                    (*j)->character->regAttackLastPress = now;
                                }
                                else
                                {
                                    (*j)->character->regAttackCount = 0;
                                    (*j)->character->regAttackLastPress = now;
                                }
                                //TODO:// This is a temporary block To reset counter if it goes over amount Attack count.
                                ////////////////////////////////////////////
                                if ((*j)->character->regAttackCount > 1)  //
                                {
                                    //
                                    (*j)->character->regAttackCount =0;   //
                                }                                         //
                                ////////////////////////////////////////////

                            }
                            (*j)->character->isAttackingReg = true;
                            //(*j)->character->char_textures->SetFrameCount(0);
                        }
                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_B && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            if((*j)->character->jumpBlock < 2)
                            {
                                (*j)->character->isJumping = true;
                                (*j)->character->isColliding = false;
                                (*j)->character->isFalling = false;
                                (*j)->character->isAttackingReg = false;
                                (*j)->character->char_textures->SetFrameCount(0);
                                (*j)->character->fluct_vely = -(*j)->character->moveVelY;
                                (*j)->character->jumpBlock++;
                            }
                        }
                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_X && (*i)->pressed == SDL_PRESSED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {

                        }
                    }

                    //SDL_RELEASED

                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            //(*j)->character->fluct_vely = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            //(*j)->character->fluct_vely = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->character->isMovingLeft = false;
                            (*j)->character->fluct_velx = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_RELEASED)
                    {

                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->character->isMovingRight = false;
                            (*j)->character->fluct_velx = 0;
                        }

                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_A && (*i)->pressed == SDL_RELEASED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {

                        }
                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_B && (*i)->pressed == SDL_RELEASED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->character->isJumping = false;
                            if(!(*j)->character->isColliding)
                            {
                                (*j)->character->isFalling = true;
                            }
                        }
                    }
                    else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_X && (*i)->pressed == SDL_RELEASED)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {

                        }
                    }
                }
            }
        }

        //Clear interactions off of the heap
        for (Interaction* i : *data->interact)
        {
            delete (i);
        }
        data->interact->clear();
    }
    SDL_UnlockMutex(parse_mutex);
}

int Core::EventHandler(void* data)
{
    SDL_Event event;
    ThreadData *channel = (ThreadData*)data;
    bool quit = false;
    while (!quit)
    {
        while( SDL_WaitEvent(&event) != 0)
        {
            Interaction *inter = new Interaction();
            if(event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
            {
                if (SDL_LockMutex(channel->parse_mutex) == 0)
                {
                    inter->button_event = event.cbutton.button;
                    inter->controller_id = event.cbutton.which;
                    inter->pressed = event.cbutton.state;
                    channel->interact->push_back(inter);
                    SDL_UnlockMutex(channel->parse_mutex);
                }
                else
                {
                    std::cout << "Event_4: Error() => "<<SDL_TryLockMutex(channel->parse_mutex) <<std::endl;
                }
            }// BUTTONDOWN
        }
    }
    return 0;
}

void Core::CoreShutdown()
{
    std::cout<<"In core shutdown_1."<<std::endl;
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    this->window        = NULL;
    this->renderer      = NULL;
    std::cout<<"In core shutdown_2."<<std::endl;
    std::cout<<"In core shutdown_3."<<std::endl;
    std::cout<<"In core shutdown_4."<<std::endl;
    delete(this->state);
    std::cout<<"In core shutdown_5."<<std::endl;
    delete(this->data);
    std::cout<<"In core shutdown_6."<<std::endl;
    for (PlayerObject* i : *this->players)
    {
        delete(i);
    }
    std::cout<<"In core shutdown_8."<<std::endl;
    IMG_Quit();
    std::cout<<"In core shutdown_9."<<std::endl;
    SDL_Quit();
    std::cout<<"In core shutdown_10."<<std::endl;
}
