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
#include "event.h"


namespace Events {
//it chooses keyboard or joystick
Event::Event(int eventType)
{
//if it will be JOYSTICK, instance the object
	if (eventType == JOYSTICK) {
		this->eventType = eventType;
		this->eventObj = new Joystick(&action);
	}
//else instance joystick
	if (eventType == KEYBOARD) {
		this->eventType = eventType;
		this->eventObj = new Keyboard(&action);
	}
}


Event::~Event()
{
//if it will be JOYSTICK, liberates it of the memory
	if (this->eventType == JOYSTICK)
		delete reinterpret_cast<Joystick *> (eventObj);
//esle liberates it of the memory the KEYBORAD
	if (this->eventType == KEYBOARD)
		delete reinterpret_cast<Keyboard *> (eventObj);
}

void Event::change(int eventType) {
    this->eventType = eventType;
}


//while running, it reads the object
    void Event::capture() {
        if (eventType == KEYBOARD)
            reinterpret_cast<Keyboard *> (eventObj)->KeyCapture(&event);
        if (eventType == JOYSTICK)
            reinterpret_cast<Joystick *> (eventObj)->JoyCapture(&event);
    }

}
