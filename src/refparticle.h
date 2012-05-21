#ifndef REFPARTICLE_H_INCLUDED
#define REFPARTICLE_H_INCLUDED

#include "particlecache.h"
#include "particlesystem.h"
#include "particlelua.h"
#include "sound.h"

namespace Render {
  class RefParticle {
    public:

      RefParticle(Scenario::Sound *sound);

      void particleAnalyzer();
      void addParticle(int posX, int posY,ParticleCache  *particleCache, VideoRender* render,SDL_Rect *mapSrcRect,int time);
      void addLuaParticle(SDL_Rect* mapSrcRect,lua_State *L,string file,int posX,int posY,Render::VideoRender* render,int num,int time,int cicles);
    private:
      int numberParticle;
      list<Render::ParticleSystem *> psystem;
      list<ParticleLua *> psyslua;
      Scenario::Sound *sound;

  };

}


#endif // REFPARTICLE_H_INCLUDED
