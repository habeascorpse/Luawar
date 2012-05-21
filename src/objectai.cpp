/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz   *
 *   habeas_corpse@yahoo.com.br   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "objectai.h"

using namespace std;

namespace AI
{
  /**
    @author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
  */


  //constructor
  //it opens archive LUA with basic configurations of the AI
  ObjectAI::ObjectAI(const char *file,string ia,CoreObjects *core, Person* person) : Person(file,core)
  {
    this->map = core->map;
    this->person = person;
    this->mapSrcRect = core->mapSrcRect;

    ifstream fileIA(ia.c_str());
    if (!fileIA) {
      cout <<"Error on open Script for IA:"<<ia<<endl;

    }
      cout <<"Load IA Script success:"<<ia<<endl;

    string line;

    while(getline(fileIA,line)) {
      script += line + "\n";
    }
    timeAttackIA = 0;
   }

  //destructor;
  ObjectAI::~ObjectAI()  {

  }

  int ObjectAI::execObj() {

    luabind::globals(L)["ia"] = reinterpret_cast<Person *> (this);

    #ifdef LUA50
        int s = lua_dostring(L,script.c_str());
    #else
        int s = luaL_dostring(L,script.c_str());
    #endif

   // this->report_errors(L,s);
   timeAttackIA += TIME_RULES;
    synchronizeImg();
    heroMovement();
    return SUCCESS;

  }

  void ObjectAI::synchronizeImg() {
    imgPkg->destRect->x = getPosX() - mapSrcRect->x;
    imgPkg->destRect->y = getPosY() - mapSrcRect->y;
  }

  void ObjectAI::createBody(int x,int y) {

	b2BodyDef bodyDef;
	bodyDef.position.Set(x,y);
	bodyDef.massData.mass = weight;
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);

	b2PolygonDef shapeDef;
	shapeDef.SetAsBox(sizexImg/2, sizeyImg/2);
	shapeDef.density = density;
	shapeDef.friction = friction;
	shapeDef.filter.categoryBits = 0x0004;
  shapeDef.filter.maskBits = 0x0005;
  shapeDef.filter.groupIndex = 1;

	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();

}


}
