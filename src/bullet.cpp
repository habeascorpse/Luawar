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
#include "bullet.h"
Bullet::Bullet(int posX, int posY,SDL_Rect *mapSrcRect,SDL_Surface* img,int priority,Render::VideoRender* Render,b2World* world,int direction){
        this->x = posX;
        this->y = posY;

        pkg.img = img;
        this->mapSrcRect = mapSrcRect;
        pkg.destRect = new SDL_Rect;
        pkg.srcRect = NULL;
        pkg.number = priority;
        this->render = Render;
        this->running = 1;

        //Body Definition
        b2BodyDef bodyDef;
        if (direction == ACT_MV_LEFT)
          bodyDef.position.Set(x,y+30);
        else
          bodyDef.position.Set(x + 50,y+30);
        bodyDef.massData.mass = 8;
        bodyDef.isBullet = true;
        bodyDef.fixedRotation = false;
        bodyDef.userData = this;
        body = world->CreateBody(&bodyDef);

        b2PolygonDef shapeDef;
        shapeDef.SetAsBox(pkg.img->w/2, pkg.img->h/2);
        shapeDef.density = 1;
        shapeDef.friction =0;
        shapeDef.filter.categoryBits = 0x0005;
        shapeDef.filter.maskBits = 0x0005;
        shapeDef.filter.groupIndex = 1;
        body->CreateShape(&shapeDef);
        body->SetMassFromShapes();
        this->direction = direction;

        render->priority->addPackage(&pkg);
}

Bullet::~Bullet() {
  render->priority->removePackage(pkg.number);
  delete pkg.destRect;
}

void Bullet::refresh() {
  b2Vec2 position = this->body->GetPosition();
  pkg.destRect->x = (position.x - (pkg.img->w / 2)) - mapSrcRect->x;
  pkg.destRect->y = (position.y - (pkg.img->h / 2))- mapSrcRect->y;
  if (this->direction == ACT_MV_LEFT)
    body->SetLinearVelocity(b2Vec2(-600,0));
  else
    body->SetLinearVelocity(b2Vec2(600,0));

  body->ApplyTorque(999000);
}

