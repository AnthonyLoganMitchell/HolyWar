#include "Core.h"
Core::Core()
{

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
            gameController = SDL_GameControllerOpen( 0 );
            if( gameController == NULL )
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
        window = SDL_CreateWindow( "HolyWar", 500, 20, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {

            //Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL )
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
    window        = NULL;
    renderer      = NULL;
    gameController= NULL;
    SDL_GameControllerClose(gameController);
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();
}

void Core::EventHandler(SDL_Event e)
{
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
                yPos=-5;
            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_UP) ==1)
            {
                yPos=5;
            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT) ==1)
            {
                xPos=-5;
            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ==1)
            {
                xPos=5;
            }
        }// BUTTONDOWN
        else if(e.type == SDL_CONTROLLERBUTTONUP)
        {
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_DOWN) ==0 )
            {
                yPos=0;
            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_UP) ==0)
            {
                yPos=0;
            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT) ==0)
            {
                xPos=0;
            }
            if(SDL_GameControllerGetButton(gameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ==0)
            {
                xPos=0;
            }

        }

    }
}
