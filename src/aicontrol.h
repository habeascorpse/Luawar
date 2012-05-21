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
#ifndef AIAICONTROL_H
#define AIAICONTROL_H
#include <list>
#include <pthread.h>

#include "defs.h"
#include "map.h"
#include "objectai.h"
#include "refparticle.h"
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


namespace AI {

/**
	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/
class AiControl{
	public:
	/**
		* @brief Construtor padrão de aiControl
		<br>	Default constructor for aiControl Class
		*/
    AiControl(CoreObjects *core,string iaFile,Person *person);

    ~AiControl();

		void removeAI(int number);
		void addAI(string file,int posX,int posY,string iaFile);
		void load();
		void execAI();

	private:

		list<ObjectAI *> aiList;
		int numberAi;
		string iaFile;

		CoreObjects *Core;
		Person *person;
		Render::ParticleCache *pcache1;

};

}

#endif
