/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva,Gabriel Vedana Queiroz   *
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
#include "object.h"

Object::Object(int posX, int posY,SDL_Surface* img,int priority,CoreObjects *core){

        this->x = posX;
        this->y = posY;

        pkg.img = img;
        this->core = core;
        pkg.destRect = new SDL_Rect;
        pkg.srcRect = NULL;
        pkg.number = priority;
        pkg.rotable = true;

        //Body Definition
        b2BodyDef bodyDef;
        bodyDef.position.Set(x,y);
        bodyDef.massData.mass = 40;
        bodyDef.massData.I = 20.0f;
        bodyDef.allowSleep = true;
        bodyDef.isSleeping = false;

        bodyDef.fixedRotation = false;
        bodyDef.userData = this;
        body = core->world->CreateBody(&bodyDef);

        b2PolygonDef shapeDef;
        shapeDef.SetAsBox(pkg.img->w/2, pkg.img->h/2);
        shapeDef.density = 9;
        shapeDef.friction =0.2;
        shapeDef.filter.categoryBits = 0x0004;
        shapeDef.filter.maskBits = 0x0004;
        shapeDef.filter.groupIndex = 1;
        body->CreateShape(&shapeDef);
        body->SetMassFromShapes();
        pkg.rotation = body->GetAngle();
        core->render->priority->addPackage(&pkg);
}

Object::~Object() {
  core->render->priority->removePackage(pkg.number);
  SDL_FreeSurface(pkg.img);
  delete pkg.destRect;
}

void Object::refresh() {
  pkg.rotation = -1 * (body->GetAngle()  * (180/3.14159265));
  //cout <<"rotation:"<<pkg.rotation<<" X:"<<pkg.destRect->x<<" Y:"<<pkg.destRect->y<<" W:"<<pkg.destRect->w<< " H:"<<pkg.destRect->h<<endl;
  b2Vec2 position = this->body->GetPosition();
  pkg.destRect->x = (position.x - (pkg.destRect->w / 2)) - core->mapSrcRect->x;
  pkg.destRect->y = (position.y - (pkg.destRect->h / 2))- core->mapSrcRect->y;
}
