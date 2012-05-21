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

#ifndef RENDERVIDEO_H
#define RENDERVIDEO_H
//heading for IO
#include <iostream>
//heading for SDL
#include <SDL/SDL.h>
#include <SDL_image.h>
//heading for for definitionfor file
#include "defs.h"

using namespace std;
namespace Render {
/**
	@author Alan de Oliveira Silva <habeas_corpse@yahoo.com.br>;
		Gabriel Vedana Queiroz <gabielvq@hotmail.com>;
*/

class Video{
	public:
		/** @brief
		*  Construtor da Classe Vídeo, que por padrão abrirá com as configurações
		    Definido no defs.h
		*/
		Video();
		/** @brief
     		*Construtor da Classe Vídeo, que é criado a partir dos parâmetros
		* de dimensões e quantidade de cores
		*/
		Video(int width,int height,int depth);
		/** @brief
    		*  Retorna o tamanho X da tela
     		*/
		int getWidht();
		/** @brief
    		*  Retorna o tamanho Y da tela
     		*/
		int getHeight();
		/** @brief
    		*  Retorna a quantidade de cores da tela
     		*/
		int getDepth();
		/** @brief
    		*  Muda o tamanho da tela e a quantidade de cores
     		*/
		int setScreen(int widht,int height, int depth);
		/** @brief
    		*  Variável que é a tela no formato de SDL_Surface*
     		*/
		SDL_Surface* screen;
		/** @brief
    		*  Destrutor padrão de Video
     		*/
		virtual ~Video();
		/** @brief
		* Esta funcão carrega a imagem e retira a cor magenta, deixando ela transparente.
		 Ela deve ser usado para carregar todas as imagens. */

		static SDL_Surface* LoadBMP(const char* file);
    static SDL_Surface* CreateSurface(int x,int y,int depth);
	private:
		/** @brief
    		*  Tamanho X da Tela
     		*/
		int Width;
		/** @brief
    		*  Tamanho Y da Tela
     		*/
		int Height;
		/** @brief
    		*  Quantidade de cores
     		*/
		int Depth;


};

}

#endif
