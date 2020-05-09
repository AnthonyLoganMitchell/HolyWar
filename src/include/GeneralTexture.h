/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
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
    bool loadGeneralTextureFromFile( std::string, SDL_Renderer*);
    bool loadMedia(SDL_Renderer*);
    void render(SDL_Renderer*, int, int, int, int, int, SDL_Rect*);


    //These functions are generic and abstract in base class//
    int  GetWidth();
    int  GetHeight();
    void SetWidth(int);
    void SetHeight(int);
    int  GetXPos();
    int  GetYPos();
    void SetXPos(int);
    void SetYPos(int);
    void SetBlendMode( SDL_BlendMode blending );
    void SetAlpha(Uint8 alpha);
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
    bool isStartingPlatform;
    bool isOccupied;

private:
   //Common Across all derived
    std::string name;
    int width;
    int height;
    int frameCount;
    ////////////////

};
#endif
