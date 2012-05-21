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
#include "joystick.h"



namespace Events {


Joystick::Joystick(Rules::Action *action)
{
//it initiates the joystick
	SDL_Init(SDL_INIT_JOYSTICK);
//if different of the 0
	if(SDL_NumJoysticks()>0) {
		Joy=SDL_JoystickOpen(0);
		cout <<"Number of Buttons:"<<SDL_JoystickNumButtons(Joy)<<endl;
	} else
		cout<<"No Joystick found"<<endl;

	actListener = action;
}

//destructor joystick
Joystick::~Joystick()
{
	if(SDL_JoystickOpened(0))
		SDL_JoystickClose(Joy);
}

//capture event botton
void Joystick::JoyCapture(SDL_Event *Event) {
//while spoll, capture
	while (SDL_PollEvent(Event)) {

		if (Event->type == SDL_JOYBUTTONDOWN) {
			if (Event->jaxis.axis == 0) {
				cout <<"Fire Button Pressed"<<endl;
				actListener->addAction(ACT_FIRE);
			}

			if (Event->jaxis.axis == 3) {
				cout <<"Jump Button Pressed"<<endl;
				actListener->addAction(ACT_JUMP);
			}

			if (Event->jaxis.axis == 1) {
				cout <<"ChangeWeapon Button Pressed"<<endl;
				actListener->addAction(ACT_JUMP);
			}
			if (Event->jaxis.axis == 2) {
				cout <<"Scape Button Pressed"<<endl;
				actListener->addAction(ACT_EXIT);
			}

		}
		if (Event->type == SDL_JOYAXISMOTION) {
			if ((Event->jaxis.axis == 0) &(Event->jaxis.value > 0)) {
				cout<<"Right Button Pressed"<<endl;
				actListener->addAction(ACT_MV_RIGHT);
			}
			if ((Event->jaxis.axis == 0) &(Event->jaxis.value < 0)) {
				cout<<"Left Button Pressed"<<endl;
				actListener->addAction(ACT_MV_LEFT);
			}
			if ((Event->jaxis.axis == 0) &(Event->jaxis.value == 0)) {
				cout<<"Motion Button has solved"<<endl;
				actListener->addAction(ACT_MV_STOPX);
			}
			if ((Event->jaxis.axis == 1) &(Event->jaxis.value < 0)) {
				cout<<"Up Button Pressed"<<endl;
				actListener->addAction(ACT_MV_UP);
			}
			if ((Event->jaxis.axis == 1) &(Event->jaxis.value > 0)) {
				cout<<"Down Button Pressed"<<endl;
				actListener->addAction(ACT_MV_DOWN);
			}
			if ((Event->jaxis.axis == 0) &(Event->jaxis.value == 0)) {
				cout<<"Left Button Pressed"<<endl;
				actListener->addAction(ACT_MV_STOPY);
			}
		}
		if (Event->type ==  SDL_MOUSEBUTTONDOWN) {
			if (Event->button.button ==  SDL_BUTTON_LEFT) {
				actListener->addAction(ACT_MOUSECL_LEFT);
				cout <<"Mouse button Left has clicked"<<endl;
			}
			if (Event->button.button ==  SDL_BUTTON_RIGHT) {
				actListener->addAction(ACT_MOUSECL_RIGHT);
				cout <<"Mouse button Right has clicked"<<endl;
			}
		}

	}
}


}
