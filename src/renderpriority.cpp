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
#include "renderpriority.h"

namespace Render {

bool comparePkg(const Package* pkg1,const Package* pkg2) {
  return (pkg1->number < pkg2->number);
}

RenderPriority::RenderPriority()
{
	pthread_mutex_init(&videoMutex,NULL);
}


RenderPriority::~RenderPriority()
{
    pkg.clear();
    pthread_mutex_destroy(&videoMutex);
}
void RenderPriority::removePackage(unsigned int number) {

	pthread_mutex_lock(&videoMutex);
	list<Package*>::iterator it;
	it = pkg.begin();
	while (((*it)->number != number) && (it !=pkg.end()))
		it ++;
	it = pkg.erase(it);
	pkg.sort(comparePkg);
	pthread_mutex_unlock(&videoMutex);

}

void RenderPriority::addPackage(Package* pkg) {

	pthread_mutex_lock(&videoMutex);
	this->pkg.push_back(pkg);
	this->pkg.sort(comparePkg);
	pthread_mutex_unlock(&videoMutex);

}

}

