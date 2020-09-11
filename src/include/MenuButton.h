/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <string>
class SDL_Renderer;
class GeneralTexture;
class MenuButton
{
    public:
        MenuButton();
        MenuButton(int,std::string , SDL_Renderer*);
        virtual ~MenuButton();
        GeneralTexture* texture;
        //template<class T>
        //static T (*func)();
        bool is_highlighted;
};

#endif // MENUBUTTON_H
