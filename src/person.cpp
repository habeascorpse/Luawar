/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira SilvaGabriel Vedana Queiroz    *
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
#include "person.h"

//it opens archive LUA with basic configurations of the personage
Person::Person(const char* file,CoreObjects *core) {
    this->core = core;
	L = core->L;
	this->world = core->world;
	init(file);

}

void Person::init(const char *file){
//abri arquivo lua com configuraçoes basicas do personagem

	int s = luaL_loadfile(core->L, file);

	if ( s==0 ) {
		// execute Lua Script
		s = lua_pcall(L, 0, LUA_MULTRET, 0);

    //set stack
    lua_getglobal (L,"ForceX");

		lua_getglobal (L,"tAttack");
		lua_getglobal (L,"tJumping");
		lua_getglobal (L,"tWalking");

		lua_getglobal (L,"attackLeftB");
		lua_getglobal (L,"attackLeftA");

		lua_getglobal (L,"attackRightB");
		lua_getglobal (L,"attackRightA");

		lua_getglobal (L,"jumpingLeftB");
		lua_getglobal (L,"jumpingLeftA");

		lua_getglobal (L,"jumpingRightB");
		lua_getglobal (L,"jumpingRightA");

		lua_getglobal (L,"walkingLeftD");
		lua_getglobal (L,"walkingLeftC");
		lua_getglobal (L,"walkingLeftB");
		lua_getglobal (L,"walkingLeftA");

		lua_getglobal (L,"walkingRightD");
		lua_getglobal (L,"walkingRightC");
		lua_getglobal (L,"walkingRightB");
		lua_getglobal (L,"walkingRightA");

		lua_getglobal (L, "direction");
		lua_getglobal (L, "density");
		lua_getglobal (L, "friction");
		lua_getglobal (L, "weight");
		lua_getglobal (L, "posY");
		lua_getglobal (L, "posX");
		lua_getglobal (L, "life");

		// return value stack

    this->ForceX = lua_tonumber(L,-27);
		this->tmpAttack = lua_tonumber(L,-26);
		this->tmpJumping = lua_tonumber(L,-25);
		this->tmpWalking = lua_tonumber(L,-24);

		this->imgPerson[15] = Render::Video::LoadBMP(lua_tostring(L,-23));
		this->imgPerson[14] = Render::Video::LoadBMP(lua_tostring(L,-22));
		this->imgPerson[13]  = Render::Video::LoadBMP(lua_tostring(L,-21));
		this->imgPerson[12]  = Render::Video::LoadBMP(lua_tostring(L,-20));

		this->imgPerson[11] = Render::Video::LoadBMP(lua_tostring(L,-19));
		this->imgPerson[10] = Render::Video::LoadBMP(lua_tostring(L,-18));
		this->imgPerson[9]  = Render::Video::LoadBMP(lua_tostring(L,-17));
		this->imgPerson[8]  = Render::Video::LoadBMP(lua_tostring(L,-16));


		this->imgPerson[7] = Render::Video::LoadBMP(lua_tostring(L,-15));
		this->imgPerson[6] = Render::Video::LoadBMP(lua_tostring(L,-14));
		this->imgPerson[5] = Render::Video::LoadBMP(lua_tostring(L,-13));
		this->imgPerson[4] = Render::Video::LoadBMP(lua_tostring(L,-12));

		this->imgPerson[3] = Render::Video::LoadBMP(lua_tostring(L,-11));
		this->imgPerson[2] = Render::Video::LoadBMP(lua_tostring(L,-10));
		this->imgPerson[1] = Render::Video::LoadBMP(lua_tostring(L,-9));
		this->imgPerson[0] = Render::Video::LoadBMP(lua_tostring(L,-8));

		this->direction = lua_tonumber(L, -7);
		this->density = lua_toboolean(L, -6);
		this->friction = lua_tonumber(L, -5);
		this->weight = lua_tonumber(L, -4);
		this->posY = lua_tonumber(L, -3);
		this->posX = lua_tonumber(L, -2);
		this->life = lua_tonumber(L, -1);


		this->lifeLimit = this->life;
		this->specialLimit = this->special;

	}

	report_errors(s);

	this->sizexImg = (this->imgPerson[0]->w - 8);
	this->sizeyImg = this->imgPerson[0]->h - 15;
	this->sizeBlockX = this->sizexImg / TILE_SIZE;
	this->sizeBlockY = this->sizeyImg / TILE_SIZE;
	this->imgPkg = new Render::Package;

	this->destRect = new SDL_Rect;
	this->destRect->x = this->posX;
	this->destRect->y = this->posY;
	//this->destRect->w = this->imgPerson[0]->w;
	//this->destRect->h = this->imgPerson[0]->h;

	this->srcRect = new SDL_Rect;
	this->srcRect->x = 0;
	this->srcRect->y = 0;
	//this->srcRect->w = this->imgPerson[0]->w;
	//this->srcRect->h = this->imgPerson[0]->h;

	this->imgPkg->img = this->imgPerson[1];
	this->imgPkg->destRect = this->destRect;
	this->imgPkg->srcRect = this->srcRect;

	this->acelX = 0;
	this->lastMov = 0;
	this->attackFlag = 0;
	this->timeAttack2 = 0;
	this->colide = false;
	this->master = 0;

}

