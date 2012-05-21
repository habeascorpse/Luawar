#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "videorender.h"

class Menu {

    public:
        Menu();

        void init() {/*
            Scenario::Map *map = new Scenario::Map();
            map->loadMap("../maps/mapa1.map");
            Scenario::Map *map2 = new Scenario::Map();
            map2->loadMap("../maps/mapa2.map");

            Rules::RulesGame *rules = new Rules::RulesGame(map,map2);
            rules->init();*/


        }

        ~Menu();
    private:
        Render::VideoRender* render;

};



#endif // MENU_H_INCLUDED
