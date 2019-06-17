#include "Core.h"
#include <vector>
#include "MainMenuOptions.h"
Core::Core()
{
    this->window = NULL;
    this->renderer = NULL;
    this->quit_program =NULL;
    this->tick = 0;
    this->state->onMainMenuStart = true;
    this->state->onOptionSelection = false;
    this->state->onLevelSelction = false;
    this->state->onCharacterSelection = false;
    this->state->onRunningMatch = false;
    this->data= new(ThreadData);
    this->data->parse_mutex = SDL_CreateMutex();
    this->data->interact = new(std::vector<Interaction*>);
}
void Core::renderPresent()
{
    SDL_RenderPresent(renderer);
}
void Core::renderClear()
{
    SDL_RenderClear(renderer);
}

bool Core::CoreInit(SDL_GameController* gameControllers[])
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

        if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
            //TODO: Add small while SDL_NumJoysticks()loop or for to collect all controllers and
            for(int i = 0; i <SDL_NumJoysticks(); i++)
            {
                if (SDL_IsGameController(i))
                {
                    gameControllers[i] = SDL_GameControllerOpen(i);
                }
            }
        }
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
    IMG_Quit();
    SDL_Quit();
}

void  Core::CoreMainMenuRun()
{
    this->state->MM_OPS = new MainMenuOptions(this->renderer);
    this->state->MM_OPS->menuStart->is_option = true;


    int logoXPos = 0;
    logoXPos = this->SCREEN_WIDTH/2-430;
    bool alphaFlag = true;
    while (this->state->onMainMenuStart || this->state->onOptionSelection)
    {
        if (alphaFlag)  //TODO: add short circuit here for user pressing start to skip into Alpha blend.
        {
            for (int i=0; i<256; i++)
            {
                this->ParseEvents(this->data,"");
                this->renderClear();
                this->state->MM_OPS->menuBackground->render(this->state->MM_OPS->menuBackground, this->renderer,0,0,2,NULL);
                this->state->MM_OPS->menuBackground->setAlpha(i);
                this->state->MM_OPS->menuLogo->render(this->state->MM_OPS->menuLogo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
                this->state->MM_OPS->menuLogo->setAlpha(i);
                this->renderPresent();
                SDL_Delay(30);

            }
        }
        this->ParseEvents(this->data,"");
        alphaFlag = false;
        this->renderClear();
        this->state->MM_OPS->menuBackground->render(this->state->MM_OPS->menuBackground, this->renderer,0,0,2,NULL);
        this->state->MM_OPS->menuLogo->render(this->state->MM_OPS->menuLogo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
        if(this->state->onMainMenuStart && !this->state->onOptionSelection)
        {
            this->state->MM_OPS->menuStart->texture->render(this->state->MM_OPS->menuStart->texture,this->renderer,logoXPos+320,(this->SCREEN_HEIGHT/2)+150,4,NULL);
        } else if (!this->state->onMainMenuStart && this->state->onOptionSelection)
        {
            if(this->state->MM_OPS->menuBattle->is_option)
            {
              this->state->MM_OPS->menuBattle->texture->render(this->state->MM_OPS->menuBattle->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,5,NULL);
              this->state->MM_OPS->menuOptions->texture->render(this->state->MM_OPS->menuOptions->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,4,NULL);
            } else {
              this->state->MM_OPS->menuBattle->texture->render(this->state->MM_OPS->menuBattle->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+150,4,NULL);
              this->state->MM_OPS->menuOptions->texture->render(this->state->MM_OPS->menuOptions->texture,this->renderer,logoXPos+300,(this->SCREEN_HEIGHT/2)+200,5,NULL);
            }

        }
        this->renderPresent();
        SDL_Delay(30);
    }
}
template<class T>
void Core::ParseEvents(ThreadData* data,T* Modify)
{
    if (SDL_TryLockMutex(data->parse_mutex) == 0 && data->interact->size() > 0)
    {
        if (this->state->onMainMenuStart)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                if((*i)->button_event == SDL_CONTROLLER_BUTTON_START)
                {
                    this->state->onMainMenuStart =false;
                    this->state->onOptionSelection = true;
                    this->state->MM_OPS->menuStart->is_option = false;
                    this->state->MM_OPS->menuBattle->is_option = true;
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
                    this->state->MM_OPS->menuStart->is_option = true;
                }else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_DOWN &&this->state->MM_OPS->menuBattle->is_option)
                {
                    this->state->MM_OPS->menuBattle->is_option = false;
                    this->state->MM_OPS->menuOptions->is_option= true;
                }else if ((*i)->button_event == SDL_CONTROLLER_BUTTON_DPAD_UP && this->state->MM_OPS->menuOptions->is_option)
                {
                    this->state->MM_OPS->menuBattle->is_option = true;
                    this->state->MM_OPS->menuOptions->is_option= false;
                }
            }
        }
        else if (this->state->onLevelSelction)
        {
            for (std::vector<Interaction*>::iterator i = data->interact->begin(); i != data->interact->end(); i++)
            {
                //std::cout <<"ControllerID: "<< (*i)->controller_id << std::endl;
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

            if( event.type == SDL_QUIT )
            {
                quit=true;
            }
            else if(event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
            {
                if (SDL_TryLockMutex(channel->parse_mutex) == 0)
                {
                    inter->button_event = event.cbutton.button;
                    inter->controller_id = event.cbutton.which;
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
