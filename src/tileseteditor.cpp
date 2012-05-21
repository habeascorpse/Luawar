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
#include "tileseteditor.h"

namespace Editors {
// this is a Default constructor of Editor
TileSetEditor::TileSetEditor(string fileTileset,string fileImage,CoreObjects* core)
{
// init the resources
	render = core->render;
	event = core->event;
	this->initResources();

// try to open tileset, if failcreate new tileset
	this->fileTileset = fileTileset;
	this->fileImage = fileImage;
	this->imgInformation = Render::Video::LoadBMP("../images/tilesets/informationteditor.png");
	for (i = 0;i<TILESET_X;i++) {
		for (j = 0;j<TILESET_Y;j++) {
			tileSet->setProperty(i,j,0);
		}
	}
	if ((this->tileSet->loadTileset(fileTileset.c_str())) == ERROR) {
		this->X = TILESET_X;
		this->Y = TILESET_Y;

		if (tileSet->setImgFile(this->fileImage)== SUCCESS){
			if (tileSet->saveTileset(this->fileTileset) == SUCCESS){
				cout<<"TileSet save with success"<<endl;
			}
		}


	}
// if file exist, open tileset and put all properties
	else {
		this->X = TILESET_X;
		this->Y = TILESET_Y;
	}
// create the Surfaces
	this->imgTile = Render::Video::LoadBMP(this->tileSet->getImgFile().c_str());
  if(this->imgTile == NULL){
      this->imgTile = Render::Video::LoadBMP("../images/tilesets/errortset.png");
    }
//Register pkg of Tileset
	this->pkgTile = new Render::Package;
	this->pkgTile->img = this->imgTile;
	this->pkgTile->destRect = NULL;
	this->pkgTile->srcRect = NULL;
	this->pkgTile->number = 2;
	this->render->priority->addPackage(this->pkgTile);

//RegisterPkg of Information
	this->pkgInf = new Render::Package;
	this->pkgInf->img = this->imgInformation;
	this->pkgInf->destRect = NULL;
	this->pkgInf->srcRect = NULL;
	this->pkgInf->number = 3;
	this->render->priority->addPackage(this->pkgInf);


	SDL_WM_SetCaption("TileSet Editor","../images/ico.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("../images/ico.bmp"),NULL);
	top->add(label);
	render->priority->addPackage(&pkgGui);
}

// Destructor that clear all resources
TileSetEditor::~TileSetEditor()
{
	delete tileSet;
	delete pkgInf;
	delete pkgTile;

	render->priority->removePackage(pkgGui.number);
  SDL_FreeSurface(pkgGui.img);

  delete label;
  delete font;
  delete top;
  delete gui;

  delete input;
  delete graphics;
  delete imageLoader;

}

// This function initialize all resources the need to
// do, it is: Event, Video, Map.
void TileSetEditor::initResources() {

	tileSet   = new Scenario::Tileset();

// define the size of rectangle that the map goes to occupy
	this->tileSrcRect.x = 0;
	this->tileSrcRect.y = 0;
	this->tileSrcRect.w = DF_WIDTH - sizeTsetVideoX;
	this->tileSrcRect.h = DF_HEIGHT;
// set the positions of scrolling map
	this->cursorY = 0;
	this->cursorX = 0;

	// Initializations of Guichan

  pkgGui.destRect = NULL;
  pkgGui.number = 100;
  pkgGui.srcRect = NULL;
  pkgGui.img = Render::Video::CreateSurface(640 ,480,DF_DEPTH);

  SDL_EnableUNICODE(1);
  imageLoader = new gcn::SDLImageLoader();
  gcn::Image::setImageLoader(imageLoader);
  graphics = new gcn::SDLGraphics();
  graphics->setTarget(pkgGui.img);
  input = new gcn::SDLInput();

  font = new gcn::ImageFont("../images/Font/font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]");
  gcn::Widget::setGlobalFont(font);

  gui = new gcn::Gui();
  gui->setGraphics(graphics);
  gui->setInput(input);

  top = new gcn::Container();
  top->setDimension(gcn::Rectangle(sizeTsetVideoX, 0, 640, 480));
  gui->setTop(top);

  //Map
  label = new gcn::Label("Valor do Tileset:");
  label->setPosition(100, 200);
}

// Draw grid of tile
void TileSetEditor::drawGridTile() {

	int i,j, sizetx,sizety;
	sizetx = sizeTsetVideoX;
	sizety = DF_HEIGHT;
	SDL_Rect destRect;
	for (i = 0;i<TILESET_X;i++) {
		destRect.x = (i + 1) * TILE_SIZE;
		destRect.y = 0;
		destRect.w = 2;
		destRect.h = sizety;
		SDL_FillRect(this->imgTile,&destRect,91);
	}

	for (j = 0;j<TILESET_Y;j++) {
		destRect.x = 0;
		destRect.y = (j + 1) * TILE_SIZE;
		destRect.w = sizetx;
		destRect.h = 2;
		SDL_FillRect(this->imgTile,&destRect,91);
	}
}


// this function analyze the events into Action
// and make all actions necessary
void TileSetEditor::eventAnalyzer() {
    while (event->action.firstAction() != 0) {
        if (event->action.firstAction() == ACT_EXIT) {
            this->quit = true;
            event->action.removeAction();
        }
// Save the tileSet
	if (event->action.firstAction() == ACT_FIRE) {
		if (tileSet->setImgFile(this->fileImage)== SUCCESS){
			if (tileSet->saveTileset(this->fileTileset) == SUCCESS){
				cout<<"TileSet save with success"<<endl;
				label->setCaption("Tileset salvo!");
			}
		}
		event->action.removeAction();
	}

	if (event->action.firstAction() == ACT_MOUSECL_LEFT) {
		this->clipBoard = 0;
		mousex = (event->event.button.x / TILE_SIZE);
		mousey = (event->event.button.y / TILE_SIZE);
// verify if the mouse is on Tileset Box

		if ((event->event.button.x) <= this->sizeTsetVideoX) {
			this->clipBoard = Scenario::Tileset::matrixToBase8(mousex,mousey);
			cout <<"Clipboard antes = "<<this->clipBoard<<endl;

			this->clipBoard = this->tileSet->getProperty(this->clipBoard) +1;
//pass base positive
			if(clipBoard < 0){
				this->clipBoard = this->clipBoard * -1;
			}

			cout <<"Clipboard depois = "<<this->clipBoard<<endl;
			this->tileSet->setProperty(mousex,mousey,this->clipBoard);
			stringstream stream;
			stream <<"Valor:"<<this->clipBoard;
			label->setCaption(stream.str());
//print in sreen

			event->action.removeAction();
		}
	}
	if (event->action.firstAction() == ACT_MOUSECL_RIGHT ) {
// verify if the mouse is on Tileset Box
		if ((event->event.button.x) <= this->sizeTsetVideoX) {
			this->clipBoard = Scenario::Tileset::matrixToBase8(mousex,mousey);
			cout <<"Clipboard antes = "<<this->clipBoard<<endl;
			this->clipBoard = this->tileSet->getProperty(this->clipBoard) -1;
			if(clipBoard < 0){
				clipBoard = 0;
			}
			cout <<"Clipboard depois= "<<this->clipBoard<<endl;
			this->tileSet->setProperty(mousex,mousey,this->clipBoard);
			stringstream stream;
			stream <<"Valor:"<<this->clipBoard;
			label->setCaption(stream.str());
			event->action.removeAction();
		}
	}
// if the action does not compatible, then remove
        if (event->action.firstAction() != 0) {
            event->action.removeAction();
        }
    }
}

void TileSetEditor::loop() {

	this->drawGridTile();
	this->quit = false;
	while (this->quit == false) {
    event->capture();
		eventAnalyzer();
		gui->logic();
    pthread_mutex_lock(&render->priority->videoMutex);
    gui->draw();
    pthread_mutex_unlock(&render->priority->videoMutex);
		SDL_Delay(50);
	}
	this->render->priority->removePackage(this->pkgTile->number);
	this->render->priority->removePackage(this->pkgInf->number);
	SDL_FreeSurface(this->imgInformation);
	SDL_FreeSurface(this->imgTile);
}
}

