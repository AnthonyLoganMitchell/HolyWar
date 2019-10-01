#include "Level.h"


Level::Level(std::string name,SDL_Renderer* renderer)
{
    this->textures = new std::vector<GeneralTexture*>;
    this->platforms = new std::vector<GeneralTexture*>;
    this->InitLevelObjects(name,renderer);
}

Level::~Level()
{

}
void Level::InitLevelObjects(std::string name,SDL_Renderer* renderer)
{
    //TODO:// this is the prototyping level for testing.
    if(name == "mountain_top")
    {
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
        //TODO:// in future for this demo level add actual platforms to start on, which can overlap with the
        //forground platform, in order to have everyone start on floor platform but in their own positions.
        forground->isStartingPlatform = true;
        this->platforms->push_back(forground);


        //Delete dangling pointers
        background = NULL;
        midground = NULL;
        forground = NULL;
        delete forground;
        delete midground;
        delete background;
    }
}
