#include "particlecache.h"


namespace Render {


    ParticleCache::ParticleCache( lua_State * L, string file) {
        this->L = L;
        this->file = file;
        last = 0;
    }

    ParticleCache::~ParticleCache() {
      int i = 0;
      while (i < last) {
        SDL_FreeSurface(img[i]);
        i++;
      }
      Mix_FreeChunk(sound);
      sound = NULL;
    }

    void ParticleCache::addParticle(string file) {
        img[last] = Video::LoadBMP(file.c_str());
        last++;
    }
    void ParticleCache::addSound(string file) {
      fileSound = file;
      sound = Mix_LoadWAV(file.c_str());
    }

    void ParticleCache::load() {

      #ifdef LUA5.1
        luaL_dofile(L,file.c_str());
      #else
        lua_dofile(L,file.c_str());
      #endif
    }




}
