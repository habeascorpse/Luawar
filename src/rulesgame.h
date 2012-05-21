/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva Gabriel Vedana Queiroz   *
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
#ifndef RULESRULES_H
#define RULESRULES_H

#include <SDL/SDL.h>
#include <pthread.h>
#include <list>
#include "defs.h"
#include "event.h"
#include "videorender.h"
#include "package.h"
#include "person.h"
#include "map.h"
#include "aicontrol.h"
#include "api.h"
#include "layermanager.h"
#include "particlecache.h"
#include "particlesystem.h"
#include "sound.h"
#include "bullet.h"
#include "bulletmanager.h"
#include "contact.h"
#include "refparticle.h"
#include "coreobjects.h"
#include "particlelua.h"

#include <luabind/luabind.hpp>
#include <Box2D.h>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include "objectmanager.h"


namespace Rules {

/**
	@author Alan de Oliveira Silva Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/

/**
 * @section rulesgame_sec
 *  Esta classe implementa a parte de regras do jogo
 * tanto quanto regras da física, quanto da regras gerais. Utilizando a engine
 * você deverá utilizá-la separadamente pois esta classe faz parte especificamente de
 * Luawar.
 */
class RulesGame{
	public:
		/** @brief RulesGame é o Construtor que requer um mapa em sua construcão
		 *
		 */
		RulesGame(string filePerson,string fileIA,string fileBack1,string fileBack2,string fileFore,string fileObj,Scenario::Map* map,Scenario::Map* map2,CoreObjects* coreObj);
		/** @brief
		 * Destrutor do RulesGame, não requer parâmetro
		 */
		~RulesGame();
		/** @brief
		*	inicializa o subsistema de Regras do Jogo.
		*/
		void init();
		/** @brief
		* Termina o Subsistema de Regras do Jogo.
		*/

		bool running;

	private:

		void loop();

		// Rules
		void eventAnalyzer();
		void scrolling();

		//Particle Manager
		Render::RefParticle *refParticle;


		void bulletAnalyzer();
		void addBullet(int posX, int posY,SDL_Surface* img,Mix_Chunk* soundMix);
		void destroyBullet();
		list<Bullet *> bulletList;
		int numberBullet;


		// threads variables
		Events::Event* event;
		Render::VideoRender *render;

		//Person
		Person* person;
		unsigned int tmpLastMov;
		unsigned int lastMov;

		//IA
		AI::AiControl *aiControl;
		AI::ObjectAI *ia1;

        // Map
		Render::Package *pkgMap;
		Render::Package *pkgMap2;
		Scenario::Map *map;
		Scenario::Map *map2;
		SDL_Rect *mapSrcRect;
		SDL_Rect *mapDestRect;
		SDL_Rect *map2SrcRect;
		SDL_Rect *map2DestRect;


		//BackGround and Foreground
		Scenario::BgLayer* Backgound;
		Scenario::BgLayer* Background2;
		Scenario::BgLayer* ForeGround1;

		Render::Package *pkgLogo;

		//Screen
		int midScreenX,midScreenY;

		// Lua
		lua_State *L;

		//Physics
		b2World* world;

		//Particle System
		Render::ParticleCache *pcache1;
		Render::ParticleCache *bloodCache;
		Render::ParticleCache *smokeCache;

		//Bullets
		BulletManager *bmanager;

		Scenario::Sound *sound;

		CoreObjects *core;

		gcn::SDLInput* input;
    gcn::SDLGraphics* graphics;
    gcn::SDLImageLoader* imageLoader;
    gcn::Gui* gui;
    gcn::Container* top;
    gcn::ImageFont* font;
    gcn::Label* label;
    Render::Package pkgGui;

    int lastLife;

    //Jump Sound
    Mix_Chunk* soundJump;

    int gameState;

    ObjectManager *mapObject;

};

}

#endif
