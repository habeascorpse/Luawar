#include "refparticle.h"
namespace Render {
  RefParticle::RefParticle(Scenario::Sound *sound) {
    numberParticle = 401;
    this->sound = sound;
  }

  void RefParticle::particleAnalyzer() {
      list<ParticleSystem *>::iterator it;
      for (it = this->psystem.begin();it!=this->psystem.end();it++) {
          ParticleSystem* temp = (*it);
          if (temp->running == 0) {
            delete temp;
            it = psystem.erase(it);
          }
          else
            temp->loop();
      }

      list<ParticleLua *>::iterator it2;
      for (it2 = this->psyslua.begin();it2!=this->psyslua.end();it2++) {
          ParticleLua* temp = (*it2);
          if (temp->lastCicle >= temp->cicles) {
            delete temp;
            it2 = psyslua.erase(it2);
          }
          else
            temp->exec();
      }

  }

  void RefParticle::addParticle(int posX, int posY,ParticleCache  *particleCache, VideoRender* render,SDL_Rect *mapSrcRect, int time) {
    numberParticle++;
    if (numberParticle > 600)
      numberParticle = 401;
    sound->play(particleCache->sound);
    ParticleSystem *psystem1 = new ParticleSystem(posX, posY, particleCache, time,numberParticle,render, mapSrcRect);
    this->psystem.push_back(psystem1);
  }

  void RefParticle::addLuaParticle(SDL_Rect* mapSrcRect,lua_State *L,string file,int posX,int posY,Render::VideoRender* render,int num,int time,int cicles) {
    numberParticle++;
    if (numberParticle > 600)
      numberParticle = 401;

    ParticleLua *plua = new ParticleLua(mapSrcRect,L,file,num,posX,posY,render,time,cicles,numberParticle);
    this->psyslua.push_back(plua);
  }

}
