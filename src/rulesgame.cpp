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
#include "rulesgame.h"



namespace Rules
{

	RulesGame::RulesGame(string filePerson,string fileIA,string fileBack1,string fileBack2,string fileFore,string fileObj,Scenario::Map* map,Scenario::Map* map2,CoreObjects* coreObj) {
		L = lua_open();
		#ifdef LUA50
            luaopen_base(L);             /* opens the basic library */
            luaopen_table(L);            /* opens the table library */
            luaopen_io(L);               /* opens the I/O library */
            luaopen_string(L);           /* opens the string lib. */
            luaopen_math(L);             /* opens the math lib. */
        #else
            luaL_openlibs(L);
        #endif



    // Connect LuaBind to this lua state
    luabind::open(L);

    createBind(L);

    core = coreObj;

    core->L = L;
		event = core->event;
		render = core->render;
		sound = core->sound;

		this->pkgLogo = new Render::Package;
		this->pkgLogo->img = Render::Video::LoadBMP("../images/ico.png");
		this->pkgLogo->destRect = new SDL_Rect;
		this->pkgLogo->destRect->x =580;
		this->pkgLogo->destRect->y = 0;
		this->pkgLogo->srcRect = NULL;

		b2AABB worldAABB;
		worldAABB.lowerBound.Set(-100000.0f, -100000.0f);
		worldAABB.upperBound.Set(100000.0f,100000.0f);

		b2Vec2 gravity(0.0f,300.0f);
		bool doSleep = false;

		world = new b2World(worldAABB, gravity, doSleep);
		world->SetContactListener(new ContactListener);
		core->world = world;

		// Map Initialization
		this->mapSrcRect = new SDL_Rect;
		this->mapSrcRect->x = 0;
		this->mapSrcRect->y = 0;
		this->mapSrcRect->w = DF_WIDTH;
		this->mapSrcRect->h = DF_HEIGHT;

		this->mapDestRect = new SDL_Rect;
		this->mapDestRect->x = 0;
		this->mapDestRect->y = 0;
		this->mapDestRect->w = DF_WIDTH;
		this->mapDestRect->h = DF_HEIGHT;

		this->map2SrcRect = new SDL_Rect;
		this->map2SrcRect->x = 0;
		this->map2SrcRect->y = 0;
		this->map2SrcRect->w = DF_WIDTH;
		this->map2SrcRect->h = DF_HEIGHT;

		this->map2DestRect = new SDL_Rect;
		this->map2DestRect->x = 0;
		this->map2DestRect->y = 0;
		this->map2DestRect->w = DF_WIDTH;
		this->map2DestRect->h = DF_HEIGHT;

		this->pkgMap = new Render::Package;
		this->pkgMap2 = new Render::Package;

		SDL_Surface* tempImg;
		tempImg = Render::Video::LoadBMP(map->tileset->getImgFile().c_str());
		this->pkgMap->img = SDL_CreateRGBSurface((SDL_HWSURFACE|SDL_SRCCOLORKEY),map->getX() * TILE_SIZE,map->getY() * TILE_SIZE,DF_DEPTH,0,0,0,0);
		if ((tempImg != NULL) && (this->pkgMap != NULL))
            map->drawMap(this->pkgMap->img,tempImg);


		SDL_FreeSurface(tempImg);

		tempImg = Render::Video::LoadBMP(map2->tileset->getImgFile().c_str());
		this->pkgMap2->img = SDL_CreateRGBSurface((SDL_HWSURFACE|SDL_SRCCOLORKEY),map2->getX() * TILE_SIZE,map2->getY() * TILE_SIZE,DF_DEPTH,0,0,0,0);
		if ((tempImg != NULL) && (this->pkgMap2 != NULL))
			map2->drawMap(this->pkgMap2->img,tempImg);


		SDL_FreeSurface(tempImg);

		this->pkgMap->srcRect = this->mapSrcRect;
		this->pkgMap->destRect = this->mapDestRect;

		this->pkgMap2->srcRect = this->map2SrcRect;
		this->pkgMap2->destRect = this->map2DestRect;

		this->pkgMap->number     = 7;
		this->pkgMap2->number    = 6;
		this->pkgLogo->number    = 700;

		this->lastMov = 0;
		this->tmpLastMov = 0;

		bmanager = new BulletManager(L,"../scripts/bullet1.lua");
		luabind::globals(L)["bullet"] = bmanager;
		bmanager->load();

        //Explosion
		pcache1 = new Render::ParticleCache(L,"../scripts/explosao.lua");
		luabind::globals(L)["pcache"] = pcache1;
		pcache1->load();
		//Blood particle
		bloodCache = new Render::ParticleCache(L,"../scripts/blood.lua");
		luabind::globals(L)["bloodCache"] = bloodCache;
		bloodCache->load();
		//Smoke Particle
		smokeCache = new Render::ParticleCache(L,"../scripts/smoke.lua");
		luabind::globals(L)["smcache"] = smokeCache;
		smokeCache->load();
		//Map Objects
		mapObject = new ObjectManager(this->core,fileObj);
		luabind::globals(L)["mapObject"] = mapObject;
		mapObject->load();

		//Jump Sound
		soundJump = Mix_LoadWAV("../sound/jump.wav");

		refParticle = new Render::RefParticle(sound);

		//Parallax Background
		this->Backgound = new Scenario::BgLayer(fileBack1, 0.5, 0.3,this->mapSrcRect,2);
		this->Background2 = new Scenario::BgLayer(fileBack2, 0, 0,this->mapSrcRect,1);
		this->ForeGround1 = new Scenario::BgLayer(fileFore, 1.4, 1.2,this->mapSrcRect,601);

		render->priority->addPackage(this->Backgound->layer);
		render->priority->addPackage(this->Background2->layer);
		render->priority->addPackage(this->ForeGround1->layer);
		render->priority->addPackage(this->pkgLogo);
		render->priority->addPackage(this->pkgMap2);
		render->priority->addPackage(this->pkgMap);

		this->map = map;
		this->map2 = map2;

		midScreenX = DF_WIDTH / 2;
		midScreenY = DF_HEIGHT / 2;

		luabind::globals(L)["map"] = map;

		map->createBodies(world);

		core->mapSrcRect = this->mapSrcRect;
		// core->render = render;
		core->sound = sound;
		core->map = this->map;
		core->particleCache = pcache1;
		core->refParticle = refParticle;
		core->bloodCache = bloodCache;
		core->smokeCache = smokeCache;
		core->gameState = &gameState;

		// Person
		person = new Person(filePerson.c_str(),core);
		person->createBody(this->map->startPointX,map->startPointY);
		luabind::globals(L)["person"] = person;
		person->imgPkg->number = 11;
		render->priority->addPackage(person->imgPkg);

		aiControl = new AI::AiControl(core,fileIA,person);
		aiControl->load();
		numberBullet = 101;
		core->MusicGame = Mix_LoadMUS("../sound/music.ogg");
		Mix_PlayMusic(core->MusicGame, -1);
		Mix_VolumeMusic(64);

		//Guichan  Life Person
		pkgGui.destRect = NULL;
    pkgGui.number = 1000;
    pkgGui.srcRect = NULL;
    pkgGui.img = Render::Video::CreateSurface(640 ,480,DF_DEPTH);

    SDL_EnableUNICODE(1);
    imageLoader = new gcn::SDLImageLoader();
    gcn::Image::setImageLoader(imageLoader);
    graphics = new gcn::SDLGraphics();
    graphics->setTarget(pkgGui.img);
    input = new gcn::SDLInput();

    font = new gcn::ImageFont("../images/Font/font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?!-+/():;%&`'*#=[]");
    gcn::Widget::setGlobalFont(font);

    gui = new gcn::Gui();
    gui->setGraphics(graphics);
    gui->setInput(input);

    top = new gcn::Container();
    top->setDimension(gcn::Rectangle(0, 0, 120, 25));
    top->setOpaque(false);
    gui->setTop(top);

    //Map
    stringstream temp;
    temp <<"LIFE:"<<person->getLife();
    label = new gcn::Label(temp.str());
    label->setPosition(10, 5);
    label->setSize(120,25);
    top->add(label);
    lastLife = person->getLife();
    gui->draw();
    render->priority->addPackage(&pkgGui);

    gameState = GAME_START;
    luabind::globals(L)["gameState"] = gameState;
	}

