#ifndef COREOBJECTS_H_INCLUDED
#define COREOBJECTS_H_INCLUDED

#include <SDL/SDL.h>
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
#include "videorender.h"
#include "map.h"
#include "sound.h"
#include "refparticle.h"
#include "particlecache.h"
#include "event.h"

class CoreObjects {

  public:
    SDL_Rect *mapSrcRect;
    Render::VideoRender *render;
    lua_State *L;
    Scenario::Map *map;
    Scenario::Sound *sound;
    b2World* world;
    Render::RefParticle *refParticle;
    Render::ParticleCache *particleCache;
    Render::ParticleCache *bloodCache;
    Render::ParticleCache *smokeCache;
    Mix_Music* MusicGame;
    Events::Event *event;
    int* gameState;
};


#endif // COREOBJECTS_H_INCLUDED
