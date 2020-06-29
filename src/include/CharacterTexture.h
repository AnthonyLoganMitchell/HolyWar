/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#ifndef   CHARACTERTEXTURE_H_
#define   CHARACTERTEXTURE_H_
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include <iostream>
class CharacterTexture : public Texture
{
public:
    //Constructors
    //int totalIdleClips,int totalJumpingClips,int totalFallingClips,int totalWalkingClips,int totalRunningClips,int totalRegularAttackClips,
    //int totalRegularAttackClips2,int totalRegularJumpingAttackClips,int totalStrongAttackClips,int totalSpecialOpen, int totalSpecialOpenCharacter
    CharacterTexture(int,int,int,int,int,int,int,int,int,int,int,std::string,SDL_Renderer*);
    //////////////////////////////////////////
    ~CharacterTexture();
    //These functions are not derived
    bool loadCharacterFromFile( std::string,SDL_Renderer*,std::string);
    bool loadCharacterMedia(SDL_Renderer*);
    void render(SDL_Renderer*, int, int, int, int, int, SDL_Rect*,std::string,SDL_RendererFlip);
    int  GetIdleClipCount();
    int  GetJumpingClipCount();
    int  GetFallingClipCount();
    int  GetWalkingClipCount();
    int  GetRunningClipCount();
    int  GetRegularAttackClipCount();
    int  GetRegularAttackClipCount2();
    int  GetJumpingRegularAttackClipCount();
    int  GetStrongClipCount();
    int  GetSpecialOpenAttackClipCount();
    int  GetSpecialOpenAttackCharacterClipCount();
    //These functions are generic and abstract in base class//
    int  GetWidth();
    int  GetHeight();
    void SetWidth(int);
    void SetHeight(int);
    int  GetXPos();
    int  GetYPos();
    void SetXPos(int);
    void SetYPos(int);
    void SetFrameCount(int);
    void TickFrameCount();
    int  GetFrameCount();
    void Free_Texture();
    ///////////////////////////////////////////////////////////

    SDL_Texture*    idleTexture;
    SDL_Texture*    jumpingTexture;
    SDL_Texture*    fallingTexture;
    SDL_Texture*    walkingTexture;
    SDL_Texture*    runningTexture;
    SDL_Texture*    attackRegularTexture;
    SDL_Texture*    attackRegularTexture2;
    SDL_Texture*    attackStrongTexture;
    SDL_Texture*    attackRegularJumpingTexture;
    SDL_Texture*    attackSpecialOpenTexture;
    SDL_Texture*    attackSpecialOpenCharacterTexture;


    SDL_Rect*    idleClips;
    SDL_Rect*    jumpingClips;
    SDL_Rect*    fallingClips;
    SDL_Rect*    walkingClips;
    SDL_Rect*    runningClips;
    SDL_Rect*    attackRegularClips;
    SDL_Rect*    attackRegularClips2;
    SDL_Rect*    attackRegularJumpingClips;
    SDL_Rect*    attackStrongClips;
    SDL_Rect*    attackSpecialOpenClips;
    SDL_Rect*    attackSpecialOpenCharacterClips;

    int idleMod;
    int jumpingMod;
    int fallingMod;
    int walkMod;
    int runMod;
    int attackRegMod;
    int attackRegMod2;
    int attackRegJumpingMod;
    int attackStrongMod;
    int attackSpecialOpenMod;
    int attackSpecialOpenCharacterMod;

private:
    //Common Across all derived
    std::string name;
    int width;
    int height;
    int xposition;
    int yposition;
    int frameCount;
    ////////////////////////////

    //Specific to character Textures
    int idleClipCount;
    int jumpingClipCount;
    int fallingClipCount;
    int walkingClipCount;
    int runningClipCount;
    int attackRegularClipCount;
    int attackRegularClipCount2;
    int attackRegularJumpingClipCount;
    int attackStrongClipCount;
    int attackSpecialOpenClipCount;
    int attackSpecialOpenCharacterClipCount;
    ////////////////////////////////
};
#endif
