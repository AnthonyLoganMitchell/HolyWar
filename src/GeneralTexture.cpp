/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "GeneralTexture.h"
#include <string>
//Fix this constructor.
GeneralTexture::GeneralTexture(int totalClips, std::string texName,SDL_Renderer* rend) {
    this->textureClipCount = totalClips -1;
    this->name = texName;
    this->animation = new SDL_Rect[totalClips];
    this->frameCount = 0;
    this->loadMedia(rend);
    this->xposition=0;
    this->yposition=0;
    this->isStartingPlatform =false;
    this->isOccupied = false;
}

void GeneralTexture::render(SDL_Renderer* renderer, int rend_pos_x, int rend_pos_y, int scale, int offset_width, int offset_height, SDL_Rect* clip ) {
    //Set rendering space and render to screen
    //std::cout << t->GetWidth() << ": " << t->GetHeight() << std::endl;
    SDL_Rect renderQuad = { rend_pos_x+offset_width, rend_pos_y+offset_height,(this->GetWidth()*scale), (this->GetHeight()*scale)};
    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = (clip->w*scale);
        renderQuad.h = (clip->h*scale);
    }
    //Render to screen
    SDL_RenderCopy( renderer, this->texture, clip, &renderQuad );
}
bool GeneralTexture::loadGeneralTextureFromFile( std::string path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        } else {
            //Get image dimensions
            this->SetWidth(loadedSurface->w);
            this->SetHeight(loadedSurface->h);
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    //Return success
    this->texture = newTexture;
    return this->texture != NULL;
}

