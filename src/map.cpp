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
#include "map.h"


namespace Scenario {

// Constructor of Map
// This constructor create new Tileset only
Map::Map()
{
	this->tileset = new Tileset();

}


// Makematrix create a matrix of numbers integers
// that is used for matrix map and storage the tilesets positions
// values
void Map::makeMatrix(int x,int y) {

	int i,j;
	map = new int*[x];
	for (i=0;i<x;i++) {
		map[i] = new int[y];
	}

	for (i=0;i<x;i++)
		for (j=0;j<y;j++)
			map[i][j] = 0;
}


// Clear all variables
Map::~Map()
{
	int i;
	for (i=0;i<this->X;i++)
		delete []map[i];
	delete []map;

	delete tileset;
}
// this function save the map with the name passed
// for parameters
int Map::saveMap(string filename) {
	// Open file and verify for errors
	ofstream file(filename.c_str());
	if (!file) {
		cout <<"Error on open MapFile to save"<<endl;
		return ERROR;
	}
	// put the properties X Y and T
	// that is Coordinated X and Y and Tileset name
	file << "X=" << this->X <<";"<< endl;
	file << "Y=" << this->Y <<";"<< endl;
	file << "T=" << this->tilesetName <<";"<< endl;
	file << "I=" << this->startPointX <<";"<< endl;
	file << "J=" << this->startPointY <<";"<< endl;
	int i,j;

	// write in file the properties of X and Y
	for (i = 0;i<this->Y;i++) {
		for (j = 0;j<this->X;j++) {
			stringstream temp;
			temp << this->map[j][i];
			file << temp.str();
			if ((j + 1) < this->getX())
				file << ",";
		}
		file <<";"<<endl;
	}

	file.close();
	return SUCCESS;

}

// this function load the map
int Map::loadMap(string filename) {
	// open file in read only mode
	ifstream file(filename.c_str());
	if (!file) {
		cout <<"Error on open MapFile"<<endl;
		return ERROR;
	}
	this->flag = 1;
	// read X and Y
	int response = CONTINUE;
	string buffer2;
	while (response == CONTINUE) {
		file >> buffer2;
		response = this->procString(buffer2);
	}
	makeMatrix(this->X,this->Y);
	this->flag = 2;
	this->px = 0;
	this->py = 0;
	this->strcount = 0;
	// read the positions of map
	response = CONTINUE;
	while (!file.eof()) {
		char temp;
		file.get(temp);
		response = this->procString((string ) &temp);
	}

	this->fileName = filename;


	file.close();

	this->tileset = new Tileset();
	this->tileset->loadTileset(this->tilesetName);

	return SUCCESS;

}


// modify x value and make the matrix
void Map::setX(int x) {
	if ( (x > MAX_INT) || (x < MIN_INT) ) {
		 this->X = 0;
		 cout << "error, the value of x is too large"<<endl;
	}
	else
		this->X = x;
	this->makeMatrix(this->getX(),this->getY());
}
// modify y value and make the matrix
void Map::setY(int y) {
	if ( (y > MAX_INT) || (y < MIN_INT) ) {
		this->Y = 0;
		cout << "error, the value of y is too large"<<endl;
	}
	else
		this->Y = y;
	this->makeMatrix(this->getX(),this->getY());
}

// return X
int Map::getX() {
	return this->X;
}
// return X
int Map::getY() {
	return this->Y;
}
// modify X and Y value and make the matrix
void Map::setXY(int x,int y) {

	if ( (x > MAX_INT) || (x < MIN_INT) ) {
		this->X = 0;
		cout << "error, the value of x is too large"<<endl;
	}
	else
		this->X = x;

	if ( (y > MAX_INT) || (y < MIN_INT) ) {
		this->Y = 0;
		cout << "error, the value of y is too large"<<endl;
	}
	else
		this->Y = y;
	this->makeMatrix(this->getX(),this->getY());
}
// change the filename
void Map::setFileName(string filename) {
	this->fileName = filename;
}
// change the tileset filename
void Map::setTilesetName(string filename) {
	this->tilesetName = filename;
}
// return filename
string Map::getFileName() {
	return this->fileName;
}
// return tileset File name
string Map::getTilesetName() {
	return this->tilesetName;
}

// this function process the strings passed
// via loadMap and Save map Functions
int Map::procString(string str) {

	// flag= 1, take the properties of X, Y and Tileset
	if (this->flag == 1) {
		if ((str[0] == 'x') or (str[0] == 'X')) {
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
				this->setX(atoi(temp.c_str()));
				return CONTINUE;
			}
		}

		if ((str[0] == 'y') || (str[0] == 'Y')) {
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
				this->setY(atoi(temp.c_str()));
				return CONTINUE;
			}
		}
		if ((str[0] == 't') || (str[0] == 'T')) {
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
				this->tilesetName = temp;
				return CONTINUE;
			}
		}
		if ((str[0] == 'i') || (str[0] == 'I')) {
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
				this->startPointX = atoi(temp.c_str());
				return CONTINUE;
			}
		}
		if ((str[0] == 'j') || (str[0] == 'J')) {
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
				this->startPointY = atoi(temp.c_str());
				return BREAK;
			}
		}

	}
	// flag=2 take propertie of map
	else {
		if ((str[0] !=',') && ( str[0] !='\n') && (str[0] !=';')) {
			this->bf[strcount] = str[0];
			this->strcount++;
			this->bf[strcount] = '\n';
			return CONTINUE;
		}
		if (str[0] ==',') {
			this->map[px][py] = atoi(bf);
			this->px++;
			this->bf[0]='\n';
			this->strcount = 0;
			return CONTINUE;
		}
		else {
			if (str[0] ==';') {
				this->map[px][py] = atoi(bf);
				this->py++;
				this->px = 0;
				this->bf[0]='\n';
				this->strcount = 0;
				return CONTINUE;
			}
		}
	}
	return CONTINUE;
}

