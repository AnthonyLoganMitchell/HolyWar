#include "Core.h"
#include <vector>
#include "MainMenuOptions.h"
#include <string>
#include <vector>

Core::Core()
{
    //
    this->window = NULL;
    this->renderer = NULL;
    this->quit_program =NULL;
    this->state = new(State);
    this->state->onMainMenuStart = true;
    this->state->onOptionSelection = false;
    this->state->onLevelSelction = false;
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
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER) < 0 )
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
        //TODO: Change screen width and height back.
        window = SDL_CreateWindow( "HolyWar", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {

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
                std::cout << SDL_NumJoysticks() << std::endl;
                //Load new players and joystick pointers to each player.
                //TODO:
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

void  Core::MainMenuRun(SDL_mutex* mutex)
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
                this->ParseEvents(this->data,"",mutex);
                this->renderClear();
                background->render(background, this->renderer,0,0,2,0,0,NULL);
                background->setAlpha(i);
                logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,0,0,NULL);
                logo->setAlpha(i);
                this->renderPresent();
                SDL_Delay(20);
            }
        }
        this->ParseEvents(this->data,"",mutex);
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
                this->ParseEvents(this->data,"",mutex);
                alphaFlag = false;
                this->renderClear();
                background->setAlpha(i);
                background->render(this->state->mainMenuOps->menuBackground, this->renderer,0,0,2,0,0,NULL);
                logo->setAlpha(i);
                logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,0,0,NULL);
                if (this->state->onOptionSelection)
                {
                    if(BattleButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,5,0,0,NULL);
                        BattleButton->texture->setAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,0,0,NULL);
                        OptionsButton->texture->setAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,0,0,NULL);
                        QuitButton->texture->setAlpha(i);
                    }
                    if (OptionsButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
                        BattleButton->texture->setAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,5,0,0,NULL);
                        OptionsButton->texture->setAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,0,0,NULL);
                        QuitButton->texture->setAlpha(i);
                    }
                    if (QuitButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,0,0,NULL);
                        BattleButton->texture->setAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,0,0,NULL);
                        OptionsButton->texture->setAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,5,0,0,NULL);
                        QuitButton->texture->setAlpha(i);
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

void Core::CharacterSelectRun(SDL_mutex* mutex)
{

    GeneralTexture* background = this->state->mainMenuOps->menuBackground;
    GeneralTexture* playerNumber = new GeneralTexture(10,"NumberStrip",this->renderer);
    GeneralTexture* cs_menu_midground = new GeneralTexture(1,"CharacterSelectMenu",this->renderer);
    std::vector<CharacterPortrait*> *avatars = this->InitPortraits(this->renderer);
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
    int default_x_pos = 200;
    int default_y_pos = 500;

    SDL_Rect *exp_rec = new (SDL_Rect);
    exp_rec->h= 85;
    exp_rec->w= 120;
    exp_rec->x= default_x_pos;
    exp_rec->y= default_y_pos;

    while(this->state->onCharacterSelection)
    {

        if (alphaFlag)  //TODO: add short circuit here for user pressing start to skip into Alpha blend.
        {
            for (int i=0; i<256; i++)
            {
                this->ParseEvents(this->data,"",mutex);
                this->renderClear();
                background->setAlpha(i);
                background->render(background, this->renderer,0,0,2,0,0,NULL);
                cs_menu_midground->setAlpha(i);
                cs_menu_midground->render(cs_menu_midground,this->renderer,100,100,1,0,0,NULL);
                this->renderPresent();
                SDL_Delay(1);
            }
            alphaFlag = false;
            SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0); // Testing rectangle.
        }


        this->renderClear();
        this->ParseEvents(this->data,"",mutex);
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
                        if(this->CollisionDetect((*j)->cursor,exp_rec))
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
                                std::cout<<"Character: "<<(*i)->CharacterName<<" selected!"<<std::endl;
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
                exp_rec->x=default_x_pos;
                exp_rec->y= exp_rec->y+exp_rec->h+50;
                SDL_RenderDrawRect(this->renderer,exp_rec);
                int offset_x = ((exp_rec->w-((*i)->avatar->GetWidth()/(*i)->avatar->textureClipCount+1))/2)+5;
                int offset_y=   exp_rec->h-(*i)->avatar->GetHeight()-10;
                (*i)->avatar->render((*i)->avatar,this->renderer,exp_rec->x,exp_rec->y,1,offset_x,offset_y, &(*i)->avatar->animation[0]);
                for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                {
                    if ((*j)->isActive)
                    {
                        if(this->CollisionDetect((*j)->cursor,exp_rec))
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
                                std::cout<<"Character: "<<(*i)->CharacterName<<" selected!"<<std::endl;
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
        exp_rec->x = default_x_pos;
        exp_rec->y = default_y_pos;
        SDL_SetRenderDrawColor( this->renderer, 119, 119, 119, 0);
        SDL_Delay(25);
    }
}

std::vector<CharacterPortrait*> *Core::InitPortraits(SDL_Renderer* renderer)
{
    //TODO: START HERE.
    std::vector<CharacterPortrait*> *cp_vec = new std::vector<CharacterPortrait*>;
    CharacterPortrait *cp = new CharacterPortrait(9,"HorusCharacterSelect","Horus",renderer);
    cp_vec->push_back(cp);
    cp = NULL;
    delete(cp);
    if (sizeof(cp_vec) > 0)
    {
        return cp_vec;
    }
    return NULL;
}


bool Core::CollisionDetect(PlayerCursor* A,SDL_Rect* B)
{
    int rect_1_top = A->PosY+2;
    int rect_1_bottom = A->PosY+A->Texture->GetHeight()+2;
    int rect_1_left = A->PosX+2;
    int rect_1_right = A->PosX+A->Texture->GetWidth()+2;

    int rect_2_top = B->y;
    int rect_2_bottom = B->y+B->h;
    int rect_2_left = B->x;
    int rect_2_right = B->x+B->w;

    //std::cout<<"Rect_1: top:"<<rect_1_top<<" bot: "<<rect_1_bottom<<" left: "<<rect_1_left<<" right: "<<rect_1_right<<std::endl;
    //std::cout<<"Rect_2: top:"<<rect_2_top<<" bot: "<<rect_2_bottom<<" left: "<<rect_2_left<<" right: "<<rect_2_right<<std::endl;

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


template<class T>
void Core::ParseEvents(ThreadData* data,T* Modify,SDL_mutex* parse_mutex)
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
        else if (this->state->onLevelSelction)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                std::cout <<"ControllerID: "<< (*i)->controller_id << std::endl;
            }
        }
        //RnningMatch state//
        /////////////////////////////////////////////////////////////////////////////////////////
        else if (this->state->onRunningMatch)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                //std::cout <<"ControllerID: "<< (*i)->controller_id << std::endl;
            }
        }

        //Clear interactions off of the heap
        for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
        {
            delete(*i);
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
        while( SDL_PollEvent(&event) != 0)
        {
            Interaction *inter = new Interaction();

            if( event.type == SDL_QUIT)
            {
                quit=true;
            }
            else if(event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
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
            else
            {
                break;
            }

        }
    }
    return 0;
}

void Core::CoreShutdown()
{
    this->window        = NULL;
    this->renderer      = NULL;
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    delete(this->state);
    delete(this->data);
    for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
    {
        delete((*i));
    }
    delete(this->players);
    IMG_Quit();
    SDL_Quit();
}
