#include "layermanager.h"

namespace Scenario {
  BgLayer::BgLayer(string filename, float velocity_x,float  velocity_y, SDL_Rect* mapSrcRect,int priority) {
    layer = new Render::Package();
    layer->img = Render::Video::LoadBMP(filename.c_str());
    layer->number = priority;
    layer->destRect = new SDL_Rect;
    layer->destRect->x = 0;
    layer->destRect->y = 0;
    layer->destRect->w = DF_WIDTH;
    layer->destRect->h = DF_HEIGHT;
    layer->srcRect = new SDL_Rect;
    layer->srcRect->x = 0;
    layer->srcRect->y = 0;
    layer->srcRect->w = DF_WIDTH;
    layer->srcRect->h = DF_HEIGHT;

    this->velocityX = velocity_x;
    this->velocityY = velocity_y;
    this->mapSrcRect = mapSrcRect;

  }

  void BgLayer::refresh() {

    layer->srcRect->x = mapSrcRect->x * velocityX;
    layer->srcRect->y = mapSrcRect->y * velocityY;


  }

  BgLayer::~BgLayer() {

    //Free Surface
    SDL_FreeSurface(layer->img);
    layer->img = NULL;

    // Delete layers
    delete layer->destRect;
    delete layer->srcRect;
    delete layer;
  }




}
