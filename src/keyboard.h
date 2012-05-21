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
#ifndef EVENTSKEYBOARD_H
#define EVENTSKEYBOARD_H
#include <SDL/SDL.h>
#include <iostream>
#include "defs.h"
#include "action.h"

using namespace std;
namespace Events {

/** @section key_sec Descrição
*	Esta classe Keyboard é de uso somente da Classe Event
*	pois ela dedus se vai ser utilizado o Joystick ou Keyboard
*/
/**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>; 
                Thiago Luiz Rodrigues <bobboyms@yahoo.com.br>; 
*/

class Keyboard{

	public:
		/** @brief
    		* Construtor de Keyboard que deve passar por parâmetro a Ação
		* que já foi criada na Classe Eventos
     		*/
		Keyboard(Rules::Action* action);
		/** @brief
    		* Destrutor padrão de Keyboard
     		*/
		~Keyboard();
		/** @brief
    		* Função que captura as ações de eventos do Keyboard (já declarada no Event)
		* e passa as ações correspondentes para o Buffer de Ações da Action
     		*/
		void KeyCapture(SDL_Event* Event);

	private:
		Rules::Action* actListener;
};

}

#endif