Person::~Person() {

    for (int aux = 0; aux < 16; aux++)
        SDL_FreeSurface(this->imgPerson[aux]);

    delete destRect;
    delete srcRect;
    delete imgPkg;
    world->DestroyBody(body);
}


void Person::report_errors(int error) {
  if ( error!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}
//decrease life
int Person::increaseLife(int quantity){

	// verify size of quantity
	if((quantity > 0) && ((life + quantity) < LIMIT) && ((life + quantity) < lifeLimit))
		this->life += quantity;
	else
		this->life = lifeLimit;

	return 0;
}

// decrease life
int Person::decreaseLife(int quantity)
{
	// verify size of quantity
	if( (quantity >= 0) && ((life - quantity)>= 0))
		this->life -= quantity;
	else {
		this->status = false;
		this->life = 0;
	}
	core->refParticle->addParticle(getPosX(),getPosY(),core->bloodCache,core->render,core->mapSrcRect,60);
	cout <<this->life<<endl;
	return 1;
}

void Person::movRight(int quantity) {
  if (colideRight == false) {
    if ((this->body->GetLinearVelocity().y < 10) || (this->body->GetLinearVelocity().y > -10)) {
      b2Vec2 speed(quantity,this->body->GetLinearVelocity().y);
      this->body->SetLinearVelocity(speed);
      this->moving = true;
      this->direction = ACT_MV_RIGHT;
    }
  }
}

void Person::movLeft(int quantity) {
  if (colideLeft == false) {
    if ((this->body->GetLinearVelocity().y < 10) || (this->body->GetLinearVelocity().y > -10)) {
      b2Vec2 speed(-quantity,this->body->GetLinearVelocity().y);
      this->body->SetLinearVelocity(speed);
      this->moving = true;
      this->direction = ACT_MV_LEFT;
    }
  }
}


//it modifies the life
int Person::setLife(int quantity){

	// verify size of quantity
	if ((quantity > 0) && (quantity < LIMIT) && ((life + quantity) < lifeLimit ))
		this->life += quantity;
	else
		this->life = lifeLimit;
	return 1;
}

//increse special of the personage
int Person::increaseSpecial(int quantity) {

	// verify size of quantity
	if ((quantity > 0) && ((special + quantity) < LIMIT) && ((special + quantity) < specialLimit))
		this->special += special;
	else {
		cout <<"number of special more than allowed"<<endl;
		this->special = specialLimit;
	}
	return 1;
}

//decrase special of the personagem
int Person::decreaseSpecial(int quantity){
	// verify size of quantity
	if ((quantity > 0) && ((special - quantity) > 0))
		this->special -= special;
	else {
		cout <<"number of special minor than allowed"<<endl;
		this->special = 0;
	}
	return 1;
}

//it modifies the direction, left or right
void Person::setDirection(int position){
	this->direction = position;
}


//it modifies the jumping, motionless or jumping
void Person::jump(){
	b2Vec2  v1 = body->GetLinearVelocity();
  if ( int(v1.y) != 0 ) return;

  body->WakeUp();

  b2Vec2 speed(this->body->GetLinearVelocity().x,-30000);
	this->body->SetLinearVelocity(speed);
}

//it set master ia or not
void Person::setMaster(int mast) {
    this->master = mast;
}
//it returns the posiction X
int Person::getPosX() {
	b2Vec2 position = this->body->GetPosition();
	int x = position.x ;
	return x - (sizexImg / 2);
}

//it returns the posiction Y
int Person::getPosY() {
	b2Vec2 position = this->body->GetPosition();
	int y = position.y - (sizeyImg /2);
	return y;
}

//it returns the speed of cordinate X
int Person::getSpeedX() {
	return this->body->GetLinearVelocity().x;
}
// it returns the speed of coordinate y
int Person::getSpeedY() {
	return this->body->GetLinearVelocity().y;
}

int Person::getAccelX() {
	return this->acelX;
}

int Person::getAccelY() {
	return this->acelY;
}

void Person::setAccelX(int acel) {
	this->acelX = acel;
}

void Person::setAccelY(int acel) {
	this->acelY = acel;
}

//it returns the master ia or not
int Person::getMaster(){
    return this->master;
}

//it returns the quantity of special
int Person::getSpecial(){
	return this->special;
}

//it returns the quantity of life
int Person::getLife(){
	return this->life;
}
////it returns the direction that the personage is if moving
int Person::getDirection(){
	return this->direction;
}

//it returns the direction that personage is if jumping
bool Person::getJumping(){
  if ((this->body->GetLinearVelocity().y > 10) || (this->body->GetLinearVelocity().y < -10))
    this->jumping = true;
  else
    this->jumping = false;

	return this->jumping;
}

void Person::attack(bool status) {
    //if (timeLast ==
  attacking = status;
  timeAttack = 0;
  if (timeAttack2 >= 500) {
      timeAttack2 = 0;
      if (status == true) {
        if (this->attackFlag == 0)
          attackFlag =1;
        else
          attackFlag = 0;
      }
  }
}


bool Person::isAttack() {
  return attacking;
}

//it returns if the personage is if moving
bool Person::getMoving(){
  return moving;

}

unsigned short int Person::getSizeX() {
	return this->sizexImg;
}

unsigned short int Person::getSizeY() {
	return this->sizeyImg;
}
unsigned short int Person::getSizeBlockX() {
	return this->sizeBlockX;
}
unsigned short int Person::getSizeBlockY() {
	return this->sizeBlockY;
}

void Person::createBody(int x,int y) {

	b2BodyDef bodyDef;
	bodyDef.position.Set(x,y);
	bodyDef.massData.mass = weight;
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);

	b2PolygonDef shapeDef;
	shapeDef.SetAsBox(sizexImg/2, sizeyImg/2);
	shapeDef.density = density;
	shapeDef.friction = friction;
	shapeDef.filter.categoryBits = 0x0002;
    shapeDef.filter.maskBits = 0x0002;
    shapeDef.filter.groupIndex = 1;

	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();

}

