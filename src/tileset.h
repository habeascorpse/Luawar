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
#ifndef SCENARIOTILESET_H
#define SCENARIOTILESET_H
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <SDL/SDL.h>
#include "defs.h"

using namespace std;

namespace Scenario {

/** @section tileset_sec Descrição
*	Esta classe Tileset prove as funcionalidades de que a Classe Map
*	necessita para carregar os respectivos tilesets
*/
/**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>; 
                Thiago Luiz Rodrigues <bobboyms@yahoo.com.br>; 
*/

class Tileset{
	public:
		/** @brief
    		* Construtor padrão de Tileset
     		*/
		Tileset();
		/** @brief
    		* Destrutor padrão de Tileset, que elimina
		* todos os ponteiros
     		*/
		~Tileset();
		/** @brief
    		* Função que carrega todos as propriedades do tile site
		* de um arquivo passado por parâmetro, e retorna true se
		* ocorreu com sucesso e false se ocorreu algum problema
     		*/
		bool loadTileset(string filename);
		/** @brief
    		* Função que salva todos as propriedades do tile site
		* em um arquivo passado por parâmetro, e retorna true se
		* ocorreu com sucesso e false se ocorreu algum problema
     		*/
		bool saveTileset(string filename);
		/** @brief
    		* Retorna o nome do arquivo de Tileset
     		*/
		string getFileName();
		/** @brief
    		* Inseri a variável de imagem do Tileset
     		*/
		bool setImgFile(string imgFile);
		/** @brief
    		* Retorna a variável de imagem do Tileset
     		*/
		string getImgFile();
		/** @brief
		 * Retorna a variável de imagem do Tileset
		 */
		//SDL_Surface* img;
		
		/** @brief
		*		Retorna no formato de base 5 a partir de uma matriz
		*/
		static int matrixToBase8(int x,int y);
		
		/** @brief
		*		Retorna o valor do tile
		*/
		int getProperty(int base8);

		/** @brief
		*		Seta o valor do Tileset
		*/
		void setProperty(int x,int y,int value);
	private:
		
		int procString(string str);
		
		unsigned short int strcount;
		string buffer;
		char bf[5];
		string fileName;
		string imgFile;
		int tilePropertie[8][15];
		int flag;
		int px,py;
};

}

#endif
