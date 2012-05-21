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
#ifndef RENDERRENDERPRIORITY_H
#define RENDERRENDERPRIORITY_H

#include <list>
#include <iostream>
#include <pthread.h>
#include <SDL/SDL.h>
#include "package.h"




using namespace std;

namespace Render {

/**
Esta classe fornece os pacotes de prioridade de renderização,
nelas estarão guardadas todas as Surpefícies e seus Retângulos

	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/
class RenderPriority{

    public:
		RenderPriority();

		~RenderPriority();


		void addPackage(Package* pkg);
		void removePackage(unsigned int number);
		list<Package *> pkg;

		pthread_mutex_t videoMutex;
};

}

#endif
