#ifndef   GENERALTEXTURE_H_
#define   GENERALTEXTURE_H_
#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
class GeneralTexture : public Texture
{
public:
    //Constructors
    //total clips/name/xpos/ypos
    GeneralTexture(int,std::string,SDL_Renderer*); // Going to fix CharacterTexture class first
    //////////////////////////////////////////

    //These functions are not derived
    bool loadGeneralTextureFromFile( std::string, GeneralTexture*, SDL_Renderer*);
    bool loadMedia(GeneralTexture*, SDL_Renderer*);
    void render(GeneralTexture*, SDL_Renderer*, int, int, int, int, SDL_Rect*);


    //These functions are generic and abstract in base class//
    int  GetWidth();
    int  GetHeight();
    void SetWidth(int);
    void SetHeight(int);
    int GetXPos();
    int GetYPos();
    void SetXPos(int);
    void SetYPos(int);
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha(Uint8 alpha);
    void SetFrameCount(int);
    void TickFrameCount();
    void ResetFrameCount();
    int  GetFrameCount();
    void Free_Texture();
    ///////////////////////////////////////////////////////////
    SDL_Texture* texture;
    SDL_Rect* animation;
    int xposition;
    int yposition;
    int textureClipCount;

private:
   //Common Across all derived
    std::string name;
    int width;
    int height;
    int frameCount;
    ////////////////

};
#endif