bool GeneralTexture::loadMedia(SDL_Renderer* renderer) {
    //Loading success flag
    if (this->name == "MainMenuLogo") {
        if (!this->loadGeneralTextureFromFile("../../rec/text/main_menu_logo.png",renderer)) {
            printf( "Failed to load sprite sheet texture: main_menu_logo.png\n" );
            return false;
        } else {
            this->animation[0].x =1;
            this->animation[0].y =1;
            this->animation[0].h =385;
            this->animation[0].w =790;
            return true;
        }
    }
    if (this->name == "PentagramCursor") {
        if(!this->loadGeneralTextureFromFile("../../rec/objects/symbols/pentagram_cursor.png",renderer)) {
            printf("Failed to load sprite sheet texture: pentagram_cursor.png\n");
            return false;
        } else {
            this->animation[0].x = 0;
            this->animation[0].y = 0;
            this->animation[0].w = 20;
            this->animation[0].h = 20;
            return true;
        }
    }
    if (this->name == "FullMoonBlankSky") {

        if (!this->loadGeneralTextureFromFile("../../rec/backgrounds/full_moon_blank_sky.png",renderer)) {
            printf("Failed to load sprite sheet texture: full_moon_blank_sky.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].h = 540;
            this->animation[0].w = 960;
            return true;
        }
    }
    if (this->name == "BlankNightSky") {

        if (!this->loadGeneralTextureFromFile("../../rec/backgrounds/blank_night_sky.png",renderer)) {
            printf("Failed to load sprite sheet texture: blank_night_sky.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].h = 540;
            this->animation[0].w = 960;
            return true;
        }
    }

    if (this->name == "MountainMidground") {
        if (!this->loadGeneralTextureFromFile("../../rec/midgrounds/mountain_midground.png",renderer)) {
            printf("Failed to load sprite sheet texture: mountain_midground\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].h = 185;
            this->animation[0].w = 960;
            return true;
        }
    }

    if (this->name == "RockMidground") {
        if(!this->loadGeneralTextureFromFile("../../rec/midgrounds/rock_midground.png",renderer)) {
            printf("Failed to load sprite sheet texture: rock_midground.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 960;
            this->animation[0].h = 97;
            return true;
        }
    }

    if (this->name == "MidGroundBush") {
        if (!this->loadGeneralTextureFromFile("../../rec/midgrounds/bush_midground.png",renderer)) {
            printf( "Failed to load sprite sheet texture: bush_midground\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 960;
            this->animation[0].h = 49;
            return true;
        }
    }
    if (this->name == "MidGroundForest_1") {
        if (!this->loadGeneralTextureFromFile("../../rec/midgrounds/forest_midground_1.png",renderer)) {
            printf( "Failed to load sprite sheet texture: forest_midground_1.png\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 960;
            this->animation[0].h = 540;
            return true;
        }
    }
    if (this->name == "SplashBackground") {
        if (!this->loadGeneralTextureFromFile("../../rec/backgrounds/splash_background.png",renderer)) {
            printf( "Failed to load sprite sheet texture: splash_background.png\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 1920;
            this->animation[0].h = 1080;
            return true;

        }
    }

    if (this->name == "StoneFloor") {
        if (!this->loadGeneralTextureFromFile("../../rec/forgrounds/stone_floor.png",renderer)) {
            printf( "Failed to load sprite sheet texture: stone_floor.png\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 960;
            this->animation[0].h = 25;
            return true;

        }
    }
    if (this->name == "MenuStartButton") {
        if (!this->loadGeneralTextureFromFile("../../rec/text/main_menu_start_button.png",renderer)) {
            printf( "Failed to load sprite sheet texture: main_menu_start_button.png\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 49;
            this->animation[0].h = 10;
            return true;

        }
    }
    if (this->name == "MenuBattleButton") {
        if (!this->loadGeneralTextureFromFile("../../rec/text/main_menu_battle_button.png",renderer)) {
            printf( "Failed to load sprite sheet texture: main_menu_battle_button.png\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 45;
            this->animation[0].h = 10;
            return true;

        }
    }
    if (this->name == "MenuOptionsButton") {
        if (!this->loadGeneralTextureFromFile("../../rec/text/main_menu_options_button.png",renderer)) {
            printf( "Failed to load sprite sheet texture: main_menu_options_button.png\n" );
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 55;
            this->animation[0].h = 10;
            return true;

        }
    }
    if (this->name == "MenuQuitButton") {
        if(!this->loadGeneralTextureFromFile("../../rec/text/main_menu_quit_button.png",renderer)) {
            printf("Failed to load sprite sheet texture: main_menu_quit_button.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 32;
            this->animation[0].h = 9;
            return true;
        }
    }
    if (this->name == "Pentagram") {
        if(!this->loadGeneralTextureFromFile("../../rec/objects/symbols/pentagram.png",renderer)) {
            printf("Failed to load sprite sheet texture: pentagram.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 159;
            this->animation[0].h = 159;
            return true;
        }
    }
    if (this->name == "CharacterSelectMenu") {
        if(!this->loadGeneralTextureFromFile("../../rec/midgrounds/character_select_menu.png",renderer)) {
            printf("Failed to load sprite sheet texture: character_select_menu.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 1701;
            this->animation[0].h = 901;
            return true;
        }
    }
    if (this->name == "MountainPrototypeSmall") {
        if(!this->loadGeneralTextureFromFile("../../rec/level_avatars/mountain_avatar_small.png",renderer)) {
            printf("Failed to load sprite sheet texture: mountain_avatar_small.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 120;
            this->animation[0].h = 85;
            return true;
        }
    }
    if (this->name == "MountainPrototypeBig") {
        if(!this->loadGeneralTextureFromFile("../../rec/level_avatars/mountain_avatar_big.png",renderer)) {
            printf("Failed to load sprite sheet texture: mountain_avatar_big.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].w = 600;
            this->animation[0].h = 275;
            return true;
        }
    }

    if (this->name == "WoodTorch") {
        if (!this->loadGeneralTextureFromFile("../../rec/animations/torch_wood.png",renderer)) {
            printf("Failed to load sprite sheet texture: torch_wood.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].h = 39;
            this->animation[0].w = 38;

            this->animation[1].x = 39;
            this->animation[1].y = 1;
            this->animation[1].h = 39;
            this->animation[1].w = 38;

            this->animation[2].x = 77;
            this->animation[2].y = 1;
            this->animation[2].h = 39;
            this->animation[2].w = 38;

            this->animation[3].x = 115;
            this->animation[3].y = 1;
            this->animation[3].h = 39;
            this->animation[3].w = 38;

            this->animation[4].x = 153;
            this->animation[4].y = 1;
            this->animation[4].h = 39;
            this->animation[4].w = 38;

            this->animation[5].x = 191;
            this->animation[5].y = 1;
            this->animation[5].h = 39;
            this->animation[5].w = 38;

            this->animation[6].x = 228;
            this->animation[6].y = 1;
            this->animation[6].h = 39;
            this->animation[6].w = 38;
            return true;
        }
    }
    if (this->name == "SteelTorch") {
        if (!this->loadGeneralTextureFromFile("../../rec/animations/steel_wood.png",renderer)) {
            printf("Failed to load sprite sheet texture: steel_wood.png\n");
            return false;
        } else {
            this->animation[0].x = 1;
            this->animation[0].y = 1;
            this->animation[0].h = 39;
            this->animation[0].w = 38;

            this->animation[1].x = 39;
            this->animation[1].y = 1;
            this->animation[1].h = 39;
            this->animation[1].w = 38;

            this->animation[2].x = 77;
            this->animation[2].y = 1;
            this->animation[2].h = 39;
            this->animation[2].w = 38;

            this->animation[3].x = 115;
            this->animation[3].y = 1;
            this->animation[3].h = 39;
            this->animation[3].w = 38;

            this->animation[4].x = 153;
            this->animation[4].y = 1;
            this->animation[4].h = 39;
            this->animation[4].w = 38;

            this->animation[5].x = 191;
            this->animation[5].y = 1;
            this->animation[5].h = 39;
            this->animation[5].w = 38;

            this->animation[6].x = 228;
            this->animation[6].y = 1;
            this->animation[6].h = 39;
            this->animation[6].w = 38;
            return true;
        }
    }
    if (this->name == "PineTree") {
        if (!this->loadGeneralTextureFromFile("../../rec/animations/pine_tree_animation.png",renderer)) {
            printf( "Failed to load sprite sheet texture: pine_tree_animation.png\n" );
            return false;
        } else {
            this->animation[0].x =1;
            this->animation[0].y =1;
            this->animation[0].h =88;
            this->animation[0].w =81;

            this->animation[1].x =82;
            this->animation[1].y =1;
            this->animation[1].h =88;
            this->animation[1].w =81;

            this->animation[2].x = 163;
            this->animation[2].y = 1;
            this->animation[2].h = 88;
            this->animation[2].w = 81;

            this->animation[3].x = 244;
            this->animation[3].y = 1;
            this->animation[3].h = 88;
            this->animation[3].w = 81;

            this->animation[4].x = 325;
            this->animation[4].y = 1;
            this->animation[4].h = 88;
            this->animation[4].w = 81;

            this->animation[5].x = 406;
            this->animation[5].y = 1;
            this->animation[5].h = 88;
            this->animation[5].w = 81;

            this->animation[6].x = 487;
            this->animation[6].y = 1;
            this->animation[6].h = 88;
            this->animation[6].w = 81;

            this->animation[7].x = 568;
            this->animation[7].y = 1;
            this->animation[7].h = 88;
            this->animation[7].w = 81;

            this->animation[8].x = 649;
            this->animation[8].y = 1;
            this->animation[8].h = 88;
            this->animation[8].w = 81;
            return true;
        }
    }
    if (this->name == "NumberStrip") {
        if(!this->loadGeneralTextureFromFile("../../rec/text/number_strip.png",renderer)) {
            printf( "Failed to load sprite sheet texture: number_strip.png\n" );
            return false;
        } else {
            this->animation[0].x =1;
            this->animation[0].y =1;
            this->animation[0].w =9;
            this->animation[0].h =9;

            this->animation[1].x =10;
            this->animation[1].y =1;
            this->animation[1].w =9;
            this->animation[1].h =9;

            this->animation[2].x =19;
            this->animation[2].y =1;
            this->animation[2].w =9;
            this->animation[2].h =9;

            this->animation[3].x =28;
            this->animation[3].y =1;
            this->animation[3].w =9;
            this->animation[3].h =9;

            this->animation[4].x =37;
            this->animation[4].y =1;
            this->animation[4].w =9;
            this->animation[4].h =9;

            this->animation[5].x =46;
            this->animation[5].y =1;
            this->animation[5].w =9;
            this->animation[5].h =9;

            this->animation[6].x =55;
            this->animation[6].y =1;
            this->animation[6].w =9;
            this->animation[6].h =9;

            this->animation[7].x =64;
            this->animation[7].y =1;
            this->animation[7].w =9;
            this->animation[7].h =9;

            this->animation[8].x =73;
            this->animation[8].y =1;
            this->animation[8].w =9;
            this->animation[8].h =9;

            this->animation[9].x =82;
            this->animation[9].y =1;
            this->animation[9].w =9;
            this->animation[9].h =9;
            return true;
        }
    }
    //Character Idle Portraits are loaded in here.
    if (this->name == "HorusCharacterSelect") {
        if(!this->loadGeneralTextureFromFile("../../rec/animations/characters/horus/horus_idle.png", renderer)) {
            printf( "Failed to load sprite sheet texture! GeneralTexture.cpp :horus_idle.png\n" );
            return false;
        } else {
            int width = 79;
            int x_pos = 1;
            for (int i =0; i<18; i++) {
                this->animation[i].x = x_pos;
                this->animation[i].y =1;
                this->animation[i].w =79;
                this->animation[i].h =65;
                x_pos = x_pos + width + 1;
            }
            return true;
        }
    }
    return false;
}

int GeneralTexture::GetWidth() {
    return this->width;
}

int GeneralTexture::GetHeight() {
    return this->height;
}

void GeneralTexture::SetWidth(int x) {
    this->width = x;
}

void GeneralTexture::SetHeight(int x) {
    this->height = x;
}
void GeneralTexture::SetXPos(int x) {
    this->xposition = x;
}

void GeneralTexture::SetYPos(int y) {
    this->yposition = y;
}

void GeneralTexture::SetBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(this->texture,blending);
}

void GeneralTexture::SetAlpha( Uint8 alpha ) {
    SDL_SetTextureAlphaMod( this->texture, alpha );
}

int GeneralTexture::GetXPos() {
    return this->xposition;
}
int GeneralTexture::GetYPos() {
    return this->yposition;
}

void GeneralTexture::SetFrameCount(int x) {
    this->frameCount = x;
}

int GeneralTexture::GetFrameCount() {
    return this->frameCount;
}

void GeneralTexture::TickFrameCount() {
    this->frameCount++;

}

void GeneralTexture::ResetFrameCount() {
    this->frameCount =0;
}

void GeneralTexture::Free_Texture() {
    //Free texture if it exists
    if( this->texture != NULL ) {
        this->texture = NULL;
        SDL_DestroyTexture( this->texture );
    }
}