// Draw map in SDL_Surface passed for parameters
void Map::drawMap(SDL_Surface* imgMap,SDL_Surface* imgTile) {
	int i,j;
	SDL_Rect drect;
	drect.x = 0;
	drect.y = 0;
	drect.w = TILE_SIZE * getX();
	drect.h = TILE_SIZE * getY();
	SDL_FillRect(imgMap,&drect,SDL_MapRGB(imgMap->format,255,0,255));

	for (i=0;i<this->X;i++) {
		for (j=0;j<this->Y;j++) {
            this->drawParticle(i * TILE_SIZE,j * TILE_SIZE,this->map[i][j],imgMap,imgTile);
		}
	}
	SDL_SetColorKey(imgMap,(SDL_SRCCOLORKEY | SDL_RLEACCEL | SDL_HWACCEL),SDL_MapRGB(imgMap->format,255,0,255));
}

// draw a particle of map
void Map::drawParticle(int x, int y, int tbase8,SDL_Surface* imgMap,SDL_Surface* imgTile) {
	SDL_Rect rectMap, rectTile;
	rectMap.x = x;
	rectMap.y = y;
	rectMap.w = TILE_SIZE;
	rectMap.h = TILE_SIZE;

	div_t temp;
	temp = div(tbase8,10);

	rectTile.x = temp.rem * TILE_SIZE;
	rectTile.y = temp.quot * TILE_SIZE;
	rectTile.w = TILE_SIZE;
	rectTile.h = TILE_SIZE;

	SDL_BlitSurface(imgTile,&rectTile,imgMap,&rectMap);
}

void Map::createBodies(b2World* world) {
	int i,j;
	b2Body* groundBody;
  //b2BodyDef* groundBodyDef;


	for (i=0;i<this->X;i++) {
		for (j=0;j<this->Y;j++) {

			if ((this->tileset->getProperty(this->map[i][j]) >= BREAK) && (this->tileset->getProperty(this->map[i][j]) <= B_POL_LEFT)) {

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set((i * TILE_SIZE) + (TILE_SIZE/2) ,(j * TILE_SIZE) + (TILE_SIZE/2));
				b2PolygonDef boxDef;
				groundBody = world->CreateBody(&groundBodyDef);
				if (this->tileset->getProperty(this->map[i][j]) == BREAK)
          boxDef.SetAsBox(TILE_SIZE / 2, TILE_SIZE / 2);
        if (this->tileset->getProperty(this->map[i][j]) == B_POL_RIGHT) {
          boxDef.vertexCount = 3;
          boxDef.vertices[0].Set(TILE_SIZE / 2, TILE_SIZE / 2);
          boxDef.vertices[1].Set(-TILE_SIZE / 2, TILE_SIZE / 2);
          boxDef.vertices[2].Set(-TILE_SIZE / 2,-TILE_SIZE / 2);
        }
        if (this->tileset->getProperty(this->map[i][j]) == B_POL_LEFT) {
          boxDef.vertexCount = 3;
          boxDef.vertices[0].Set(-TILE_SIZE / 2,  TILE_SIZE / 2);
          boxDef.vertices[1].Set(TILE_SIZE / 2, -TILE_SIZE / 2);
          boxDef.vertices[2].Set(TILE_SIZE / 2, TILE_SIZE / 2);
        }
        boxDef.friction = 0.5;
        boxDef.filter.groupIndex = 1;
        boxDef.filter.categoryBits = 0x0004;
        boxDef.filter.maskBits = 0x0004;
        //boxDef.

				groundBody->CreateShape(&boxDef);
				groundBody->SetMassFromShapes();
			}

		}
  }

}
int Map::getValue(int x, int y) {
    return tileset->getProperty(map[x / TILE_SIZE][y / TILE_SIZE]);
}




}
