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
#ifndef AIOBJECTAI_H
#define AIOBJECTAI_H
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "defs.h"
#include "coreobjects.h"

#ifndef LUA50

    extern "C" {
        #include <lua.h>
        #include <lauxlib.h>
        #include <lualib.h>

    }

#else

    extern "C" {
        #include <lua50/lua.h>
        #include <lua50/lauxlib.h>
        #include <lua50/lualib.h>

    }
#endif


#include "defs.h"
#include "person.h"
#include "map.h"

using namespace std;
namespace AI {

/**
	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/
class ObjectAI : public Person {
	public:
    /**
		* @brief Construtor padrão de ObjectAI
		<br>	Default constructor for ObjectAI
		*/
    ObjectAI(const char *file,string ia,CoreObjects *core,Person* person);
    ~ObjectAI();

		int execObj();

		void setNumber(int nb);
		int index;
		void createBody(int x,int y);
		int timeAttackIA;
	private:

    const SDL_Rect *mapSrcRect;

		string script;
		string stgLua;
		Scenario::Map* map;
		Person* person;

		void synchronizeImg();

};

}

#endif
