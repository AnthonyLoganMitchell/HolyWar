/* *CopyRight 2018, Anthony Logan Mitchell, All rights reserved.
   *Holy war is my personal programming project and all artwork
   *and high level programming outside of SDL2 framework, openGL,
   *and c++ api are my original work in progress.
   *Unauthorized copying of this file, via any medium is strictly prohibited
   *Proprietary and confidential
   *Written by Logan Mitchell <loganmitchell2011@gmail.com>
*/
#include "Projectile.h"
#include "ProjectileModules.h"
#include "ProjectileLinks.h"
#include "ProjectileTexture.h"
#include "SDL.h"
#include <iostream>
void ProjectileModules::RunProjectiles(int Tick, std::vector<Projectile*>* projectiles,SDL_Renderer* renderer) {
   for (std::vector<Projectile*>::iterator i = projectiles->begin(); i != projectiles->end(); i++) {
      if (!(*i)->isActive) {
         break;
      }
      Projectile* p = (*i);
      if (p->owner_name == "Horus") {
         if (p->projectile_name == "horus_beam") {
            if (p->isActive) {
               if(p->links->size() == 0) {
                  p->base_texture->render(renderer,p->posX,p->posY,2,0,0,&p->base_texture->multiClips[0][0][0],SDL_FLIP_NONE);
                  //x,y,index,Tick
                  ProjectileLinks* link = new ProjectileLinks(p->posX,p->posY,0,Tick);
                  p->links->push_back(link);                                
               } else {
                  int width=0;
                  int index=0;
                  int x_pos=0;
                  for(std::vector<ProjectileLinks*>::iterator j = p->links->begin(); j != p->links->end(); j++) {
                     if (p->direction == "LEFT") {
                        p->base_texture->render(renderer,(*j)->xPos,(*j)->yPos,2,0,0,&p->base_texture->multiClips[0][(*j)->rectIndex][p->base_texture->GetFrameCount()],SDL_FLIP_HORIZONTAL);
                     } else if (p->direction == "RIGHT") {
                        p->base_texture->render(renderer,(*j)->xPos,(*j)->yPos,2,0,0,&p->base_texture->multiClips[0][(*j)->rectIndex][p->base_texture->GetFrameCount()],SDL_FLIP_NONE);
                     }
                     if (j == p->links->end()-1 && (*j)->xPos+p->base_texture->multiClips[0][(*j)->rectIndex][p->base_texture->GetFrameCount()].x < 1920 && (*j)->xPos+p->base_texture->multiClips[0][(*j)->rectIndex][p->base_texture->GetFrameCount()].x > 0) {
                  
                        width = p->base_texture->multiClips[0][(*j)->rectIndex][p->base_texture->GetFrameCount()].w;
                  
                        if ((*j)->rectIndex  > p->base_texture->GetFrameCount()) {
                           index =  1;
                        } else {
                           index = (*j)->rectIndex +1;
                        }
                     }
                  }
                  
                  if (Tick%p->linkRate == 0) {      
                     std::cout << "HITS" << std::endl;               
                     if(p->direction == "LEFT") {
                        x_pos -= width;
                     }
                     if(p->direction == "RIGHT") {
                        x_pos += width;
                     } 
                     if(p->direction == "LEFT") {
                        ProjectileLinks* link = new ProjectileLinks(x_pos,p->posY,index,Tick);
                        p->links->push_back(link);                   
                     }
                     if(p->direction == "RIGHT") {                  
                        ProjectileLinks* link = new ProjectileLinks(x_pos,p->posY,index,Tick);
                        p->links->push_back(link); 
                  
                     }
                  }
               }
               if (Tick%p->base_texture->ClipMod == 0) {
                  std::cout << p->base_texture->GetFrameCount() << std::endl;                  
                  p->base_texture->SetFrameCount(p->base_texture->GetFrameCount()+1);
               }
               if (p->base_texture->GetFrameCount() >= p->base_texture->GetMaxClipCount()){
                  
                  p->base_texture->SetFrameCount(0);
                  p->isActive= false;
                  p->links->clear();             
               }
            }       
         }
      }
   }

   for (std::vector<Projectile*>::iterator i = projectiles->begin(); i != projectiles->end(); i++) {
      if ((*i)->isActive) {
         break;
      }
      if (!(*i)->isActive && i == projectiles->end()) {
         projectiles->clear();
      }
   }
}