	RulesGame::~RulesGame() {

      SDL_FreeSurface(pkgGui.img);

      delete label;
      delete font;
      delete top;
      delete gui;

      delete input;
      delete graphics;
      delete imageLoader;

	    //delete sound;
	    Mix_FreeChunk(soundJump);

	    delete pkgLogo->destRect;
	    delete pkgLogo;
	    delete map2DestRect;
	    delete map2SrcRect;
	    delete mapDestRect;
	    delete mapSrcRect;
	    SDL_FreeSurface(pkgMap->img);
	    SDL_FreeSurface(pkgMap2->img);
	    delete pkgMap;
	    delete pkgMap2;
	    destroyBullet();
	    delete bmanager;
	    delete bloodCache;
	    delete pcache1;
	    delete smokeCache;
	    delete refParticle;
	    delete Backgound;
	    delete Background2;
	    delete ForeGround1;
	    delete person;
	    delete aiControl;
	    delete world;
	    lua_close(L);

	}

	void RulesGame::init() {
		running = true;
		loop();
	}


	void RulesGame::loop() {
		//render->init();
		float32 timeStep = 1.0f / 30.0f;
		int32 velocityIterations = 10;
		int32 positionIterations = 1;
		while (gameState == GAME_START) {
      event->capture();
			this->eventAnalyzer();
			this->bulletAnalyzer();
			core->refParticle->particleAnalyzer();
			person->heroMovement();
      world->Step(timeStep, velocityIterations);
      this->Backgound->refresh();
      this->Background2->refresh();
      this->ForeGround1->refresh();
      aiControl->execAI();
      this->scrolling();
      gui->logic();
      mapObject->update();
      //cout<<"Posição X:"<<person->getPosX()<<"  Posição Y:"<<person->getPosY()<<endl;
      if (lastLife != person->getLife()) {
        lastLife = person->getLife();
        stringstream temp;
        temp <<"LIFE:"<<person->getLife();
        label->setCaption(temp.str());
        pthread_mutex_lock(&render->priority->videoMutex);
        SDL_FillRect( pkgGui.img, NULL, 0 );
        gui->draw();
        pthread_mutex_unlock(&render->priority->videoMutex);
      }
      if (person->getLife() <= 0)
        gameState = GAME_OVER;

			SDL_Delay(TIME_RULES);
		}
		render->priority->removePackage(1);
		render->priority->removePackage(2);
		render->priority->removePackage(6);
		render->priority->removePackage(7);
		render->priority->removePackage(11);
		render->priority->removePackage(601);
		render->priority->removePackage(700);
		render->priority->removePackage(1000);
		delete mapObject;
		if (gameState == GAME_OVER) {

		  Render::Package pkgGameOver;
		  pkgGameOver.destRect = NULL;
		  pkgGameOver.srcRect = NULL;
		  pkgGameOver.number = 700;
		  pkgGameOver.img = Render::Video::LoadBMP("../images/gameover.png");
		  render->priority->addPackage(&pkgGameOver);
		  SDL_Delay(4000);
		  render->priority->removePackage(700);
		  SDL_FreeSurface(pkgGameOver.img);
		}
		if (gameState == GAME_WIN) {

		  Render::Package pkgGameOver;
		  pkgGameOver.destRect = NULL;
		  pkgGameOver.srcRect = NULL;
		  pkgGameOver.number = 700;
		  pkgGameOver.img = Render::Video::LoadBMP("../images/gamewin.png");
		  render->priority->addPackage(&pkgGameOver);
		  SDL_Delay(4000);
		  render->priority->removePackage(700);
		  SDL_FreeSurface(pkgGameOver.img);
		}
	}


