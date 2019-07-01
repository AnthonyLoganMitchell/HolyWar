#include "Core.h"
#include <vector>
#include "MainMenuOptions.h"
Core::Core()
{
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
    this->data->parse_mutex = SDL_CreateMutex();
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
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
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

            int maps = SDL_GameControllerAddMappingsFromFile("rec/ControllerMaps/gamecontrollerdb.txt");
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
                    //this->players.push_back()
                    PlayerObject* newPlayer = new PlayerObject();
                    newPlayer->controller = SDL_GameControllerOpen(i);
                    if (SDL_IsGameController(i))
                    {
                        this->players->push_back(newPlayer);
                    }else
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

void  Core::MainMenuRun()
{
    this->state->transition = false;
    this->state->onMainMenuStart = true;
    this->state->onOptionSelection= false;
    this->state->mainMenuOps = new MainMenuOptions(this->renderer);
    //Textures
    GeneralTexture* logo       = this->state->mainMenuOps->menuLogo;
    GeneralTexture* background = this->state->mainMenuOps->menuBackground;


    //Buttons
    MenuButton* StartButton = this->state->mainMenuOps->menuStart;
    MenuButton* BattleButton = this->state->mainMenuOps->menuBattle;
    BattleButton->is_highlighted = true;
    MenuButton* OptionsButton = this->state->mainMenuOps->menuOptions;
    OptionsButton->is_highlighted = false;
    MenuButton* QuitButton = this->state->mainMenuOps->menuQuit;
    QuitButton->is_highlighted=false;


    int logoXPos = 0;
    logoXPos = this->SCREEN_WIDTH/2-430;
    bool alphaFlag = true;
    while ((this->state->onMainMenuStart || this->state->onOptionSelection) && !this->quit_program)
    {
        if (alphaFlag)  //TODO: add short circuit here for user pressing start to skip into Alpha blend.
        {
            for (int i=0; i<256; i++)
            {
                this->ParseEvents(this->data,"");
                this->renderClear();
                background->render(background, this->renderer,0,0,2,NULL);
                background->setAlpha(i);
                logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
                logo->setAlpha(i);
                this->renderPresent();
                SDL_Delay(20);
            }
        }
        this->ParseEvents(this->data,"");
        alphaFlag = false;
        this->renderClear();
        background->render(background, this->renderer,0,0,2,NULL);
        logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
        if(this->state->onMainMenuStart)
        {
            StartButton->texture->render(StartButton->texture,this->renderer,logoXPos+320,(this->SCREEN_HEIGHT/2)+150,4,NULL);
        }
        if (this->state->onOptionSelection)
        {
            if(BattleButton->is_highlighted)
            {
                BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,5,NULL);
                OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,NULL);
                QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,NULL);
            }
            if (OptionsButton->is_highlighted)
            {
                BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,NULL);
                OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,5,NULL);
                QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,NULL);
            }
            if (QuitButton->is_highlighted)
            {
                BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,NULL);
                OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,NULL);
                QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,5,NULL);
            }

        }
        this->renderPresent();
        SDL_Delay(30);

        if(this->state->transition)
        {
            for(int i = 255; i>=0; i--)
            {
                this->ParseEvents(this->data,"");
                alphaFlag = false;
                this->renderClear();
                background->setAlpha(i);
                background->render(this->state->mainMenuOps->menuBackground, this->renderer,0,0,2,NULL);
                logo->setAlpha(i);
                logo->render(logo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
                if (this->state->onOptionSelection)
                {
                    if(BattleButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,5,NULL);
                        BattleButton->texture->setAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,NULL);
                        OptionsButton->texture->setAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,NULL);
                        QuitButton->texture->setAlpha(i);
                    }
                    if (OptionsButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,NULL);
                        BattleButton->texture->setAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,5,NULL);
                        OptionsButton->texture->setAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,4,NULL);
                        QuitButton->texture->setAlpha(i);
                    }
                    if (QuitButton->is_highlighted)
                    {
                        BattleButton->texture->render(BattleButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,NULL);
                        BattleButton->texture->setAlpha(i);
                        OptionsButton->texture->render(OptionsButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,NULL);
                        OptionsButton->texture->setAlpha(i);
                        QuitButton->texture->render(QuitButton->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+250,5,NULL);
                        QuitButton->texture->setAlpha(i);
                    }

                }
                this->renderPresent();
                SDL_Delay(10);
            }
            this->state->onMainMenuStart= false;
            this->state->onOptionSelection = false;
            this->state->onCharacterSelection = true;
        }
    }
}