void Person::heroMovement() {
    timeAttack2 +=TIME_RULES;
    if (this->getMoving() && !(this->isAttack())) {
      if (this->isAttack()) {
          if (timeAttack <500)
            timeAttack += TIME_RULES;
          else
            this->attack(false);
          if (this->getDirection() == ACT_MV_RIGHT)
            this->imgPkg->img = this->imgPerson[12 + attackFlag];
          else
            this->imgPkg->img = this->imgPerson[14 + attackFlag];
      }
      else {

        if ((this->getDirection() == ACT_MV_RIGHT) ) {

                  this->movRight(ForceX);
                  if (!this->getJumping()) {
                      if (lastMov == 0) {
                        this->imgPkg->img = this->imgPerson[1];
                        lastMov = 1;
                      }
                      this->tmpLastMov += TIME_RULES;

                      if (this->tmpWalking <= this->tmpLastMov) {
                          this->tmpLastMov = 0;
                          this->lastMov++;

                          if (this->lastMov >= 4)
                              this->lastMov=0;
                          this->imgPkg->img = this->imgPerson[lastMov];
                      }
                  }
                 else
                      this->imgPkg->img = this->imgPerson[8];
        }

        if ((this->getDirection() == ACT_MV_LEFT) ) {

                  this->movLeft(ForceX);
                  if (!this->getJumping()) {

                      this->tmpLastMov += TIME_RULES;
                      if (lastMov <= 4)  {
                        lastMov = 5;
                        this->imgPkg->img = this->imgPerson[lastMov];
                      }

                      if (this->tmpWalking <= this->tmpLastMov) {
                          this->tmpLastMov = 0;
                          this->lastMov++;

                          if (this->lastMov >= 8)
                              this->lastMov=4;

                          this->imgPkg->img = this->imgPerson[lastMov];
                      }
                  }
                  else {
                      lastMov = 10;
                      this->imgPkg->img = this->imgPerson[lastMov];
                  }
        }
      }
		}
		else {
            if (this->getJumping()) {
                if (this->getDirection() == ACT_MV_LEFT) {
                    lastMov = 10;
                    this->imgPkg->img = this->imgPerson[lastMov];
                }
                else {
                    lastMov = 8;
                    this->imgPkg->img = this->imgPerson[lastMov];
                }
            }
            else {
                if (this->isAttack()) {
                  if (timeAttack < 500)
                    timeAttack += TIME_RULES;
                  else
                    this->attack(false);
                  if (this->getDirection() == ACT_MV_RIGHT)
                    this->imgPkg->img = this->imgPerson[12 + attackFlag];
                  else
                    this->imgPkg->img = this->imgPerson[14 + attackFlag];
                }
                else {
                  this->tmpLastMov = 0;
                  if (this->getDirection() == ACT_MV_LEFT) {
                      lastMov = 4;
                      this->imgPkg->img = this->imgPerson[lastMov];
                  }
                  else {
                      lastMov = 0;
                      this->imgPkg->img = this->imgPerson[lastMov];
                  }
                }
            }
		}

	}

void Person::stop() {
    this->moving = false;

}

void Person::setMov() {
    this->moving = true;
}

