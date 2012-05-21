#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "defs.h"
#include <Box2D.h>
#include "package.h"
#include <string>
#include <SDL/SDL.h>
#include "videorender.h"
#include "coreobjects.h"

using namespace std;

class Object {

  public:
    Object(int posX, int posY,SDL_Surface* img,int priority,CoreObjects* core);
    ~Object();

    void refresh();
    Render::Package pkg;
    b2Body *body;

  private:

    int x,y;
    string fileName;
    CoreObjects *core;
    int direction;

};



#endif // OBJECT_H_INCLUDED
