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

#include "video.h"


namespace Render {


// enable the video on default parameters
Video::Video()
{
	this->screen = SDL_SetVideoMode(DF_WIDTH, DF_HEIGHT, DF_DEPTH, SDL_HWSURFACE|SDL_DOUBLEBUF);
	this->Width = DF_WIDTH;
	this->Height = DF_HEIGHT;
	this->Depth = DF_DEPTH;
	SDL_WM_SetCaption("Luawar","../images/ico.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("../images/ico.bmp"),NULL);

}

// enable the video with defined parameters
Video::Video(int width,int height,int depth) {
	this->screen = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE|SDL_DOUBLEBUF);
	this->Width = width;
	this->Height = height;
	this->Depth = depth;
	SDL_WM_SetCaption("Luawar","../images/ico.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("../images/ico.bmp"),NULL);
}

//return size X from the screen
int Video::getWidht() {
	return this->Width;
}

//return size Y from the screen
int Video::getHeight() {
	return this->Height;
}

//returns the amount from colors of the screen
int Video::getDepth() {
	return this->Depth;
}

//Dumb the size of the screen and the amount of colors
//return SUCESS or ERROR
int Video::setScreen(int width,int height,int depth) {

	if ((this->screen = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE|SDL_DOUBLEBUF))) {
		this->Width = width;
		this->Height = height;
		this->Depth = depth;
		return SUCCESS;
	}
	else {
		cout <<"Error on change screen format!"<<endl;
		return ERROR;
	}

}

// this function load a bmp file and return the surface with colorkey
SDL_Surface* Video::LoadBMP(const char* file) {
    SDL_Surface* temp;

    if ((temp = IMG_Load(file)) == NULL)
        cout <<"Error on Load Image: "<<file<<endl;


    return temp;
}

SDL_Surface* Video::CreateSurface(int x,int y,int depth) {
  SDL_Surface *temp;
  temp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,x,y,depth, 0, 0, 255, 0x000000ff);
  SDL_Surface *temp2 = SDL_DisplayFormatAlpha(temp);
  SDL_FreeSurface(temp);
  return temp2;
}


//destructor class
Video::~Video()
{
	SDL_FreeSurface(this->screen);
}


}
