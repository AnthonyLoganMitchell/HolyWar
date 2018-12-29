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
void  Core::CoreMainMenuRun()
{
    //std::cout << "\n" <<this->SCREEN_HEIGHT/4 << std::endl;
    this->renderClear();
    MenuTexture *mainMenu = new MenuTexture(1,"MainMenuLogo", (this->SCREEN_WIDTH/4)+50, (this->SCREEN_HEIGHT/4));
    MenuTexture *torch_1 = new MenuTexture(7,"MainMenuTorch", (this->SCREEN_WIDTH/4)+50, (this->SCREEN_HEIGHT/2));
    MenuTexture *torch_2 = new MenuTexture(7,"MainMenuTorch", ((this->SCREEN_WIDTH/4)*3), (this->SCREEN_HEIGHT/2));
    mainMenu->loadMenuMedia(mainMenu,this->renderer);
    torch_1->loadMenuMedia(torch_1,this->renderer);
    torch_2->loadMenuMedia(torch_2,this->renderer);
    while (!this->quit_program)
    {

            mainMenu->render(mainMenu,this->renderer,mainMenu->xposition,mainMenu->yposition,3,NULL);
            torch_1->render(torch_1,this->renderer,torch_1->xposition,torch_1->yposition,4,&torch_1->animation[torch_1->GetFrameCount()]);
            torch_2->render(torch_2,this->renderer,torch_2->xposition,torch_2->yposition,4,&torch_2->animation[torch_1->GetFrameCount()]);
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

//Initialize and load textures for background and menu options
//Design the main menu loop.


}
