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
#include "tileset.h"


namespace Scenario {

Tileset::Tileset()
{
}


Tileset::~Tileset()
{
}

bool Tileset::loadTileset(string filename) {
	
	ifstream file(filename.c_str());
	if (!file) {
		cout <<"Error on open Tileset"<<endl;
		return ERROR;
	}
	// Este flag � para identificar a ordem que vai pegar as informa��es no arquivo
	// ele deve pegar primeiro o nome da imagem, e depois as propriedades do Tileset
	this->flag = 1;
	this->px = 0;
	this->py = 0;
	
	int response = CONTINUE;
	string buffer;
	while (response == CONTINUE) {
		file >> buffer;
		response = this->procString(buffer);
	}
	
	this->flag = 2;
	this->strcount = 0;

	response = CONTINUE;
	while (!file.eof()) {
		char temp;
		file.get(temp);
		response = this->procString((string ) &temp);
	}
	
	this->fileName = filename;
	
	file.close();
	
	return SUCCESS;
}


bool Tileset::saveTileset(string filename) {
	ofstream file(filename.c_str());
	if (!file) {
		cout <<"Error on open Tileset to save"<<endl;
		return ERROR;
	}
	file << "I=" << this->imgFile <<";"<< endl;
	int i,j;
	
	for (i = 0;i<TILESET_Y;i++) {
		for (j = 0;j<TILESET_X;j++) {
			stringstream temp;
			temp << this->tilePropertie[j][i];
			file << temp.str();
			if ((j + 1) < TILESET_X)
				file << ",";
		}
		file <<";"<<endl;
	}
	
	file.close();
	return SUCCESS;
}

string Tileset::getFileName() {
	return this->fileName;
}

string Tileset::getImgFile() {
	return this->imgFile;
}

bool Tileset::setImgFile(string imgFile) {
	if(imgFile != ""){ 
		this->imgFile = imgFile;
		return SUCCESS;
	}
	else{
		cout <<"Image TileSet can't be null "<<endl;	
		return ERROR;
	}
}

int Tileset::procString(string str) {
	
	if (this->flag == 1) {
		if ((str[0] == 'i') or (str[0] == 'I')) {
			if (str[1] == '=') {
				int i = 2;
				while (str[i] != ';') {
					i++;
				}
				string temp;
				int j = 0;
				while ((j+2) < i) {
					temp += str[j+2];
					j++;
				}
				this->imgFile = temp;
				return BREAK;
			}
		}
	}
	else {
		if ((str[0] !=',') && ( str[0] !='\n') && (str[0] !=';')) {
			this->bf[strcount] = str[0];
			this->strcount++;
			this->bf[strcount] = '\n';
			return CONTINUE;
		}
		if (str[0] ==',') {
			this->tilePropertie[px][py] = atoi(bf);
			this->px++;
			this->bf[0] = '\n';
			this->strcount = 0;
			return CONTINUE;
		}
		if (str[0] ==';') {
			this->tilePropertie[px][py] = atoi(bf);
			this->py++;
			this->px = 0;
			this->bf[0] = '\n';
			this->strcount = 0;
			return CONTINUE;
		}
	}
	return BREAK;
}

int Tileset::matrixToBase8(int x,int y) {
	y = y * 10;
	return y + x;
}

int Tileset::getProperty(int base8) {
	
	div_t temp;
	temp = div(base8,10);

	return this->tilePropertie[temp.rem][temp.quot];
}

void Tileset::setProperty(int x,int y,int value) {
	this->tilePropertie[x][y] = value;
}
	
}
