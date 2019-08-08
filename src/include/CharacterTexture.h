#ifndef   CHARACTERTEXTURE_H_
#define   CHARACTERTEXTURE_H_
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
class CharacterTexture : public Texture
{
public:
    //Constructors
    //totalIdleClips, totalJumpingClips, totalFallingClips, totalMovementClips, totalRegularAttackClips, totalStrongAttackClips
    //^^^The six int's at beginning of CharacterTexture();^^^
    CharacterTexture(int,int,int,int,int,int,std::string,SDL_Renderer*);
    //////////////////////////////////////////
    ~CharacterTexture();
    //These functions are not derived
    bool loadCharacterFromFile( std::string, CharacterTexture*, SDL_Renderer*,char);
    bool loadCharacterMedia(CharacterTexture*, SDL_Renderer*);
    void render(CharacterTexture *, SDL_Renderer*, int, int, int, int, int, SDL_Rect*,char);
    int  GetIdleClipCount();
    int  GetJumpingClipCount();
    int  GetFallingClipCount();
    int  GetMoveingClipCount();
    int  GetRegularClipCount();
    int  GetStrongClipCount();
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
    SDL_Texture*    movementTexture;
    SDL_Texture*    attackRegularTexture;
    SDL_Texture*    attackStrongTexture;


    SDL_Rect*    idleClips;
    SDL_Rect*    jumpingClips;
    SDL_Rect*    fallingClips;
    SDL_Rect*    movementClips;
    SDL_Rect*    attackRegularClips;
    SDL_Rect*    attackStrongClips;

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
    int movementClipCount;
    int attackRegularClipCount;
    int attackStrongClipCount;
    ////////////////////////////////
};
#endif
