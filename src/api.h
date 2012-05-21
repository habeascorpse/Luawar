#ifndef API_H
#define API_H

#include <luabind/luabind.hpp>
#include "person.h"
#include "map.h"
#include "defs.h"
#include "particlecache.h"
#include "bulletmanager.h"
#include "aicontrol.h"
#include <string>
#include <iostream>
#include "object.h"
#include "objectmanager.h"
#include "particlelua.h"


using namespace Scenario;

namespace Rules {


    static void createBind(lua_State *L) {

      #ifdef LUA50

      lua_dostring(L,"DF_WIDTH=640");
      lua_dostring(L,"DF_HEIGHT =480");
      lua_dostring(L,"DF_DEPTH =24");
      lua_dostring(L,"TILE_SIZE =32");
      lua_dostring(L,"CONTINUE =1");
      lua_dostring(L,"BREAK = 2");
      lua_dostring(L,"TILESET_X =8");
      lua_dostring(L,"TILESET_Y =15");
      #else
        luaL_dostring(L,"DF_WIDTH=640");
        luaL_dostring(L,"DF_HEIGHT =480");
        luaL_dostring(L,"DF_DEPTH =24");
        luaL_dostring(L,"TILE_SIZE =32");
        luaL_dostring(L,"CONTINUE =1");
        luaL_dostring(L,"BREAK = 2");
        luaL_dostring(L,"TILESET_X =8");
        luaL_dostring(L,"TILESET_Y =15");
      #endif

        // Declaration of Person Class
        luabind::module(L) [


            luabind::class_<Person>("Person")
              .def("increaseLife", &Person::increaseLife)
              .def("decreaseLife", &Person::decreaseLife)
              .def("setLife", &Person::setLife)
              .def("increaseSpecial", &Person::increaseSpecial)
              .def("decreaseSpecial", &Person::decreaseSpecial)
              .def("setDirection", &Person::setDirection)
              .def("jump", &Person::jump)
              .def("movRight", &Person::movRight)
              .def("movLeft", &Person::movLeft)
              .def("setAccelX", &Person::setAccelX)
              .def("setAccelY", &Person::setAccelY)
              .def("getSpeedX", &Person::getSpeedX)
              .def("getSpeedY", &Person::getSpeedY)
              .def("getPosX", &Person::getPosX)
              .def("getPosY", &Person::getPosY)
              .def("getLife", &Person::getLife)
              .def("getDirection", &Person::getDirection)
              .def("getJumping", &Person::getJumping)
              .def("getMoving", &Person::getMoving)
              .def("setMov", &Person::setMov)
              .def("attack", &Person::attack)
              .def("getMaster", &Person::getMaster)
              .def("setMaster", &Person::setMaster)
              .def_readonly("colideLeft", &Person::colideLeft)
              .def_readonly("colide", &Person::colide)
              .def_readonly("colideRight", &Person::colideRight)
              .def_readonly("sizexImg", &Person::sizexImg)
              .def_readonly("sizeyImg", &Person::sizeyImg)
              .def("stop", &Person::stop),

            luabind::class_<Map>("Map")
              .def("getValue",&Map::getValue),

            luabind::class_<Render::ParticleCache>("ParticleCache")
              .def("addParticle",&Render::ParticleCache::addParticle)
              .def("addSound",&Render::ParticleCache::addSound),

            luabind::class_<BulletManager>("Bullet")
              .def("addBullet",&BulletManager::addBullet)
              .def("addSound",&BulletManager::addSound),

            luabind::class_<AI::AiControl>("AiControl")
              .def("addAI",&AI::AiControl::addAI),

            luabind::class_<ParticleLua>("ParticleLua")
              .def("getX",&ParticleLua::getX)
              .def("getY",&ParticleLua::getY)
              .def("getVelX",&ParticleLua::getVelX)
              .def("getVelY",&ParticleLua::getVelY)
              .def("getColor",&ParticleLua::getColor)
              .def("setX",&ParticleLua::setX)
              .def("setY",&ParticleLua::setY)
              .def("setVelX",&ParticleLua::setVelX)
              .def("setVelY",&ParticleLua::setVelY)
              .def("getNum",&ParticleLua::getNum)
              .def("setColor",&ParticleLua::setColor),

            luabind::class_<ObjectManager>("ObjectManager")
              .def("addObject",&ObjectManager::addObject)

          ];



    }

}

#endif
