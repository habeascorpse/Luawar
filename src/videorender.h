/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva, Thiago Luiz Rodrigues,  *
 *   Gabriel Vedana Queiroz                                                *
 *   habeas_corpse@yahoo.com.br                                            *
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
#ifndef RULES_GAME_H
#define RULES_GAME_H

#include <iostream>
#include <SDL/SDL.h>
#include <list>
#include "defs.h"
#include "video.h"
#include "renderpriority.h"
#include "package.h"
#include <SDL_rotozoom.h>


namespace Render {
  /**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>;
*/

class VideoRender : public Video  {

	public:
	/**
		* @brief Construtor padrão de Action
		<br>	Default constructor for Action Class
		*/

		VideoRender();

		~VideoRender();

		virtual void render();

		void init();

		void kill(); // mata a thread

		void loop();

		RenderPriority* priority;

	private:

		int running;

		static void* start(void* arg);


		pthread_t thread;
};

}

#endif
