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
#include "editor.h"

// this is a Default constructor of Editor
Editor::Editor(int x,int y, string filemap,string filetileset,CoreObjects *core)
{
	// init the resources
	this->initResources();
	render = core->render;
	event = core->event;

	// try to open map, if failcreate new Map
	this->fileMap = filemap;
	this->imgInformation = Render::Video::LoadBMP("../images/informationeditor.png");
	this->pointX = 0;
	this->pointY = 0;

	if ((this->map->loadMap(this->fileMap)) == ERROR) {
		this->X = x;
		this->Y = y;

		this->map->setFileName(this->fileMap);


		this->fileTileset = filetileset;
		this->map->setTilesetName(this->fileTileset);
		this->map->setXY(x,y);
		this->map->tileset->loadTileset(this->fileTileset);

		imgMap = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,X * TILE_SIZE, Y * TILE_SIZE, DF_DEPTH, 0, 0,0,0);

		this->imgTile = Render::Video::LoadBMP(this->map->tileset->getImgFile().c_str());
		if(this->imgTile == NULL){
      this->imgTile = Render::Video::LoadBMP("../images/tilesets/errortset.png");
    }

	}
	// if file exist, open map and put all properties
	else {
		this->X = this->map->getX();
		this->Y = this->map->getY();
		this->imgMap = Render::Video::CreateSurface(this->X * TILE_SIZE,this->Y * TILE_SIZE,DF_DEPTH);
		this->imgTile = Render::Video::LoadBMP(this->map->tileset->getImgFile().c_str());
		this->map->drawMap(this->imgMap,this->imgTile);
	}
	// Register pkg of Map
	this->pkgMap = new Render::Package;
	this->pkgPoint = new Render::Package;

	this->pkgMap->img = this->imgMap;

	this->mapDestRect.x = sizeTsetVideoX;
	this->mapDestRect.y = 0;
	this->mapDestRect.w = DF_WIDTH - sizeTsetVideoX;
	this->mapDestRect.h = DF_HEIGHT;
	this->pkgMap->srcRect = &this->mapSrcRect;
	this->pkgMap->destRect = &this->mapDestRect;
	this->pkgMap->number = 2;
	this->render->priority->addPackage(this->pkgMap);


	//Register pkg of Tileset
	this->pkgTile = new Render::Package;
	this->pkgTile->img = this->imgTile;
	this->pkgTile->destRect = NULL;
	this->pkgTile->srcRect = NULL;
	this->pkgTile->number = 10;
	this->render->priority->addPackage(this->pkgTile);

	//RegisterPkg of Information
	this->pkgInf = new Render::Package;
	this->pkgInf->img = this->imgInformation;
	this->pkgInf->destRect = NULL;
	this->pkgInf->srcRect = NULL;
	this->pkgInf->number = 36;
	this->render->priority->addPackage(this->pkgInf);

	this->pkgGrid = new Render::Package;
	this->pkgGrid->img = Render::Video::LoadBMP("../images/grid.png");
	this->pkgGrid->destRect = NULL;
	this->pkgGrid->srcRect = NULL;
	this->pkgGrid->number = 19;
	this->render->priority->addPackage(this->pkgGrid);

	//Pkg of Start Point Person
	this->pkgPoint->img = Render::Video::LoadBMP("../images/point.png");
	this->pkgPoint->destRect = new SDL_Rect;
	this->pkgPoint->destRect->x = sizeTsetVideoX;
	this->pkgPoint->destRect->y = 0;
	this->pkgPoint->srcRect = NULL;
	this->pkgPoint->number = 30;
	this->render->priority->addPackage(this->pkgPoint);


	SDL_WM_SetCaption("Map Editor","../images/ico.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("../images/ico.bmp"),NULL);
}

// Destructor that clear all resources
Editor::~Editor()
{
	delete map;
	delete pkgInf;
	delete pkgTile;
	delete pkgMap;
	delete pkgGrid;
	delete pkgPoint;
}

// This function initialize all resources the need to
// do, it is: Event, Video, Map.
void Editor::initResources() {
	map   = new Scenario::Map();
	map2   = new Scenario::Map();
	map3  = new Scenario::Map();

	// define the size of rectangle that the map goes to occupy
	this->mapSrcRect.x = 0;
	this->mapSrcRect.y = 0;
	this->mapSrcRect.w = DF_WIDTH - sizeTsetVideoX;
	this->mapSrcRect.h = DF_HEIGHT;

	this->map2SrcRect.x = 0;
	this->map2SrcRect.y = 0;
	this->map2SrcRect.w = DF_WIDTH - sizeTsetVideoX;
	this->map2SrcRect.h = DF_HEIGHT;

	this->map3SrcRect.x = 0;
	this->map3SrcRect.y = 0;
	this->map3SrcRect.w = DF_WIDTH - sizeTsetVideoX;
	this->map3SrcRect.h = DF_HEIGHT;
	// set the positions of scrolling map
	this->cursorY = 0;
	this->cursorX = 0;
}