void Core::CharacterSelectRun()
{
    //
    //TODO: when multiple players, change color modulation
    //This compiles properly
    for(std::vector<PlayerObject*>::iterator k = this->players->begin(); k!= this->players->end();k++)
    {
        (*k)->cursor = new PlayerCursor(this->SCREEN_WIDTH/2,this->SCREEN_HEIGHT/2,this->renderer);
        (*k)->cursor->Texture = new GeneralTexture(1,"Pentagram",renderer);
        (*k)->cursor->Texture->loadMenuMedia((*k)->cursor->Texture,this->renderer);
    }
    while(this->state->onCharacterSelection)
    {
        this->ParseEvents(this->data,"");
        this->renderClear();
        for(std::vector<PlayerObject*>::iterator i = this->players->begin(); i!= this->players->end(); i++)
        {
            (*i)->cursor->Move();
            (*i)->cursor->Texture->render((*i)->cursor->Texture,this->renderer,(*i)->cursor->PosX,(*i)->cursor->PosY,1,NULL);
        }
        this->renderPresent();
        SDL_Delay(10);
    }
}

template<class T>
void Core::ParseEvents(ThreadData* data,T* Modify)
{
    if (SDL_TryLockMutex(data->parse_mutex) == 0 && data->interact->size() > 0)
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
            //std::cout<<"DEBUG_TRIGGER."<<std::endl;
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                //std::cout<<"DEBUG_0"<<std::endl;
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_PRESSED)
                {
                    //std::cout<<"trigger"<<std::endl;
                    for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                           // std::cout<<"DEBUG_0_P"<<std::endl;
                            (*j)->cursor->VelY += 1*(*j)->cursor->CURSOR_VEL;
                        }
                    }

                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_PRESSED)
                {
                   for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY += -1*(*j)->cursor->CURSOR_VEL;
                        }
                    }
                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_PRESSED)
                {
                    //std::cout<<"DEBUG_6"<<std::endl;
                   for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX += -1*(*j)->cursor->CURSOR_VEL;
                        }
                    }
                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_PRESSED)
                {
                    //std::cout<<"DEBUG_8"<<std::endl;
                   for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX += 1*(*j)->cursor->CURSOR_VEL;
                        }
                    }
                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_START && (*i)->pressed == SDL_PRESSED)
                {
                    //std::cout<<"DEBUG_8"<<std::endl;
                   for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            this->state->onCharacterSelection=false;
                            this->state->onLevelSelction=false;
                            this->state->onMainMenuStart=false;
                            this->state->onRunningMatch =false;
                            this->quit_program =true;
                        }
                    }
                }
                //SDL_RELEASED

                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN && (*i)->pressed == SDL_RELEASED)
                {
                    //std::cout<<"DEBUG_10"<<std::endl;
                   for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            std::cout<<"DEBUG_0_R"<<std::endl;
                            (*j)->cursor->VelY += -1*(*j)->cursor->CURSOR_VEL;
                        }
                    }
                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && (*i)->pressed == SDL_RELEASED)
                {
                    //std::cout<<"DEBUG_12"<<std::endl;
                    for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelY += 1*(*j)->cursor->CURSOR_VEL;
                        }
                    }
                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_LEFT && (*i)->pressed == SDL_RELEASED)
                {
                    //std::cout<<"DEBUG_14"<<std::endl;
                    for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX += 1*(*j)->cursor->CURSOR_VEL;
                        }
                    }
                }
                if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && (*i)->pressed == SDL_RELEASED)
                {
                    //std::cout<<"DEBUG_16"<<std::endl;
                    for(std::vector<PlayerObject*>::iterator j = this->players->begin(); j!= this->players->end(); j++)
                    {
                        if(SDL_GameControllerFromInstanceID((*i)->controller_id) == (*j)->controller)
                        {
                            (*j)->cursor->VelX += -1*(*j)->cursor->CURSOR_VEL;
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
        else if (this->state->onRunningMatch)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                //std::cout <<"ControllerID: "<< (*i)->controller_id << std::endl;
            }
        }
    }
    data->interact->clear();
    SDL_UnlockMutex(data->parse_mutex);
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
                if (SDL_TryLockMutex(channel->parse_mutex) == 0)
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
