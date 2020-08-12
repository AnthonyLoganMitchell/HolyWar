/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "ProjectileModules.h"
#include "ProjectileLinks.h"
void ProjectileModules::RunProjectiles(int Tick, std::vector<Projectile*>* projectiles,SDL_Renderer* renderer) {
   for (std::vector<Projectile*>::iterator i = projectiles->begin(); i != projectiles->end(); i++) {
      Projectile* p = (*i);
      if (p->owner_name == "Horus") {
         if (p->projectile_name == "horus_beam") {
            if(p->isInitialRun){
               p->base_texture->SetFrameCount(0);
            }
            if(p->links->size() == 0) {
                  p->base_texture->render(renderer,p->posX,p->posY,2,0,0,&p->base_texture->multiClips[0][0][0],SDL_FLIP_NONE);
                  //x,y,index,Tick
                  //ProjectileLinks* link = new ProjectileLinks(p->posX,p->posY,0,Tick);
                  //p->links->push_back(link);                                
            } else {
               //for(std::vector<ProjectileLinks*>::iterator j = p->links->begin(); j != p->links->end(); j++) {
               //   p->base_texture->render(renderer,(*j)->xPos,(*j)->yPos,2,0,0,&p->base_texture->multiClips[(*j)->rectIndex][p->base_texture->GetFrameCount()],SDL_FLIP_NONE);
              // }
            }
            if (Tick%p->base_texture->ClipMod == 0) {
               //std::cout<<"HITS"<<std::endl;
               p->base_texture->SetFrameCount(p->base_texture->GetFrameCount()+1);
            }
            if (p->base_texture->GetFrameCount() == p->base_texture->GetMaxClipCount()){
               p->base_texture->SetFrameCount(0);
               //p->links->clear();
               //projectiles->erase(i--);
            }
         }
      }
   }
}