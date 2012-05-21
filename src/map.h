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
#ifndef SCENARIOMAP_H
#define SCENARIOMAP_H
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <SDL/SDL.h>
#include "defs.h"
#include "tileset.h"
#include <Box2D.h>

using namespace std;

namespace Scenario {
/** @section map_sec Descrição
*	Esta classe é responsável por abrir os arquivos de mapa
*	invocar a abertura dos tilesets definir as propriedades
*       criar o mapeamento das figuras.
*/
/**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>;
                Thiago Luiz Rodrigues <bobboyms@yahoo.com.br>;
*/
class Map{
	public:
		/** @brief
    		* Construtor padrão de Map
     		*/
		Map();
		/** @brief
    		* Destrutor que encerra todas as variáveis e ponteiros de Map
     		*/
		~Map();

		/** @brief
    		* Carrega o Mapa de um arquivo passado por parâmetro
     		*/
		int loadMap(string filename);
		/** @brief
    		* Salva o Mapa em um arquivo passado por parâmetro
     		*/
		int saveMap(string filename);
		/** @brief
    		* Seta o tamanho X do Mapa, e zera todos os atributos
     		*/
		void setX(int x);
		/** @brief
    		* Seta o tamanho Y do Mapa, e zera todos os atributos
     		*/
		void setY(int y);
		/** @brief
    		* Retorna o tamanho X do mapa
     		*/
		int getX();
		/** @brief
    		* Retorna o tamanho Y do mapa
     		*/
		int getY();
		/** @brief
    		* Seta o tamanho X e Y do Mapa, e zera todos os atributos
     		*/
		void setXY(int x,int y);
		/** @brief
    		* Muda o nome do arquivo, mas não salva
     		*/
		void setFileName(string filename);

		void setTilesetName(string filename);

		/** @brief
    		* retorna o nome do arquivo de mapa atual
     		*/
		string getFileName();
		/** @brief
		 * retorna o nome do arquivo de tileset atual
		 */
		string getTilesetName();


		/** @brief
		* Função que pinta uma partícula do mapa, utilizando os parâmetros da posição do mapa
		* e qual o tileset utilizado
		*/
		void drawParticle(int x, int y, int tbase5,SDL_Surface* imgMap,SDL_Surface* imgTile);

		/** @brief
		* Esta variável é a matriz que armazena os dados de propriedade do mapa
		*/
		int** map;

		int getValue(int x, int y);
		/** constroi a matriz atravéz das coordenadas x e y
		*/
		void makeMatrix(int x,int y);
		/** @brief
		* Desenha o Mapa no superfícei passada por parâmetro
		*/
		void drawMap(SDL_Surface* imgMap,SDL_Surface* imgTile);
		/** @brief
		* Objeto do Tileset
		*/
		Tileset* tileset;

		void createBodies(b2World* world);
		int startPointX;
		int startPointY;
	private:


		string fileName;
		string tilesetName;

		int procString(string str);

		unsigned short int X, Y;
		unsigned short int strcount;
		string buffer;
		char bf[5];
		int flag;
		int px,py;

};

}

#endif
