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
#include "aicontrol.h"

namespace AI {
//Here it will have algorithms that it will verify in the class Map()
//all the Gabriel existing and will create each Gabriel
AiControl::AiControl(CoreObjects *core,string iaFile,Person *person) {

    this->Core = core;

	this->pcache1 = new Render::ParticleCache(core->L,"../scripts/explode.lua");
	luabind::globals(core->L)["iacache"] = pcache1;
	this->pcache1->load();
	this->person = person;

	numberAi = 50;

	luabind::globals(core->L)["ailoader"] = this;

	this->iaFile = iaFile;
    cout <<"Arquivo:"<<iaFile<<endl;

	// Aqui haverá algorítmos que verificará na classe map todos os IA
	// existentes e criará cada IA
}

//clean the AI list
//call method kill()
AiControl::~AiControl() {

	list<ObjectAI *>::iterator i;
	for (i = aiList.begin();i!=aiList.end();i++) {
        ObjectAI* temp = (*i);
      Core->render->priority->removePackage(temp->imgPkg->number);
      i = aiList.erase(i);
      delete temp;
	}
}


void AiControl::load() {
  #ifdef LUA50
        setlocale (LC_ALL, NULL);
        int s = lua_dofile(Core->L,this->iaFile.c_str());
    #else
        int s = luaL_dofile(Core->L,iaFile.c_str());
    #endif

    if ( s!=0 ) {
      cerr << "-- " << lua_tostring(Core->L, -1) << std::endl;
      lua_pop(Core->L, 1);
    }
}

//it covers list and executes execObj()
void AiControl::execAI() {
	list<ObjectAI *>::iterator i;
	for (i = aiList.begin();i!=aiList.end();i++) {
    ObjectAI* temp = (*i);
    if (temp->getLife() <= 0) {
      if (temp->getMaster() == 1)
        *Core->gameState = GAME_WIN;
      Core->refParticle->addParticle(temp->getPosX(),temp->getPosY(),Core->particleCache,Core->render,Core->mapSrcRect,80);
      Core->render->priority->removePackage(temp->imgPkg->number);
      i = aiList.erase(i);
      delete temp;
    }
    else
      temp->execObj();
	}
}

//remove AI of the AI list
void AiControl::removeAI(int number) {

	list<ObjectAI *>::iterator it;
	it = aiList.begin();
	while (((*it)->index != number) && (it !=aiList.end()))
		it ++;

	this->aiList.erase(it);

}

//remove AI of the AI list
void AiControl::addAI(string file,int posX,int posY,string iaFile) {

  ObjectAI* temp = new ObjectAI(file.c_str(),iaFile.c_str(),Core,person);
  temp->createBody(posX,posY);
  temp->imgPkg->number = this->numberAi;
  Core->render->priority->addPackage(temp->imgPkg);
  numberAi++;
  this->aiList.push_back(temp);
}



}



