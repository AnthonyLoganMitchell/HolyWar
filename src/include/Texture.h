#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
class Texture
{
public:
    Texture();
    virtual void Free_Texture()=0;
    virtual int  GetWidth()=0;
    virtual int  GetHeight()=0;
    virtual void SetWidth(int)=0;
    virtual void SetHeight(int)=0;
    virtual void SetFrameCount(int)=0;
    virtual int  GetFrameCount()=0;
    virtual int  GetXPos()=0;
    virtual int  GetYPos()=0;
    virtual void SetXPos(int)=0;
    virtual void SetYPos(int)=0;

private:

};
#endif // TEXTURE_H_
