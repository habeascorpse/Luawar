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

#include "videorender.h"

namespace Render {

VideoRender::VideoRender() : Video () {
	priority = new RenderPriority();
}

VideoRender::~VideoRender() {
    list<Package *>::iterator it;
	for (it = this->priority->pkg.begin();it!=this->priority->pkg.end();++it) {
        SDL_FreeSurface((*it)->img);
	}
	delete priority;
}

void VideoRender::init() {

	this->running = 1;
	pthread_create(&this->thread,NULL,VideoRender::start,this);

}

void VideoRender::kill() {
	this->running = 0;
	pthread_join(this->thread,NULL);
}

void* VideoRender::start(void* arg) {
	reinterpret_cast<VideoRender *>(arg)->loop();
	pthread_exit((void*) NULL);
}

void VideoRender::loop() {
	while (running) {
		SDL_Delay(TIME_RENDER);
		this->render();
	}
}


void VideoRender::render() {
	list<Package *>::iterator it;
	SDL_Rect drect;
	drect.x = 0;
	drect.y = 0;
	drect.w = DF_WIDTH;
	drect.h = DF_HEIGHT;
	pthread_mutex_lock(&priority->videoMutex);

	SDL_FillRect(this->screen,&drect,SDL_MapRGB(this->screen->format,255,255,255));
	for (it = this->priority->pkg.begin();it!=this->priority->pkg.end();++it) {
	    if ((*it)->destRect != NULL) {
            if (!((((*it)->destRect->x) > DF_WIDTH) || (((*it)->destRect->x + (*it)->destRect->w) < 0))) {
                if (((*it)->rotable == true) && ((*it)->lastRot !=(*it)->rotation )) {
                  (*it)->lastRot = (*it)->rotation;
                  SDL_Surface *temp = rotozoomSurface((*it)->img,(*it)->rotation, 1, 0);
                  (*it)->destRect->w = temp->w;
                  (*it)->destRect->h = temp->h;
                  SDL_BlitSurface(temp,(*it)->srcRect,this->screen,(*it)->destRect);
                  SDL_FreeSurface(temp);
                  //cout <<"rotation:"<<(*it)->rotation <<endl;
                }
                else
                  SDL_BlitSurface((*it)->img,(*it)->srcRect,this->screen,(*it)->destRect);
            }
	    }
	    else {
            SDL_BlitSurface((*it)->img,(*it)->srcRect,this->screen,(*it)->destRect);
	    }
	}

	SDL_Flip(this->screen);
	pthread_mutex_unlock(&priority->videoMutex);
}

}
