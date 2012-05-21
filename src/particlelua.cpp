#include "particlelua.h"

ParticleLua::ParticleLua(SDL_Rect* mapSrcRect,lua_State *L,string luaFile, int num,int x,int y,Render::VideoRender* render,int timer,int cicles,int priority) {
  srand ( time(NULL) );
  this->luaFile = luaFile;
  this->num = num;
  pkg = new Render::Package();
  px = x;
  py = y;
  //pkg.img = Render::Video::CreateSurface(100,100,DF_DEPTH);
  pkg->img = Render::Video::LoadBMP("../images/objects/stone.png");
  pkg->destRect = new SDL_Rect;
  pkg->destRect->x = x;
  pkg->destRect->y = y;
  pkg->srcRect = NULL;
  pkg->number = priority;
  cout <<"Num:"<<pkg->number<<endl;
  this->timer = timer;
  this->render = render;
  this->L = L;
  render->priority->addPackage(pkg);
  lastTime = timer;
  this->cicles = cicles;
  lastCicle = 0;
  this->mapSrcRect = mapSrcRect;

  int i;
  for (i=0;i<num;i++) {
    this->x[i] = 0;
    this->y[i] = 0;
    velx[i] = rand()%5;
    vely[i] = rand()%5;
    color[i] = 0;
  }
}

ParticleLua::~ParticleLua() {
  render->priority->removePackage(pkg->number);
  SDL_FreeSurface(pkg->img);
  delete pkg->destRect;
}

int ParticleLua::getNum() {
  return num;
}

int ParticleLua::getX(int id) {
  return this->x[id];
}
int ParticleLua::getY(int id) {
  return this->y[id];
}
int ParticleLua::getVelX(int id) {
  return this->velx[id];
}
int ParticleLua::getVelY(int id) {
  return this->vely[id];
}

int ParticleLua::getColor(int id) {
  return this->color[id];
}

void ParticleLua::setX(int id,int x) {
  this->x[id] = x;
}

void ParticleLua::setY(int id,int y) {
  this->y[id] = y;
}

void ParticleLua::setVelX(int id,int x) {
  this->velx[id] = x;
}

void ParticleLua::setVelY(int id,int y) {
  this->vely[id] = y;
}

void ParticleLua::setColor(int id,int c) {
  this->color[id] = c;
}

void put_pixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    int offset = y * surface->w + x;
    Uint32 color = SDL_MapRGB(surface->format, r, g, b);

    if(surface->format->BytesPerPixel == 1)
        *( ((Uint8*)surface->pixels) + offset) = color;
    else if(surface->format->BytesPerPixel == 2)
        *( ((Uint16*)surface->pixels) + offset) = color;
    else
        *( ((Uint32*)surface->pixels) + offset) = color;
}


void ParticleLua::exec() {
  if (lastTime >= timer) {
    lastCicle++;
    lastTime = 0;
    //Lock mutex Video
    SDL_Surface *temp = Render::Video::CreateSurface(100,100,DF_DEPTH);
    luabind::globals(L)["plua"] = this;
    #ifdef LUA5.1
          luaL_dofile(L,luaFile.c_str());
        #else
          lua_dofile(L,luaFile.c_str());
        #endif

    for (int i = 0;i<num;i++) {
      put_pixel(temp,  x[i], y[i], 255,0,0);
    }
    //pthread_mutex_lock(&render->priority->videoMutex);
    SDL_FreeSurface(pkg->img);
    pkg->img = temp;
    //SDL_SaveBMP(pkg->img,"teste.bmp");
    //pthread_mutex_unlock(&render->priority->videoMutex);
    pkg->destRect->x = this->px - mapSrcRect->x;
    pkg->destRect->y = this->py - mapSrcRect->y;
    //cout<<"cor"<<SDL_MapRGB(temp->format, 255,0,0)<<endl;
  }
  else
    lastTime += TIME_RULES;

  //unlock mutex
}
