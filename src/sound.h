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
#ifndef SOUND_H
#define SOUND_H
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <SDL/SDL.h>
#include <list>
#include "defs.h"

#include <SDL_mixer.h>

using namespace std;
namespace Scenario {
	class Sound{
	public:
		/** @brief
    		* Construtor padrão de som
     		*/
		Sound();
		/** @brief
    		* Destrutor que encerra todas as variáveis e ponteiros de som
     		*/
		~Sound();
		/** @brief
    		* reproduzir de som
     		*/
		 void play(Mix_Chunk* ref);

	private:
		int channel;

	};
}

#endif
