#include "particlesystem.h"

namespace Render {

    ParticleSystem::ParticleSystem(int posX, int posY,ParticleCache* cache,int time,int priority, VideoRender *render,SDL_Rect* mapSrcRect) {
        x = posX;
        y = posY;
        this->time = time;
        for (int i = 0;i<20; i++)
           particleImg[i] = cache->img[i];
        this->mapSrcRect = mapSrcRect;
        pkg = new Package;
        pkg->destRect = new SDL_Rect;
        pkg->srcRect = NULL;
        pkg->number = priority;
        this->render = render;
        this->running = 1;
        i = 1;
        auxTemp = 0;
        pkg->destRect->x = this->x - mapSrcRect->x;
        pkg->destRect->y = this->y - mapSrcRect->y;
        pkg->img = cache->img[0];
        this->cache =  cache;
        render->priority->addPackage(pkg);
    }


    ParticleSystem::~ParticleSystem() {
      delete pkg->destRect;
      delete pkg;
    }


    int ParticleSystem::loop() {
        if (running == 1) {
            auxTemp += TIME_RULES;
            if ((particleImg[i] != NULL) && (auxTemp >= time))  {
                pkg->img = particleImg[i];
                pkg->destRect->x = this->x - mapSrcRect->x;
                pkg->destRect->y = this->y - mapSrcRect->y;
                auxTemp = 0;
                i++;
            }
            if (i >= cache->last) {
                this->render->priority->removePackage(pkg->number);
                this->running = 0;
            }
        }
    }

}