// receiver the event ocurred and scroll the map
// verifying if is in end
void Editor::scrolling(int movement) {
	if ((movement == SCRL_RIGHT) & ((this->X * TILE_SIZE) > (this->mapSrcRect.w)) ) {
			this->mapSrcRect.x += TILE_SIZE;
			this->mapSrcRect.w = this->mapSrcRect.x + (DF_WIDTH - sizeTsetVideoX);
			this->pkgPoint->destRect->x -= TILE_SIZE;
			this->cursorX++;
	}
	if ((movement == SCRL_LEFT) & (this->mapSrcRect.w >(DF_WIDTH - sizeTsetVideoX))) {
		this->mapSrcRect.x -= TILE_SIZE;
		this->mapSrcRect.w = this->mapSrcRect.x + (DF_WIDTH - sizeTsetVideoX);
		this->pkgPoint->destRect->x += TILE_SIZE;
		this->cursorX--;
	}
	if ((movement == SCRL_DOWN) & ((this->mapSrcRect.h + TILE_SIZE) <= (this->Y * TILE_SIZE))) {
		this->mapSrcRect.y += TILE_SIZE;
		this->mapSrcRect.h = this->mapSrcRect.y + DF_HEIGHT ;
		this->pkgPoint->destRect->y -= TILE_SIZE;
		this->cursorY++;
	}
	if ((movement == SCRL_UP) & (this->mapSrcRect.y  > 0)) {
		this->mapSrcRect.y -= TILE_SIZE;
		this->pkgPoint->destRect->y += TILE_SIZE;
		this->mapSrcRect.h = this->mapSrcRect.y + DF_HEIGHT ;
		this->cursorY--;
	}
}

// draw the Particle of map
void Editor::drawParticle(int x, int y, int tbase8) {
	SDL_Rect rectMap, rectTile;
	rectMap.x = x;
	rectMap.y = y;
	rectMap.w = TILE_SIZE;
	rectMap.h = TILE_SIZE;

	div_t temp;
	temp = div(tbase8,10);

	rectTile.x = temp.rem * TILE_SIZE;
	rectTile.y = temp.quot * TILE_SIZE;
	rectTile.w = TILE_SIZE;
	rectTile.h = TILE_SIZE;

	SDL_BlitSurface(this->imgTile,&rectTile,this->imgMap,&rectMap);
}
// this function analyze the events into Action
// and make all actions necessary
void Editor::eventAnalyzer() {
    while (event->action.firstAction() != 0) {
        if (event->action.firstAction() == ACT_EXIT) {
            this->quit = true;
            event->action.removeAction();
        }
        if (event->action.firstAction() == ACT_MV_RIGHT) {
            this->scrolling(SCRL_RIGHT);
            event->action.removeAction();
        }
        if (event->action.firstAction() == ACT_MV_LEFT) {
            this->scrolling(SCRL_LEFT);
            event->action.removeAction();
        }
        if (event->action.firstAction() == ACT_MV_DOWN) {
            this->scrolling(SCRL_DOWN);
            event->action.removeAction();
        }
        if (event->action.firstAction() == ACT_MV_UP) {
            this->scrolling(SCRL_UP);
            event->action.removeAction();
        }
				if (event->action.firstAction() == ACT_MOUSECL_LEFT) {
					int mousex, mousey;
					mousex = (event->event.button.x / TILE_SIZE);
					mousey = (event->event.button.y / TILE_SIZE);
					// verify if the mouse is on Tileset Box
					if ((event->event.button.x) <= this->sizeTsetVideoX) {
						this->clipBoard = Scenario::Tileset::matrixToBase8(mousex,mousey);
						cout <<"Clipboard = "<<this->clipBoard<<endl;
						event->action.removeAction();
					}
					// if is on map box, draw the particle
					else {
						this->map->map[(mousex - (this->sizeTsetVideoX/TILE_SIZE)) + this->cursorX][mousey + this->cursorY] = this->clipBoard;
						pthread_mutex_lock(&render->priority->videoMutex);
						this->drawParticle(((mousex * TILE_SIZE) - this->sizeTsetVideoX) + (TILE_SIZE * this->cursorX) ,(mousey * TILE_SIZE) + (this->cursorY * TILE_SIZE),this->clipBoard);
						pthread_mutex_unlock(&render->priority->videoMutex);
						cout <<"passou"<<endl;
					}
				}
				if (event->action.firstAction() == ACT_MOUSECL_RIGHT) {
                    cout <<"ake"<<endl;
                    int mousex, mousey;
                    mousex = ((event->event.button.x - sizeTsetVideoX) / TILE_SIZE);
                    mousey = ((event->event.button.y) / TILE_SIZE);
                    if ((event->event.button.x) > this->sizeTsetVideoX) {
                      pointX =( mousex * TILE_SIZE) + this->mapSrcRect.x;
                      pointY = (mousey * TILE_SIZE) + mapSrcRect.y;
                      map->startPointX = pointX;
                      map->startPointY = pointY;
                      pkgPoint->destRect->x = (mousex * TILE_SIZE) +this->sizeTsetVideoX ;
                      pkgPoint->destRect->y = mousey * TILE_SIZE;
                    }
                    event->action.removeAction();
                }
				// Sav the Map
				if (event->action.firstAction() == ACT_FIRE) {
					map->saveMap(this->fileMap);
					cout<<"map save with success"<<endl;
					event->action.removeAction();
				}

				// if the action does not compatible, then remove
        if (event->action.firstAction() != 0) {
            event->action.removeAction();
        }
    }
}
void Editor::loop() {

	this->quit = false;
	while (this->quit == false) {
    event->capture();
		eventAnalyzer();
		SDL_Delay(30);
	}
	this->render->priority->removePackage(this->pkgTile->number);
	this->render->priority->removePackage(this->pkgMap->number);
	this->render->priority->removePackage(this->pkgInf->number);
	this->render->priority->removePackage(19);
	this->render->priority->removePackage(30);

	SDL_FreeSurface(this->imgInformation);
	SDL_FreeSurface(this->imgMap);
	SDL_FreeSurface(this->imgTile);
	SDL_FreeSurface(this->pkgGrid->img);
	SDL_FreeSurface(this->pkgPoint->img);
}


