/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "Level.h"


Level::Level(std::string name,SDL_Renderer* renderer) {
    this->textures = new std::vector<GeneralTexture*>;
    this->platforms = new std::vector<GeneralTexture*>;
    this->InitLevelObjects(name,renderer);
}

Level::~Level() {

}
void Level::InitLevelObjects(std::string name,SDL_Renderer* renderer) {
    //TODO:// this is the prototyping level for testing.
    if(name == "mountain_top") {
        GeneralTexture* background = new GeneralTexture(1,"BlankNightSky",renderer);
        background->SetXPos(0);
        background->SetYPos(0);
        this->textures->push_back(background);

        GeneralTexture* midground = new GeneralTexture(1,"MountainMidground",renderer);
        midground->SetXPos(0);
        midground->SetYPos((background->GetXPos()+background->GetHeight()*2)-midground->GetHeight()*2);
        this->textures->push_back(midground);

        GeneralTexture* forground = new GeneralTexture(1,"StoneFloor",renderer);
        forground->SetXPos(0);
        forground->SetYPos((background->GetXPos()+background->GetHeight()*2)-forground->GetHeight()*2);
        forground->isStartingPlatform = true;
        this->platforms->push_back(forground);

        GeneralTexture* rocks_midground = new GeneralTexture(1,"RockMidground",renderer);
        rocks_midground->SetXPos(0);
        rocks_midground->SetYPos(background->GetXPos()+background->GetHeight()*2-rocks_midground->GetHeight()*2-forground->GetHeight()*2);
        this->textures->push_back(rocks_midground);

        //Delete dangling pointers
        background = NULL;
        midground = NULL;
        rocks_midground =NULL;
        forground = NULL;


        delete forground;
        delete midground;
        delete background;
        delete rocks_midground;
    }
}
