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
#ifndef RENDERPACKAGE_H
#define RENDERPACKAGE_H
#include "defs.h"
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

namespace Render {

/**
	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/
class Package{
public:
    Package() {
      img = NULL;
      srcRect = NULL;
      destRect = NULL;
      rotable = false;
      rotation = 0;
      lastRot = 0;
      }
    ~Package() {}
		SDL_Surface* img;
		SDL_Rect* srcRect;
		SDL_Rect* destRect;
		unsigned long int number;
		bool rotable;
		float rotation;
		int lastRot;

};



}

#endif

