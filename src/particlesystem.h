#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include <SDL.h>
#include <list>
#include "package.h"
#include "videorender.h"
#include "particlecache.h"

using namespace std;

namespace Render {
    class ParticleSystem {
        public:

            ParticleSystem(int posX, int posY,ParticleCache* cache,int time,int priority, VideoRender *render,SDL_Rect* mapSrcRect);
            //ParticleSystem(string luaFile,int quantity);
            virtual ~ParticleSystem();

            void init();
            int loop();
            Package *pkg;
            int running;

        private:

            static void* start(void *args);

            SDL_Surface *particleImg[20];
            int time;
            int x,y;
            int i;
            int auxTemp;
            SDL_Rect *mapSrcRect;
            VideoRender *render;
            ParticleCache *cache;
    };

}


#endif // PARTICLESYSTEM_H_INCLUDED
