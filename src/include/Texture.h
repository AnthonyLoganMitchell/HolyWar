#ifndef   TEXTURE_H_
#define   TEXTURE_H_
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


class CharacterTexture
{
public:
    std::string name;
    CharacterTexture();
    CharacterTexture(int,std::string,int,int);
    CharacterTexture *initCharacterTexture(std::string);
    bool loadFromFile( std::string, CharacterTexture*, SDL_Renderer*);
    bool loadCharacterMedia(CharacterTexture*, SDL_Renderer*);
    void InitTexture();
    void render(CharacterTexture *, SDL_Renderer*, int, int, int, SDL_Rect*);
    int  GetWidth();
    int  GetHeight();
    int  GetSpriteCount();
    void SetWidth(int);
    void SetHeight(int);
    void SetFrameCount(int);
    void TickFrameCount();
    int  GetFrameCount();
    void Free_Texture();
    bool deleteTexture(CharacterTexture *);

    SDL_Texture* texture;
    SDL_Rect*    idleClips;
    SDL_Rect*    jumpingClips;
    SDL_Rect*    fallingClips;
    SDL_Rect*    movementClips;
    SDL_Rect*    attackRegularClips;
    SDL_Rect*    strongAttackClips;
    int  xposition;
    int  yposition;


private:
    int width;
    int height;
    int frameCount;
    int spriteCount;
    bool isInitialized;
};

#endif
