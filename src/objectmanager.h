#ifndef OBJECTMANAGER_H_INCLUDED
#define OBJECTMANAGER_H_INCLUDED

#include <string>
#include <SDL/SDL.h>
#include "video.h"
#include "defs.h"
#include <SDL_mixer.h>
#include <SDL_rotozoom.h>
#include "object.h"

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

class ObjectManager
{
  public:
    ObjectManager(CoreObjects *core, string file);
    ~ObjectManager();
    void addObject(string imgFile,int posX,int posY);
    void load();

    void update();

  private:
    string imgFile;
    string file;
    lua_State *L;
    list<Object *> listObject;
    int priority;
    CoreObjects *core;

};





#endif // OBJECTMANAGER_H_INCLUDED
