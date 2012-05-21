/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva,                         *
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
#ifndef RULESACTION_H
#define RULESACTION_H
#include <list>
#include <pthread.h>
#include <iostream>

using namespace std;


namespace Rules {

/** @section action_sec Descrição
*	Esta classe Action tem por funcionalidade armazenar todas
*       as ações do jogo, tanto de personagens quanto de IA
*       e chamar as funções adequadas mapeadas para ser executadas
*       em lua.
*	Esta classe contém seções críticas onde somente podem ser executada
*       uma thread por vez
*/
/**
	@author
		@li Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		@li Gabriel Vedana Queiroz <gabielvq@hotmail.com>;

*/

class Action{
	public:
		/**
		* @brief Construtor padrão de Action
		<br>	Default constructor for Action Class
		*/
		Action();
		/**
		* @brief Destrutor padrão de Action
		<br> Default Destructor of Action Class
		*/
		~Action();
		/*
		* @brief
		* 	Adiciona uma ação ao buffer de ações,
		*       neste trecho há seção crítica
		<br> add an action on the action buffer, this section use critial section
		*/
		void addAction(int nAction);
		/**
		* @brief
		* 	Retorna a próxima ação a ser executada
		*       neste trecho há seção crítica
		<br> Return the next action on the list to be perfomed
		* this passage is a critical section
		*/
		int firstAction();
		/**
		* @brief
		* 	Remove a primeira ação da lista
		*	neste trecho há seção crítica
		<br> Remove the fisrt action of list
		* this passage is a critical section
		*/
		void removeAction();
	private:
		// Lista em formato de Fila que funciona como buffer de todas as ações
		list<int> buffer;
		// Mutex que trava nas partes críticas
		pthread_mutex_t mutex;
};

}

#endif
