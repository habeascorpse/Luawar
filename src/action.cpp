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
#include "action.h"

namespace Rules {

  //it initiates thread
  Action::Action()
  {
    pthread_mutex_init(&mutex,NULL);
  }


  Action::~Action()
  {
    pthread_mutex_destroy(&mutex);
  }

  //it adds to an action the line, using mutex
  void Action::addAction(int nAction) {
    buffer.push_back(nAction);
  }

  //it returns the first action from the line
  int Action::firstAction() {
    list<int>::iterator i;
    i = buffer.begin();
    return *i;
  }

  //it remove action from the line
  void Action::removeAction() {

    list<int>::iterator i;

    i = buffer.begin();

    buffer.pop_front();

  }


}
