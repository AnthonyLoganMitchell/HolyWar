#ifndef EVENT_H_
#define EVENT_H_
#include "Globals.h"

void EventHandler(SDL_Event e)
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
#endif // EVENT_H_
