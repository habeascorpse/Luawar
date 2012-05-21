#include "objectmanager.h"

ObjectManager::ObjectManager(CoreObjects *core, string file)
{
  this->file = file;
  priority = 1200;
  this->core = core;
}

ObjectManager::~ObjectManager(){
  list<Object*>::iterator it;
  for (it = listObject.begin();it!= listObject.end();it++) {
    delete (*it);
    it = listObject.erase(it);
  }

}

void ObjectManager::addObject(string imgFile,int posX,int posY) {
  priority++;
  if (priority >=1300)
    priority = 1200;

  SDL_Surface *img = Render::Video::LoadBMP(imgFile.c_str());
  Object* temp = new Object(posX,posY,img,priority,core);
  listObject.push_back(temp);
}


void ObjectManager::load() {
  cout <<"File:"<<file<<endl;

  #ifdef LUA5.1
    luaL_dofile(core->L,"../scripts/map1object.lua");
  #else
    lua_dofile(core->L,file.c_str());
  #endif
}

void ObjectManager::update() {
  list<Object*>::iterator it;
  for (it = listObject.begin();it!= listObject.end();it++) {
    (*it)->refresh();
  }
}
