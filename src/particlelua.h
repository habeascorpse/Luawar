#ifndef PARTICLELUA_H_INCLUDED
#define PARTICLELUA_H_INCLUDED

#include <list>
#include <string>
#include <SDL_gfxPrimitives.h>
#include <pthread.h>
#include "package.h"
#include "videorender.h"
#include <cstdlib>
#include <ctime>
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

#include <luabind/luabind.hpp>

using namespace std;
class ParticleLua {
  public:

    ParticleLua(SDL_Rect* mapSrcRect,lua_State *L,string luaFile, int num,int x,int y,Render::VideoRender* render,int timer,int cicles,int priority);
    ~ParticleLua();

    void exec();
    int getX(int id);
    int getY(int id);
    int getVelX(int id);
    int getVelY(int id);
    int getColor(int id);

    void setX(int id,int x);
    void setY(int id,int y);
    void setVelX(int id,int x);
    void setVelY(int id,int y);
    void setColor(int id,int c);
    int getNum();
    int cicles, lastCicle;

  protected:

    int x[100];
    int y[100];
    int velx[100];
    int vely[100];
    int num;
    string luaFile;
    int color[100];
    Render::Package *pkg;
    int lastTime;
    int timer;
    Render::VideoRender* render;
    lua_State *L;
    SDL_Rect* mapSrcRect;
    int px,py;
};



#endif // PARTICLELUA_H_INCLUDED
