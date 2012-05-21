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
#ifndef EDITOR_H
#define EDITOR_H
#include <pthread.h>
#include "defs.h"
#include "event.h"
#include "map.h"
#include "tileset.h"
#include "videorender.h"
#include "package.h"
#include "coreobjects.h"

#define SCRL_RIGHT 1
#define SCRL_LEFT  2
#define SCRL_UP    3
#define SCRL_DOWN  4


/**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>;
                Thiago Luiz Rodrigues <bobboyms@yahoo.com.br>;
*/
class Editor{
	public:

		Editor(int x,int y, string filemap,string filetileset,CoreObjects *core);

		void init();
		void loop();

    ~Editor();

		bool quit;

	private:


		void initResources();
		void drawParticle(int x, int y, int tbase5);

		Scenario::Map *map;
		Scenario::Map *map2;
		Scenario::Map *map3;

		SDL_Surface* imgMap;
		SDL_Surface* imgMap2;
		SDL_Surface* imgMap3;

		SDL_Surface* imgTile;
		SDL_Surface* imgTile2;
		SDL_Surface* imgTile3;
		SDL_Surface* imgInformation;

		Render::Package* pkgMap;
		Render::Package* pkgMap2;
		Render::Package* pkgMap3;
		Render::Package* pkgTile;
		Render::Package* pkgInf;
		Render::Package* pkgGrid;
		Render::Package* pkgPoint;

		SDL_Rect mapSrcRect;
		SDL_Rect mapDestRect;
		SDL_Rect map2SrcRect;
		SDL_Rect map2DestRect;
		SDL_Rect map3SrcRect;
		SDL_Rect map3DestRect;


		void eventAnalyzer();
		void scrolling(int movement);

		//resources
		Render::VideoRender* render;
		Events::Event* event;

		int X,Y;
		string fileMap;
		string fileMap2;
		string fileMap3;
		string fileTileset;
		// Tamanho que o Espaço do tileset Ocupará na Tela
		static const int sizeTsetVideoX = 256;

		int clipBoard, cursorX,cursorY;
		int pointX;
		int pointY;

};

#endif
