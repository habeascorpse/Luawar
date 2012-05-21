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
#ifndef EDITORTILESETEDITOR_H
#define EDITORTILESETEDITOR_H

#include <pthread.h>
#include <SDL_ttf.h>
#include <SDL/SDL.h>

#include "defs.h"
#include "event.h"
#include "tileset.h"
#include "coreobjects.h"
#include "videorender.h"
#include "package.h"
#include <guichan.hpp>
#include <guichan/sdl.hpp>



namespace Editors {

/**
	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/
class TileSetEditor{
	public:

		TileSetEditor(string fileTileset, string fileImage,CoreObjects* core);

		void init();
		void loop();

    ~TileSetEditor();

		bool quit;

	private:

		void printText(const char* text, SDL_Surface* dst);
		void initResources();
		void drawGridTile();
		void eventAnalyzer();

	//	SDL_Surface* valueTileSet;
		SDL_Surface* imgTile;
		SDL_Surface* imgInformation;

		Render::Package *pkgTile;
		Render::Package *pkgInf;

		SDL_Rect tileSrcRect;
		SDL_Rect tileDestRect;

		//resources
		Render::VideoRender* render;
		Events::Event* event;
		Scenario::Tileset* tileSet;

		int X,Y;
		int i,j;
		int mousex, mousey;
		string fileMap;
		string fileTileset, fileImage;
		// Tamanho que o Espaço do tileset Ocupará na Tela
		static const int sizeTsetVideoX = 256;

		int clipBoard, cursorX,cursorY;

		gcn::SDLInput* input;
    gcn::SDLGraphics* graphics;
    gcn::SDLImageLoader* imageLoader;
    gcn::Gui* gui;
    gcn::Container* top;
    gcn::ImageFont* font;
    gcn::Label* label;
    Render::Package pkgGui;
};

}

#endif