	void RulesGame::eventAnalyzer() {

		while (event->action.firstAction() != NULL) {
			if (event->action.firstAction() == ACT_EXIT) {
				this->gameState =GAME_OVER;
				event->action.removeAction();
			}
			if (event->action.firstAction() == ACT_MV_RIGHT) {
					person->setDirection(ACT_MV_RIGHT);
					person->setMov();
					event->action.removeAction();
			}
			if (event->action.firstAction() == ACT_MV_LEFT) {
					person->setDirection(ACT_MV_LEFT);
					person->setMov();
					event->action.removeAction();

			}
			if (event->action.firstAction() == ACT_JUMP) {
          sound->play(soundJump);
					person->jump();
					event->action.removeAction();
			}
			if (event->action.firstAction() == ACT_MV_STOPX) {
					person->stop();
					event->action.removeAction();
			}
			if (event->action.firstAction() == ACT_FIRE) {

              person->attack(true);
              refParticle->addParticle(person->getPosX(),person->getPosY(),core->smokeCache,render,core->mapSrcRect,80);
              //refParticle->addLuaParticle(mapSrcRect,L,"../scripts/faisca.lua",person->getPosX(),person->getPosY(),core->render,99,10,30);
              addBullet(person->getPosX(),person->getPosY(),bmanager->img,bmanager->sound);
              event->action.removeAction();
			}

			if (event->action.firstAction() != 0) {
				event->action.removeAction();
			}
		}

	}

