#include "Core.h"
#include <vector>
Core::Core()
{
    this->window = NULL;
    this->renderer = NULL;
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
        window = SDL_CreateWindow( "HolyWar", 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SDL_WINDOW_SHOWN );
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
    //Object Texture initialization.
    /////////////////////////////////////////////////////////////////////////
    MenuTexture *menuBackground = new MenuTexture(1, "SplashBackground");
    MenuTexture *menuLogo = new MenuTexture(1,"MainMenuLogo");
    //////////////////////////////////////////////////////////////////////////

    //Load media for each texture into memory.
    //////////////////////////////////////////////////////////////////////////
    menuBackground->loadMenuMedia(menuBackground,this->renderer);
    menuLogo->loadMenuMedia(menuLogo,this->renderer);
    //////////////////////////////////////////////////////////////////////////

    int logoXPos = 0;
    logoXPos = this->SCREEN_WIDTH/2-430;
    bool alphaFlag = true;
    while (this->OnMainMenu)
    {
        if (alphaFlag)
        {
            for (int i=0; i<256; i++)
            {
                this->renderClear();
                menuBackground->render(menuBackground, this->renderer,0,0,2,NULL);
                menuBackground->setAlpha(i);
                menuLogo->render(menuLogo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
                menuLogo->setAlpha(i);
                this->renderPresent();
                SDL_Delay(30);

            }
        }
        alphaFlag = false;
        this->renderClear();
        menuBackground->render(menuBackground, this->renderer,0,0,2,NULL);
        menuLogo->render(menuLogo,this->renderer,logoXPos,this->SCREEN_HEIGHT/4-100,1,NULL);
        this->renderPresent();
        SDL_Delay(30);
    }
}
