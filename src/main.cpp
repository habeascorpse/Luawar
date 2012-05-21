/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva,                         *
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

/**
 * @mainpage Lua
 *
 * @image html logo.gif
 *
 * @section intro_sec Introdução
 *
 * Este é a documentação do Game Lua, O qual foi desenvolvido
 * utilizando C++ juntamente com Lua, utilizando somente ferramentas
 * livres, e podendo ser alterado e comercializado desde que aceite
 * a licensa prevista no projeto.
 *
 * @section hist_sec Histórico
 *
 * Lua game se encontra na versão 0.1 em fase de desenvolvimento
 * o qual tem sido criado para desenvolvimento de Trabalho de Conclusão
 * de Curso de Sistemas de Informação na UNIOURO - Ouro Preto do Oeste
 * ainda em 2009 para ser apresentado no final deste ano;
 *
 * @section tools Ferramentas Utilizadas
 *
 * Este projeto faz uma integração de duas linguagens
 * de programação que são:
 *     C++ - Para o motor do jogo;
 *     Lua - Para os scripts de configuração, extensão e controle
 *
 * Para a Documentação usamos o Doxygen.
 * SDL para recursos de Vídeos e Eventos.
 *
 * @section autors_sec Autores
 *
 * Alan de Oliveira Silva - habeas_corpse@yahoo.com.br
 * Gabriel Vedana Queiroz - gabielvq@hotmail.com
 *
 */



#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "video.h"
#include "videorender.h"
#include "editor.h"
#include "rulesgame.h"
#include "tileset.h"
#include "tileseteditor.h"
#include "button.h"
#include <guichan.hpp>
#include <guichan/sdl.hpp>

string fileMap;
string fileMap1;
string fileMap2;
string filePerson;
string fileIA;
string fileBack1;
string fileBack2;
string fileFore;
string fileObj;
string fileImg;
string fileTileset;
int sizeX;
int sizeY;

void guiGame(CoreObjects *core) {
  gcn::SDLInput* input;
  gcn::SDLGraphics* graphics;
  gcn::SDLImageLoader* imageLoader;

  gcn::Gui* gui;
  gcn::Container* top;
  gcn::ImageFont* font;
  gcn::Label* lbMap1;
  gcn::TextBox* map1Box;
  gcn::Label* lbMap2;
  gcn::TextBox* map2Box;
  gcn::Label* lbPerson;
  gcn::TextBox* personBox;
  gcn::Label* lbObj;
  gcn::TextBox* objBox;
  gcn::Label* lbIA;
  gcn::TextBox* iaBox;
  gcn::Label* lbBack1;
  gcn::TextBox* back1Box;
  gcn::Label* lbBack2;
  gcn::TextBox* back2Box;
  gcn::Label* lbFore;
  gcn::TextBox* foreBox;
  Button* button;

  Render::Package pkgGui;
  pkgGui.destRect = NULL;
  pkgGui.number = 1;
  pkgGui.srcRect = NULL;
  pkgGui.img = Render::Video::CreateSurface(640,480,DF_DEPTH);

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
  top->setDimension(gcn::Rectangle(0, 0, 640, 480));
  gui->setTop(top);

  //Map
  lbMap1 = new gcn::Label("Caminho do Mapa:");
  map1Box = new gcn::TextBox("../maps/mapa1.map");
  lbMap1->setPosition(10, 20);
  map1Box->setPosition(200, 20);
  //Tileset
  lbMap2 = new gcn::Label("Caminho do Mapa 2:");
  map2Box = new gcn::TextBox("../maps/mapa2.map");
  lbMap2->setPosition(10, 40);
  map2Box->setPosition(200, 40);
  // size X
  lbPerson = new gcn::Label("Personagem Principal:");
  personBox = new gcn::TextBox("../scripts/alan.lua");
  lbPerson->setPosition(10, 60);
  personBox->setPosition(200, 60);

  lbObj = new gcn::Label("Arquivo de Objetos:");
  objBox = new gcn::TextBox("../scripts/map1object.lua");
  lbObj->setPosition(10, 80);
  objBox->setPosition(200, 80);
  // size Y
  lbIA = new gcn::Label("Caminho da IA:");
  iaBox = new gcn::TextBox("../scripts/mapa1.lua");
  lbIA->setPosition(10, 100);
  iaBox->setPosition(200, 100);

  lbBack1 = new gcn::Label("Caminho do Backdround:");
  back1Box = new gcn::TextBox("../images/arvores.png");
  lbBack1->setPosition(10, 120);
  back1Box->setPosition(200, 120);

  lbBack2 = new gcn::Label("Caminho do Backdround 2:");
  back2Box = new gcn::TextBox("../images/cloud.png");
  lbBack2->setPosition(10, 140);
  back2Box->setPosition(200, 140);

  lbFore = new gcn::Label("Caminho do Foreground:");
  foreBox = new gcn::TextBox("../images/fg.png");
  lbFore->setPosition(10, 160);
  foreBox->setPosition(200, 160);


  button = new Button("OK");
  button->setPosition(40, 180);

  top->add(lbMap1);
  top->add(lbMap2);
  top->add(lbBack1);
  top->add(lbBack2);
  top->add(lbFore);
  top->add(lbIA);
  top->add(lbObj);
  top->add(lbPerson);

  top->add(map1Box);
  top->add(map2Box);
  top->add(back1Box);
  top->add(back2Box);
  top->add(foreBox);
  top->add(iaBox);
  top->add(objBox);
  top->add(personBox);

  top->add(button);
  core->render->priority->addPackage(&pkgGui);

  //Loop
  bool running = true;

    while (!button->click) {
        while(SDL_PollEvent(&core->event->event))
        {
           input->pushInput(core->event->event);
        }

       gui->logic();
       pthread_mutex_lock(&core->render->priority->videoMutex);
       gui->draw();
       pthread_mutex_unlock(&core->render->priority->videoMutex);
       SDL_Delay(50);
    }
    core->render->priority->removePackage(pkgGui.number);
    SDL_FreeSurface(pkgGui.img);

    delete lbBack1;
    delete lbMap1;
    delete lbMap2;
    delete lbBack2;
    delete lbFore;
    delete lbIA;
    delete lbObj;
    delete lbPerson;

    fileMap1 = map1Box->getText();
    fileMap2 = map2Box->getText();
    fileBack1 = back1Box->getText();
    fileBack2 = back2Box->getText();
    fileFore = foreBox->getText();
    fileIA =  iaBox->getText();
    filePerson = personBox->getText();
    fileObj = objBox->getText();

    delete map1Box;
    delete map2Box;
    delete back1Box;
    delete back2Box;
    delete foreBox;
    delete iaBox;
    delete personBox;
    delete objBox;


    delete font;
    delete top;
    delete gui;
    delete button;

    delete input;
    delete graphics;
    delete imageLoader;
}


