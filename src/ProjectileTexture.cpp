/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/


#include "ProjectileTexture.h"
//TODO LoadMedia for Projectiles.
bool ProjectileTexture::loadProjectileMedia(SDL_Renderer* renderer) {
    if (this->name == "TODO SOMETHING") {

        return true;
    }
    return false;
}

bool ProjectileTexture::loadProjectileFromFile(std::string path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "ProjectileTexture::loadProjectileFromFile - Unable to load image %s!  SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    } else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "ProjectileTexture::loadProjectileFromFile - Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            return false;
        } else {
            //Get image dimensions
            this->SetWidth(loadedSurface->w);
            this->SetHeight(loadedSurface->h);
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    this->texture = newTexture;
    return true;

}


void ProjectileTexture::render(SDL_Renderer* renderer, int x, int y,int scale, int offset_width, int offset_height, SDL_Rect* clip, SDL_RendererFlip flip) {
    if (scale < 1) {
        scale = 1;
    }
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, this->GetWidth(), this->GetHeight() };
    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = (clip->w*scale)+offset_width;
        renderQuad.h = (clip->h*scale)+offset_height;
    }
    SDL_RenderCopyEx(renderer,this->texture,clip,&renderQuad,0.0,NULL,flip);
}

int ProjectileTexture::GetWidth() {
    return this->width;
}

int ProjectileTexture::GetHeight() {
    return this->height;
}

void ProjectileTexture::SetWidth(int w) {
 this->width = w;
}
void ProjectileTexture::SetHeight(int h) {
    this->height = h;
}
void ProjectileTexture::SetFrameCount(int count) {
    this->frameCount = count;
}
int ProjectileTexture::GetFrameCount() {
    return this->frameCount;
}
int ProjectileTexture::GetXPos() {
    return this->xposition;
}
int ProjectileTexture::GetYPos() {
    return this->yposition;
}
void ProjectileTexture::SetXPos(int x) {
    this->xposition = x;
}
void ProjectileTexture::SetYPos(int y) {
    this->yposition = y;
}

void ProjectileTexture::Free_Texture() {
    delete(this);
}
