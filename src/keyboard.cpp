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
#include "keyboard.h"


namespace Events {

Keyboard::Keyboard(Rules::Action* action)
{
	this->actListener = action;
}

//destructor joystick
Keyboard::~Keyboard()
{
}
//it initiates the joystick
void Keyboard::KeyCapture(SDL_Event *Event) {
//if different of the 0
	while (SDL_PollEvent(Event)) {
//capture event botton
		if (Event->type == SDL_KEYDOWN) {
			if (Event->key.keysym.sym == SDLK_z) {

				actListener->addAction(ACT_FIRE);
			}

			if (Event->key.keysym.sym == SDLK_x) {

				actListener->addAction(ACT_JUMP);
			}

			if (Event->key.keysym.sym == SDLK_a) {

				actListener->addAction(ACT_JUMP);
			}
			if (Event->key.keysym.sym == SDLK_RIGHT) {

				actListener->addAction(ACT_MV_RIGHT);
			}
			if (Event->key.keysym.sym == SDLK_LEFT) {

				actListener->addAction(ACT_MV_LEFT);
			}
			if (Event->key.keysym.sym == SDLK_UP) {

				actListener->addAction(ACT_MV_UP);
			}
			if (Event->key.keysym.sym == SDLK_DOWN) {

				actListener->addAction(ACT_MV_DOWN);
			}
			if (Event->key.keysym.sym == SDLK_RETURN) {

				actListener->addAction(ACT_RETURN);
			}
			if (Event->key.keysym.sym == SDLK_ESCAPE) {

				actListener->addAction(ACT_EXIT);
			}
			if (Event->key.keysym.sym == SDLK_z) {

				actListener->addAction(ACT_FIRE);
			}

			// Numeric Keys
			if (Event->key.keysym.sym == SDLK_1) {

				actListener->addAction(ACT_K1);
			}
			if (Event->key.keysym.sym == SDLK_2) {

				actListener->addAction(ACT_K2);
			}
			if (Event->key.keysym.sym == SDLK_3) {

				actListener->addAction(ACT_K3);
			}
		}
		if (Event->type == SDL_KEYUP) {
			if ((Event->key.keysym.sym == SDLK_RIGHT) || (Event->key.keysym.sym == SDLK_LEFT)) {

				actListener->addAction(ACT_MV_STOPX);
			}
			if ((Event->key.keysym.sym == SDLK_UP) || (Event->key.keysym.sym == SDLK_DOWN)) {

				actListener->addAction(ACT_MV_STOPY);
			}
		}
		if (Event->type ==  SDL_MOUSEBUTTONDOWN) {
			if (Event->button.button ==  SDL_BUTTON_LEFT) {
				actListener->addAction(ACT_MOUSECL_LEFT);

			}
			if (Event->button.button ==  SDL_BUTTON_RIGHT) {
				actListener->addAction(ACT_MOUSECL_RIGHT);

			}
		}

	}

}


}
