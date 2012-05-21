#include "bulletmanager.h"

BulletManager::BulletManager(lua_State * lua, string file)
{
  this->L = lua;
  this->file = file;
}

BulletManager::~BulletManager(){
        if (img != NULL)
            SDL_FreeSurface(img);
}

void BulletManager::addBullet(string file) {
    img = Render::Video::LoadBMP(file.c_str());
}

void BulletManager::addSound(string file) {
      soundFile = file;
      sound = Mix_LoadWAV(file.c_str());
}

void BulletManager::load() {

  #ifdef LUA5.1
    luaL_dofile(L,file.c_str());
  #else
    lua_dofile(L,file.c_str());
  #endif
}
