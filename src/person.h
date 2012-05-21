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
#ifndef PERSON_H
#define PERSON_H

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "defs.h"
#include "package.h"
#include "video.h"
#include "map.h"
#include "coreobjects.h"
#include "particlesystem.h"
#include <Box2D.h>

#ifdef LUA5.1

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>

}

#else

extern "C" {
	#include <lua50/lua.h>
	#include <lua50/lauxlib.h>
	#include <lua50/lualib.h>

}
#endif

#include <luabind/luabind.hpp>


/**
	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/
using namespace std;
class Person{
	public:
		Person(const char* file,CoreObjects *core);
		virtual ~Person();

		void report_errors(int status);
		int increaseLife(int quantity);
		int decreaseLife(int quantity);

		int setLife(int quantity);
		int increaseSpecial(int quantity);
		int decreaseSpecial(int quantity);
		void setDirection(int position);

		void jump();
		virtual void attack(bool status);
		void movRight(int quantity);
		void movLeft(int quantity);
		void stop();
		void setMov();

		void setAccelX(int acel);
		void setAccelY(int acel);
    void setMaster(int mast);

		int getPosX();
		int getPosY();
		int getSpeedX();
		int getSpeedY();
		int getAccelX();
		int getAccelY();
		int getSpecial();
		int getMaster();

		int getLife();
		int getDirection();
		bool getJumping();
		bool getMoving();
		bool isAttack();

		unsigned short int getSizeX();
		unsigned short int getSizeY();
		unsigned short int getSizeBlockX();
		unsigned short int getSizeBlockY();

		virtual void createBody(int x,int y);
		void heroMovement();


		bool colideLeft;
		bool colideRight;
		bool colide;
		bool jumping;

		Render::Package *imgPkg;
		SDL_Surface* imgPerson[16];
		b2Body* body;
		b2World* world;

		float weight;
		float density;
		float friction;

		unsigned int tmpWalking, tmpJumping, tmpAttack;

		unsigned short int sizexImg;
		unsigned short int sizeyImg;

		unsigned short int sizeBlockX;
		unsigned short int sizeBlockY;

		float ForceX;


	protected:

		void init(const char* file);

		SDL_Rect* srcRect;
		SDL_Rect* destRect;

		short int posX,posY;
		int speedX;
		int speedY;
		int acelX;
		int acelY;
    int master;
		unsigned int special;
		int life, direction;
		unsigned int specialLimit, lifeLimit;
		bool status, moving;
		bool attacking;
		int timeAttack;
		int timeAttack2;
		int attackTime;
		int attackFlag;



		char tempImg[] ;
		int tmpLastMov;
		int lastMov;


		lua_State *L;
		CoreObjects *core;




};



#endif
