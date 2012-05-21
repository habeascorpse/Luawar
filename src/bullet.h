
#ifndef BULLET_H
#define BULLET_H
#include "defs.h"
#include <Box2D.h>
#include "package.h"
#include <string>
#include <SDL/SDL.h>
#include "videorender.h"

using namespace std;

class Bullet {

  public:
    Bullet(int posX, int posY,SDL_Rect *mapSrcRect,SDL_Surface* img,int priority,Render::VideoRender* Render,b2World* world,int direction);
    ~Bullet();

    void refresh();
    Render::Package pkg;
    b2Body *body;
    int running;

  private:

    int x,y;

    string fileName;
    SDL_Rect* mapSrcRect;
    Render::VideoRender* render;
    int direction;

};


#endif