	void RulesGame::scrolling() {

	    if (( person->getPosX() >= midScreenX) && (person->getPosX() <= ((map->getX() * TILE_SIZE) - midScreenX))) {
	        person->imgPkg->destRect->x = midScreenX;
	        this->mapSrcRect->x = person->getPosX() - midScreenX;
	        this->map2SrcRect->x = person->getPosX() - midScreenX;
	    }
      else {
          if ((person->getPosX() + midScreenX) >= (this->map->getX() * TILE_SIZE)) {
              person->imgPkg->destRect->x = (person->getPosX() + (midScreenX * 2)) - (map->getX() * TILE_SIZE);
          }
          else {
              person->imgPkg->destRect->x = person->getPosX();
          }

      }

	    if (( person->getPosY() >= midScreenY) && (person->getPosY() <= ((map->getY() * TILE_SIZE) - midScreenY))) {
        person->imgPkg->destRect->y = midScreenY;

			this->mapSrcRect->y = person->getPosY() - midScreenY;
			this->map2SrcRect->y = person->getPosY() - midScreenY;

		}
		else {
			if ((person->getPosY() + midScreenY) >= ((this->map->getY()) * TILE_SIZE)) {
				person->imgPkg->destRect->y = (person->getPosY() + (midScreenY * 2)) - (map->getY() * TILE_SIZE);
			}
			else {
				person->imgPkg->destRect->y = person->getPosY();
			}

		}

	}

  void RulesGame::bulletAnalyzer() {
	  list<Bullet *>::iterator it;
	  for (it = this->bulletList.begin();it!=this->bulletList.end();it++) {
            if ((*it)->running == 0) {
              Bullet* temp = (*it);
              world->DestroyBody(temp->body);
              delete temp;
              it = bulletList.erase(it);
            }
            else {
              (*it)->refresh();
            }
	  }

	}
  void RulesGame::addBullet(int posX, int posY,SDL_Surface* img,Mix_Chunk* soundMix) {
    numberBullet++;
    if (numberBullet > 400 )
      numberBullet = 101;
    sound->play(soundMix);
    Bullet *bullet1 = new Bullet(posX, posY,mapSrcRect,img,numberBullet,render,world,person->getDirection());
    bulletList.push_back(bullet1);
  }

  void RulesGame::destroyBullet() {
	  list<Bullet *>::iterator it;
	  for (it = this->bulletList.begin();it!=this->bulletList.end();it++) {
	      Bullet* temp = (*it);
          world->DestroyBody(temp->body);
          delete temp;
          it = bulletList.erase(it);
	  }

	}

}
