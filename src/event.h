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
#ifndef EVENTSEVENT_H
#define EVENTSEVENT_H
#include <pthread.h>

#include "defs.h"
#include "joystick.h"
#include "keyboard.h"
#include "action.h"


namespace Events {

/**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>;
                Thiago Luiz Rodrigues <bobboyms@yahoo.com.br>;
	@todo
		@li Implementar o destrutor de threads
*/
class Event{
	public:
/**
	@brief Construtor da classe Event que
	Passa por parâmetro o tipo do evento que pode ser:
	KEYBOARD e JOYSTICK que já definido no arquivos defs.h

*/
	Event(int eventType);
	~Event();

/**
	@brief objeto das ações principal do projeto
*/
	Rules::Action action;
	void change(int eventType);

	void capture();

	SDL_Event event;

	private:

		int eventType;
		void* eventObj;
};

}

#endif
