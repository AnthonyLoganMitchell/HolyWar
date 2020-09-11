/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_
class Texture {
public:
    virtual ~Texture(){};
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
