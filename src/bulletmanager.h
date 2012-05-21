#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <string>
#include <SDL/SDL.h>
#include "video.h"
#include "defs.h"
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

class BulletManager
{
  public:
    BulletManager(lua_State * lua, string file);
    ~BulletManager();
    void addBullet(string file);
    void addSound(string file);
    void load();

    SDL_Surface* img;
    string soundFile;
    Mix_Chunk *sound;
  private:
    string file;
    lua_State *L;

};

#endif // BULLETMANAGER_H
