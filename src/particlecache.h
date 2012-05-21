#ifndef PARTICLECACHE_H
#define PARTICLECACHE_H

#include <list>
#include <string>
#include "video.h"
#include "defs.h"
#include "package.h"
#include <SDL_mixer.h>

#ifdef LUA5.1

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>

}

#else

extern "C" {
	#include <lua50/lua.h>
	#include <lua50/lauxlib.h>
	#include <lua50/lualib.h>

}
#endif

using namespace std;

namespace Render {


    class ParticleCache {

        public:
            ParticleCache(lua_State * L,string file);
            ~ParticleCache();

            void addParticle(string file);
            void addSound(string file);
            void load();
            string fileSound;

            SDL_Surface* img[20];
            int last;
            Mix_Chunk* sound;
        private:

            lua_State * L;
            string file;

    };


}






#endif