void guiTeditor(CoreObjects *core) {
  gcn::SDLInput* input;
  gcn::SDLGraphics* graphics;
  gcn::SDLImageLoader* imageLoader;

  gcn::Gui* gui;
  gcn::Container* top;
  gcn::ImageFont* font;
  gcn::Label* label;
  gcn::TextBox* mapBox;
  gcn::Label* lbTileset;
  gcn::TextBox* tileBox;
  Button* button;

  Render::Package pkgGui;
  pkgGui.destRect = NULL;
  pkgGui.number = 1;
  pkgGui.srcRect = NULL;
  pkgGui.img = Render::Video::CreateSurface(640,480,DF_DEPTH);

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
  top->setDimension(gcn::Rectangle(0, 0, 640, 480));
  gui->setTop(top);

  //Map
  label = new gcn::Label("Caminho da Imagem:");
  mapBox = new gcn::TextBox("../images/tilesets/tileset1.png");
  label->setPosition(10, 20);
  mapBox->setPosition(200, 20);
  //Tileset
  lbTileset = new gcn::Label("Caminho do Tileset:");
  tileBox = new gcn::TextBox("../tilesets/tset1.tst");
  lbTileset->setPosition(10, 40);
  tileBox->setPosition(200, 40);

  button = new Button("OK");
  button->setPosition(40, 60);

  top->add(label);
  top->add(mapBox);
  top->add(lbTileset);
  top->add(tileBox);
  top->add(button);
  core->render->priority->addPackage(&pkgGui);

  //Loop
  bool running = true;

    while (!button->click) {
        while(SDL_PollEvent(&core->event->event))
        {
           input->pushInput(core->event->event);
        }

       gui->logic();
       pthread_mutex_lock(&core->render->priority->videoMutex);
       gui->draw();
       pthread_mutex_unlock(&core->render->priority->videoMutex);
       SDL_Delay(50);
    }
    core->render->priority->removePackage(pkgGui.number);

    delete label;
    delete font;
    delete top;
    delete gui;
    fileImg = mapBox->getText();
    delete mapBox;
    delete lbTileset;
    fileTileset = tileBox->getText();
    delete tileBox;
    delete button;

    delete input;
    delete graphics;
    delete imageLoader;

}

