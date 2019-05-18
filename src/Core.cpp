#include "Core.h"
Core::Core()
{
    this->window = NULL;
    this->renderer = NULL;
    this->gameController = NULL;
    this->quit_program =NULL;
    this->Tick = 0;
    this->OnMainMenu = false;
    this->onLevelSelction = false;
    this->onCharacterSelection = false;
    this->onRunningMatch = false;
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

        if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
            //TODO: Add small while loop or for to collect all controllers and
            this->gameController = SDL_GameControllerOpen( 0 );
            if( this->gameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
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
    this->gameController= NULL;
    SDL_GameControllerClose(gameController);
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();
}

void Core::EventHandler(SDL_Event e)
{

//TODO: Start here and make new class for background textures and level textures(possible use for inheritance).
    while( SDL_PollEvent( &e ))
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit_program = true;
        }
        else if(e.type == SDL_CONTROLLERBUTTONDOWN)
        {
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_DOWN) ==1 )
            {

            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_UP) ==1)
            {

            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT) ==1)
            {

            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ==1)
            {

            }
        }// BUTTONDOWN
        else if(e.type == SDL_CONTROLLERBUTTONUP)
        {
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_DOWN) ==0 )
            {

            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_UP) ==0)
            {

            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT) ==0)
            {

            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ==0)
            {

            }

        }

    }
}
void  Core::CoreMainMenuRun(SDL_Event *e)
{

    //TODO: Now that experimental placement is done, do correct screen width justification of Main Logo Texture
    //and split the logo into two parts

    this->renderClear();
    MenuTexture *menuLogo = new MenuTexture(1,"MainMenuLogo");
    MenuTexture *torch_1 = new MenuTexture(7,"MainMenuTorch");
    MenuTexture *torch_2 = new MenuTexture(7,"MainMenuTorch");
    MenuTexture *menuBackground = new MenuTexture(1, "MainMenuBackground");
    menuBackground->loadMenuMedia(menuBackground,this->renderer);
    menuLogo->loadMenuMedia(menuLogo,this->renderer);
    torch_1->loadMenuMedia(torch_1,this->renderer);
    torch_2->loadMenuMedia(torch_2,this->renderer);

    torch_2->SetFrameCount(5);
    int logoXPos = 0;

    int scale = 0;
    if (this->SCREEN_WIDTH > 1366)
    {
        scale = 3;
        logoXPos = ((this->SCREEN_WIDTH/2 - menuLogo->GetWidth())- menuLogo->GetWidth()/2);
    }
    else
    {
        logoXPos = ((this->SCREEN_WIDTH/2 - menuLogo->GetWidth())- menuLogo->GetWidth()/2); // << this will be changed.
        scale = 2;
    }

    while (this->OnMainMenu)
    {
        this->renderClear();
        menuBackground->render(menuBackground,this->renderer,0,0,2,NULL);
        menuLogo->render(menuLogo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4,scale,NULL);
        torch_1->render(torch_1,this->renderer,logoXPos-torch_1->GetWidth()/4,this->SCREEN_HEIGHT/4+100,scale,&torch_1->animation[torch_1->GetFrameCount()]);
        torch_2->render(torch_2,this->renderer,logoXPos+menuLogo->GetWidth()+torch_2->GetWidth()-30,this->SCREEN_HEIGHT/4+100,scale,&torch_2->animation[torch_1->GetFrameCount()]);
        torch_1->TickFrameCount();
        torch_2->TickFrameCount();
        this->renderPresent();

        if (torch_1->GetFrameCount()== torch_1->textureClipCount)
        {
            torch_1->SetFrameCount(0);
        }
        if (torch_2->GetFrameCount()== torch_2->textureClipCount)
        {
            torch_2->SetFrameCount(0);
        }
        SDL_Delay(100);
    }
}
