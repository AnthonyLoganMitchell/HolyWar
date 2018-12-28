#ifndef   MENUTEXTURE_H_
#define   MENUTEXTURE_H_
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
class MenuTexture : public Texture
{
public:
    //Constructors
    //total clips/name/xpos/ypos
    MenuTexture(int,std::string,int,int); // Going to fix CharacterTexture class first
    //////////////////////////////////////////

    //These functions are not derived
    bool loadMenuTextureFromFile( std::string, MenuTexture*, SDL_Renderer*);
    bool loadMenuMedia(MenuTexture*, SDL_Renderer*);
    void render(MenuTexture *, SDL_Renderer*, int, int, int, SDL_Rect*);


    //These functions are generic and abstract in base class//
    int  GetWidth();
    int  GetHeight();
    void SetWidth(int);
    void SetHeight(int);
    int GetXPos();
    int GetYPos();
    void SetXPos(int);
    void SetYPos(int);
    void SetFrameCount(int);
    void TickFrameCount();
    int  GetFrameCount();
    void Free_Texture();
    ///////////////////////////////////////////////////////////
    SDL_Texture* texture;
    SDL_Rect* animation;

private:
   //Common Across all derived
    std::string name;
    int textureClipCount;
    int width;
    int height;
    int xposition;
    int yposition;
    int frameCount;
    ////////////////

};

#endif
