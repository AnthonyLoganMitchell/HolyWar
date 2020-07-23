/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*///
#include "CharacterTexture.h"

CharacterTexture::CharacterTexture(int totalIdleClips,int totalJumpingClips,int totalFallingClips,int totalWalkingClips,int totalRunningClips,int totalRegularAttackClips,\
                                   int totalRegularAttackClips2,int totalRegularJumpingAttackClips,int totalStrongAttackClips,int totalSpecialOpen, int totalSpecialOpenCharacter, std::string n,SDL_Renderer* rend) : Texture() {
    this->idleTexture = NULL;
    this->attackRegularTexture = NULL;
    this->walkingTexture = NULL;
    this->runningTexture = NULL;
    this->fallingTexture = NULL;
    this->attackStrongTexture = NULL;
    this->attackRegularJumpingTexture = NULL;
    this->name        = n;
    this->frameCount  = 0;
    this->xposition   = 0;
    this->yposition   = 0;

    this->idleClipCount = totalIdleClips-1;
    this->idleClips   = new SDL_Rect[totalIdleClips];

    this->jumpingClipCount = totalJumpingClips-1;
    this->jumpingClips = new SDL_Rect[totalJumpingClips];

    this->fallingClipCount = totalFallingClips-1;
    this->fallingClips = new SDL_Rect[totalFallingClips];

    this->walkingClipCount = totalWalkingClips-1;
    this->walkingClips = new SDL_Rect[totalWalkingClips];

    this->runningClipCount =  totalRunningClips -1;
    this->runningClips = new SDL_Rect[totalRunningClips];

    this->attackRegularClipCount = totalRegularAttackClips-1;
    this->attackRegularClips = new SDL_Rect[totalRegularAttackClips];

    this->attackRegularClipCount2 = totalRegularAttackClips2-1;
    this->attackRegularClips2 = new SDL_Rect[totalRegularAttackClips2];

    this->attackRegularJumpingClipCount = totalRegularJumpingAttackClips-1;
    this->attackRegularJumpingClips = new SDL_Rect[totalRegularJumpingAttackClips];

    this->attackStrongClipCount = totalStrongAttackClips-1;
    this->attackStrongClips = new SDL_Rect[totalStrongAttackClips];

    this->attackSpecialOpenClipCount = totalSpecialOpen-1;
    this->attackSpecialOpenClips = new SDL_Rect[totalSpecialOpen];

    this->attackSpecialOpenCharacterClipCount = totalSpecialOpenCharacter-1;
    this->attackSpecialOpenCharacterClips = new SDL_Rect[totalSpecialOpenCharacter];
    //THESE HAVE TO BE == 1
    //Cant divide by zero....
    this->idleMod =1;
    this->jumpingMod =1;
    this->walkMod = 1;
    this->runMod = 1;
    this->fallingMod = 1;
    this->attackRegMod =1;
    this->attackRegMod2 =1;
    this->attackRegJumpingMod=1;
    this->attackStrongMod =1;
    this->attackSpecialOpenMod = 1;
    this->attackSpecialOpenCharacterMod = 1;
    this->loadCharacterMedia(rend);
}
CharacterTexture::~CharacterTexture() {
    //TODO: Delete all textures on the heap.

}