void guiEditor(CoreObjects *core) {
  gcn::SDLInput* input;
  gcn::SDLGraphics* graphics;
  gcn::SDLImageLoader* imageLoader;

  gcn::Gui* gui;
  gcn::Container* top;
  gcn::ImageFont* font;
  gcn::Label* label;
  gcn::TextBox* mapBox;
  gcn::Label* lbTileset;
  gcn::TextBox* tileBox;
  gcn::Label* lbX;
  gcn::TextBox* xBox;
  gcn::Label* lbY;
  gcn::TextBox* yBox;
  Button* button;

  Render::Package pkgGui;
  pkgGui.destRect = NULL;
  pkgGui.number = 1;
  pkgGui.srcRect = NULL;
  pkgGui.img = Render::Video::CreateSurface(640,480,DF_DEPTH);

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
  top->setDimension(gcn::Rectangle(0, 0, 640, 480));
  gui->setTop(top);

  //Map
  label = new gcn::Label("Caminho do Mapa:");
  mapBox = new gcn::TextBox("../maps/mapa1.map");
  label->setPosition(10, 20);
  mapBox->setPosition(200, 20);
  //Tileset
  lbTileset = new gcn::Label("Caminho do Tileset:");
  tileBox = new gcn::TextBox("../tilesets/tset1.tst");
  lbTileset->setPosition(10, 40);
  tileBox->setPosition(200, 40);
  // size X
  lbX = new gcn::Label("Tamanho X do mapa:");
  xBox = new gcn::TextBox("50");
  lbX->setPosition(10, 60);
  xBox->setPosition(400, 60);
  // size Y
  lbY = new gcn::Label("Tamanho Y do mapa");
  yBox = new gcn::TextBox("30");
  lbY->setPosition(10, 80);
  yBox->setPosition(400, 80);

  button = new Button("OK");
  button->setPosition(40, 100);

  top->add(label);
  top->add(mapBox);
  top->add(lbTileset);
  top->add(tileBox);
  top->add(lbX);
  top->add(xBox);
  top->add(lbY);
  top->add(yBox);
  top->add(button);
  core->render->priority->addPackage(&pkgGui);

  //Loop
  bool running = true;

    while (!button->click) {
        while(SDL_PollEvent(&core->event->event))
        {
           input->pushInput(core->event->event);
        }

       gui->logic();
       pthread_mutex_lock(&core->render->priority->videoMutex);
       gui->draw();
       pthread_mutex_unlock(&core->render->priority->videoMutex);
       SDL_Delay(50);
    }
    core->render->priority->removePackage(pkgGui.number);
    SDL_FreeSurface(pkgGui.img);

    delete label;
    delete font;
    delete top;
    delete gui;
    fileMap = mapBox->getText();
    delete mapBox;
    delete lbTileset;
    fileTileset = tileBox->getText();
    delete tileBox;
    delete lbX;
    sizeX = atoi(xBox->getText().c_str());
    delete xBox;
    delete lbY;
    sizeY = atoi(yBox->getText().c_str());
    delete yBox;
    delete button;

    delete input;
    delete graphics;
    delete imageLoader;
}


