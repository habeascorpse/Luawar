#ifndef LAYERMANAGER_H_INCLUDED
#define LAYERMANAGER_H_INCLUDED
#include <string>
#include <iostream>
#include "video.h"
#include "defs.h"
#include "package.h"


using namespace std;
namespace Scenario{


  class BgLayer {

    public:

      BgLayer(string filename, float velocity_x, float velocity_y,SDL_Rect* mapSrcRect,int priority);
      ~BgLayer();

      void refresh();
      Render::Package* layer;

    private:

      float velocityX;
      float velocityY;
      SDL_Rect* mapSrcRect;

  };

}



#endif // LAYERMANAGER_H_INCLUDED