bool CharacterTexture::loadCharacterFromFile(std::string path,SDL_Renderer* renderer,std::string t_type) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    bool load_flag = false;
    if( loadedSurface == NULL ) {
        printf( "CharacterTexture::LoadCharacterFromFile - Unable to load image %s!  SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "CharacterTexture::LoadCharacterFromFile - Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        } else {
            //Get image dimensions
            this->SetWidth(loadedSurface->w);
            this->SetHeight(loadedSurface->h);
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    //Return success
    if(t_type == "I") {
        this->idleTexture = newTexture;
        load_flag = true;
    } else if( t_type == "J") {
        this->jumpingTexture = newTexture;
        load_flag = true;
    } else if(t_type =="F") {
        this->fallingTexture = newTexture;
        load_flag = true;
    } else if(t_type == "W") {
        this->walkingTexture = newTexture;
        load_flag = true;
    } else if(t_type == "R") {
        this->runningTexture = newTexture;
        load_flag = true;
    } else if(t_type == "A") {
        this->attackRegularTexture = newTexture;
        load_flag = true;
    } else if(t_type == "A2") {
        this->attackRegularTexture2 = newTexture;
        load_flag = true;
    } else if (t_type == "JA") {
        this->attackRegularJumpingTexture = newTexture;
        load_flag = true;
    } else if(t_type == "S1") {
        this->attackStrongTexture = newTexture;
        load_flag = true;
    } else if(t_type == "SAO") {
        this->attackSpecialOpenTexture = newTexture;
        load_flag = true;
    } else if (t_type == "SAOC") {
        this->attackSpecialOpenCharacterTexture = newTexture;
        load_flag = true;
    }
    return load_flag;
}


void CharacterTexture::render(SDL_Renderer* renderer, int x, int y,int scale, int offset_width, int offset_height, SDL_Rect* clip, std::string t_type, SDL_RendererFlip flip) {
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
    //Render to screen
    if(t_type == "I") {
        SDL_RenderCopyEx(renderer,this->idleTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "J") {
        SDL_RenderCopyEx(renderer,this->jumpingTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "F") {
        SDL_RenderCopyEx(renderer,this->fallingTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "W") {
        SDL_RenderCopyEx(renderer,this->walkingTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "R") {
        SDL_RenderCopyEx(renderer,this->runningTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "A") {
        SDL_RenderCopyEx(renderer,this->attackRegularTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "A2") {
        SDL_RenderCopyEx(renderer,this->attackRegularTexture2,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "JA") {
        SDL_RenderCopyEx(renderer,this->attackRegularJumpingTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "S1") {
        SDL_RenderCopyEx(renderer,this->attackStrongTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "SAO") {
        SDL_RenderCopyEx(renderer,this->attackSpecialOpenTexture,clip,&renderQuad,0.0,NULL,flip);
    } else if(t_type == "SAOC") {
        SDL_RenderCopyEx(renderer,this->attackSpecialOpenCharacterTexture,clip,&renderQuad,0.0,NULL,flip);
    }
}

bool CharacterTexture::loadCharacterMedia(SDL_Renderer* renderer) {
    //Loading success flag
    //Load sprite sheet texture
    if(this->name == "jesus") {
        if(!this->loadCharacterFromFile("../../rec/animations/characters/jesus/jesus-idle.png",renderer,"I")) {
            printf( "Failed to load sprite sheet texture! jesus-idle.png\n" );
            return false;
        } else {
            //Set top left sprite
            this-> idleClips[ 0 ].x = 2;
            this-> idleClips[ 0 ].y = 0;
            this-> idleClips[ 0 ].w = 38;
            this-> idleClips[ 0 ].h = 40;

            this-> idleClips[1].x = 43;
            this-> idleClips[1].y = 0;
            this-> idleClips[1].w = 38;
            this-> idleClips[1].h = 40;

            this-> idleClips[2].x = 84;
            this-> idleClips[2].y = 0;
            this-> idleClips[2].w = 38;
            this-> idleClips[2].h = 40;

            this-> idleClips[3].x = 125;
            this-> idleClips[3].y = 0;
            this-> idleClips[3].w = 38;
            this-> idleClips[3].h = 40;

            this-> idleClips[4].x = 166;
            this-> idleClips[4].y = 0;
            this-> idleClips[4].w = 38;
            this-> idleClips[4].h = 40;

            this-> idleClips[5].x = 207;
            this-> idleClips[5].y = 0;
            this-> idleClips[5].w = 38;
            this-> idleClips[5].h = 40;

            this-> idleClips[6].x = 248;
            this-> idleClips[6].y = 0;
            this-> idleClips[6].w = 38;
            this-> idleClips[6].h = 40;

            this-> idleClips[7].x = 289;
            this-> idleClips[7].y = 0;
            this-> idleClips[7].w = 38;
            this-> idleClips[7].h = 40;
        }

        //TODO: Load more of jesus's textures here before return. (movement,attacking,jumping,falling,ect...)
        return true;
    }//End of jesus textures.
    if(this->name == "Horus") {
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_idle.png",renderer,"I")) {
            printf( "Failed to load sprite sheet texture! horus_idle.png\n" );
            return false;
        } else {
            int width = 79;
            int x_pos = 1;
            for (int i =0; i<18; i++) {
                this->idleClips[i].x = x_pos;
                this->idleClips[i].y =1;
                this->idleClips[i].w =79;
                this->idleClips[i].h =65;
                x_pos = x_pos + width + 1;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_walk.png",renderer,"W")) {
            printf( "Failed to load sprite sheet texture! horus_walk.png\n" );
            return false;
        } else {
            int width = 80;
            int x_pos = 1;
            for (int i = 0; i<17; i++) {
                this->walkingClips[i].x = x_pos;
                this->walkingClips[i].y = 1;
                this->walkingClips[i].w = 80;
                this->walkingClips[i].h = 65;
                x_pos = x_pos + width;
            }
        }

        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_run.png",renderer,"R")) {
            printf( "Failed to load sprite sheet texture! horus_run.png\n" );
            return false;
        } else {
            int width = 80;
            int x_pos = 1;
            for (int i = 0; i<13; i++) {
                this->runningClips[i].x = x_pos;
                this->runningClips[i].y = 1;
                this->runningClips[i].w = 80;
                this->runningClips[i].h = 65;
                x_pos = x_pos + width;
            }
        }

        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_jump.png", renderer,"J")) {
            printf( "Failed to load sprite sheet texture! horus_jump.png\n" );
            return false;
        } else {
            int width = 80;
            int x_pos = 1;
            for (int i = 0; i<11; i++) {
                this->jumpingClips[i].x = x_pos;
                this->jumpingClips[i].y =1;
                this->jumpingClips[i].w =80;
                this->jumpingClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_falling.png",renderer, "F")) {
            printf( "Failed to load sprite sheet texture! horus_falling.png\n" );
            return false;
        } else {
            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<6; i++) {
                this->fallingClips[i].x = x_pos;
                this->fallingClips[i].y =1;
                this->fallingClips[i].w =85;
                this->fallingClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_reg_attack_1.png",renderer, "A")) {
            printf( "Failed to load sprite sheet texture! horus_reg_attack_1.png\n" );
            return false;
        } else {

            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<14; i++) {
                this->attackRegularClips[i].x = x_pos;
                this->attackRegularClips[i].y =1;
                this->attackRegularClips[i].w =85;
                this->attackRegularClips[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_reg_attack_2.png",renderer,"A2")) {
            printf( "Failed to load sprite sheet texture! horus_reg_attack_2.png\n" );
            return false;
        } else {
            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<16; i++) {
                this->attackRegularClips2[i].x = x_pos;
                this->attackRegularClips2[i].y =1;
                this->attackRegularClips2[i].w =85;
                this->attackRegularClips2[i].h =65;
                x_pos = x_pos + width;
            }
        }
        if(!this->loadCharacterFromFile("../../rec/animations/characters/horus/horus_jumping_regular_attack.png",renderer,"JA")) {
            printf( "Failed to load sprite sheet texture! horus_jumping_regular_attack.png\n" );
            return false;
        } else {
            int width = 85;
            int x_pos = 1;
            for (int i = 0; i<13; i++) {
                this->attackRegularJumpingClips[i].x = x_pos;
                this->attackRegularJumpingClips[i].y =1;
                this->attackRegularJumpingClips[i].w =85;
                this->attackRegularJumpingClips[i].h =65;
                x_pos = x_pos + width;
            }
        } 
        if(!this->loadCharacterFromFile("../../rec/animations/character/horus/horus_special_open.png",renderer,"SAO")) {
             printf( "Failed to load sprite sheet texture! horus_special_open.png\n" );
             return false;
        } else {
            int width = 16;
            int height= 16;
            int x_pos = 1;
            int y_pos = 1;

            for (int j = 0; j<28; j++) {
                this->attackSpecialOpenClips[j].x = x_pos;
                this->attackSpecialOpenClips[j].y = y_pos;
                this->attackSpecialOpenClips[j].w = width;
                this->attackSpecialOpenClips[j].h = height; 
                x_pos = x_pos  +  width;
                if(j%4) {
                    x_pos = 1;  
                    y_pos = y_pos + height; 
                }
            }
            
        }
        if(!this->loadCharacterFromFile("../../rec/animations/character/horus/horus_special_open_character.png",renderer,"SAOC")) {
            printf("Failed to load sprite sheet texture! horus_special_open_character.png\n");
            return false;
        } else {
            int width = 80;
            int x_pos = 1;
            for (int i = 0; i<9; i++) {
                this->attackSpecialOpenCharacterClips[i].x = x_pos;
                this->attackSpecialOpenCharacterClips[i].y = 1;
                this->attackSpecialOpenCharacterClips[i].w = width;
                this->attackSpecialOpenCharacterClips[i].h = 65;    
                x_pos = x_pos + width;            
            }
        }
        return true;
    }
    return false;
}


int CharacterTexture::GetIdleClipCount() {
    return this->idleClipCount;
}
int CharacterTexture::GetJumpingClipCount() {
    return this->jumpingClipCount;
}
int CharacterTexture::GetFallingClipCount() {
    return this->fallingClipCount;
}
int CharacterTexture::GetWalkingClipCount() {
    return this->walkingClipCount;
}
int CharacterTexture::GetRunningClipCount() {
    return this->runningClipCount;
}
int CharacterTexture::GetRegularAttackClipCount() {
    return this->attackRegularClipCount;
}
int CharacterTexture::GetRegularAttackClipCount2() {
    return this->attackRegularClipCount2;
}

int CharacterTexture::GetJumpingRegularAttackClipCount() {
    return this->attackRegularJumpingClipCount;
}
int CharacterTexture::GetStrongClipCount() {
    return this->attackStrongClipCount;
}
int CharacterTexture::GetSpecialOpenAttackClipCount() {
    return this->attackSpecialOpenClipCount;
}
int CharacterTexture::GetSpecialOpenAttackCharacterClipCount() {
    return this->attackSpecialOpenCharacterClipCount;
}

void CharacterTexture::SetFrameCount(int x) {
    this->frameCount = x;
}

int CharacterTexture::GetFrameCount() {
    return this->frameCount;
}

void CharacterTexture::TickFrameCount() {
    frameCount++;
}

void CharacterTexture::SetWidth(int x) {
    this->width = x;
}

void CharacterTexture::SetHeight(int x) {
    this->height = x;
}

int CharacterTexture::GetWidth() {
    return width;
}

int CharacterTexture::GetHeight() {
    return height;
}

void CharacterTexture::Free_Texture() {
    //Free texture if it exists
    if( this->idleTexture != NULL ) {
        this->idleTexture = NULL;
        SDL_DestroyTexture( this->idleTexture);
    }
}

int CharacterTexture::GetXPos() {
    return this->xposition;
}

int CharacterTexture::GetYPos() {
    return this->yposition;
}

void CharacterTexture::SetXPos(int x) {
    this->xposition = x;
}

void CharacterTexture::SetYPos(int y) {
    this->yposition = y;
}