void menu() {
  Sound snd;
  Mix_Music* mus = Mix_LoadMUS("../sound/menu.ogg");
  Mix_PlayMusic(mus, -1);
  Render::VideoRender render;
  Render::Package pkgImgTitle;
  pkgImgTitle.img = Render::Video::LoadBMP("../images/pretitle.png");
  pkgImgTitle.number = 1;
  pkgImgTitle.srcRect = NULL;
  pkgImgTitle.destRect = NULL;
  render.priority->addPackage(&pkgImgTitle);
  render.init();
  Events::Event *event = new Events::Event(KEYBOARD);
  int cancel = false;
  while ( cancel ==false) {
    event->capture();
    if (event->action.firstAction() == ACT_EXIT) {
      cancel = true;
      event->action.removeAction();
    }

    else {
      if (event->action.firstAction() != 0) {
				event->action.removeAction();
			}
    }
    SDL_Delay(50);
  }
  render.priority->removePackage(1);
  SDL_FreeSurface(pkgImgTitle.img);
  pkgImgTitle.img = Render::Video::LoadBMP("../images/menu.png");
  cancel = false;
  SDL_Delay(1000);
  render.priority->addPackage(&pkgImgTitle);
  Render::Package pkgBar;
  pkgBar.img = Render::Video::LoadBMP("../images/bar.png");
  pkgBar.number = 2;
  pkgBar.destRect = new SDL_Rect;
  pkgBar.destRect->y = 185;
  pkgBar.destRect->x = 15;
  pkgBar.srcRect = NULL;
  render.priority->addPackage(&pkgBar);
  CoreObjects core;
  core.render = &render;
  core.event = event;
  core.sound = &snd;
  int esc = 1;
  while ( cancel ==false) {
    event->capture();
    if (event->action.firstAction() == ACT_EXIT) {
      cancel = true;
      event->action.removeAction();
    }
    if ((event->action.firstAction() == ACT_MV_DOWN)) {
      if (esc<5) {
        esc++;
        pkgBar.destRect->y += 23;
      }
      event->action.removeAction();
    }
    if ((event->action.firstAction() == ACT_MV_UP)) {
      if (esc>1) {
        esc--;
        pkgBar.destRect->y -= 23;
      }
      event->action.removeAction();
    }
    if ((event->action.firstAction() == ACT_RETURN) || (event->action.firstAction() == ACT_FIRE)) {
      if (esc == 1) {
          event->action.removeAction();
          Mix_HaltMusic();
          Mix_FreeMusic(mus);
          mus = NULL;
        render.priority->removePackage(1);
        render.priority->removePackage(2);

        guiGame(&core);
        Scenario::Map *map = new Scenario::Map();
        map->loadMap(fileMap1);
        Scenario::Map *map2 = new Scenario::Map();
        map2->loadMap(fileMap2);

        Rules::RulesGame *rules = new Rules::RulesGame(filePerson,fileIA,fileBack1,fileBack2,fileFore,fileObj,map,map2,&core);
        rules->init();

        delete rules;
        esc = 1;
        pkgBar.destRect->y = 185;
        pkgBar.destRect->x = 15;
        pkgImgTitle.img = Render::Video::LoadBMP("../images/menu.png");
        render.priority->addPackage(&pkgImgTitle);
        render.priority->addPackage(&pkgBar);
      }
      if (esc == 2) {
          event->action.removeAction();
          render.priority->removePackage(1);
          pkgImgTitle.img = Render::Video::LoadBMP("../images/menu2.png");
          render.priority->addPackage(&pkgImgTitle);
          int esc2 = 1;
          bool cancel2 = false;
          while ( cancel2 ==false) {
            event->capture();
            if (event->action.firstAction() == ACT_EXIT) {
              cancel2 = true;
              event->action.removeAction();
            }
            if ((event->action.firstAction() == ACT_MV_DOWN)) {
              if (esc2<2) {
                esc2++;
                pkgBar.destRect->y += 50;
              }
              event->action.removeAction();
            }
            if ((event->action.firstAction() == ACT_MV_UP)) {
              if (esc2>1) {
                esc2--;
                pkgBar.destRect->y -= 50;
              }
              event->action.removeAction();
            }
            if ((event->action.firstAction() == ACT_RETURN) || (event->action.firstAction() == ACT_FIRE)) {
              if (esc2 == 1) {
                  // Teclado
                  delete event;
                  event = new Events::Event(JOYSTICK);
                  cancel2 = true;
              }
              if (esc2 == 2) {
                  //joystick
                  delete event;
                  event = new Events::Event(KEYBOARD);
                  cancel2 = true;

              }
              esc = 1;
              pkgBar.destRect->y = 185;
                pkgBar.destRect->x = 15;
                render.priority->removePackage(1);
                pkgImgTitle.img = Render::Video::LoadBMP("../images/menu.png");
                render.priority->addPackage(&pkgImgTitle);
            }
            if (event->action.firstAction() != 0) {
              event->action.removeAction();
            }
            SDL_Delay(30);
          }
      }
      if (esc == 3) {
          event->action.removeAction();
          Mix_HaltMusic();
          Mix_FreeMusic(mus);
          mus = NULL;
        render.priority->removePackage(1);
        render.priority->removePackage(2);
        guiEditor(&core);

        Editor *editor = new Editor(sizeX,sizeY, fileMap,fileTileset,&core);
        editor->loop();
        delete editor;

        esc = 1;
        pkgBar.destRect->y = 185;
        pkgBar.destRect->x = 15;
        pkgImgTitle.img = Render::Video::LoadBMP("../images/menu.png");
        render.priority->addPackage(&pkgImgTitle);
        render.priority->addPackage(&pkgBar);
      }
      if (esc == 4) {
          event->action.removeAction();
          Mix_HaltMusic();
          Mix_FreeMusic(mus);
          mus = NULL;
          render.priority->removePackage(1);
          render.priority->removePackage(2);
          guiTeditor(&core);

          Editors::TileSetEditor teditor(fileTileset,fileImg,&core);
          teditor.loop();

          esc = 1;
          pkgBar.destRect->y = 185;
          pkgBar.destRect->x = 15;
          pkgImgTitle.img = Render::Video::LoadBMP("../images/menu.png");
          render.priority->addPackage(&pkgImgTitle);
          render.priority->addPackage(&pkgBar);
      }
    }
    if (event->action.firstAction() != 0) {
      event->action.removeAction();
    }
  }
  delete event;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    menu();

    SDL_Quit();

    return 0;
}
