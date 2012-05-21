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
#ifndef DEFS_H
#define DEFS_H


#define LUA50 0

// General Definitions
#define SUCCESS			1
#define ERROR			0

#define KEYBOARD  1
#define JOYSTICK  2
#define TIME_EVENT 20
#define TIME_RENDER 45
#define TIME_RULES  25

#define MAX_INT 32500
#define MIN_INT -32500
#define LIMIT   65200
#define MAX_SPEEDX 8
#define MAX_SPEEDY 25

#define GAME_START 1
#define GAME_WIN   2
#define GAME_OVER  3

// Render Definitions
static const int DF_WIDTH =  640;
static const int DF_HEIGHT = 480;
static const int DF_DEPTH   =32;

// Map Definitions
#define TILE_SIZE 32
static const int CONTINUE  =1;
static const int BREAK     =2;
static const int B_POL_RIGHT =3;
static const int B_POL_LEFT =4;
static const int TILESET_X =8;
static const int TILESET_Y =15;

// Actions and Rules Definitions
#define ACT_JUMP          1
#define ACT_FIRE          2
#define ACT_CHG_WEAPON    3
#define ACT_MV_RIGHT      4
#define ACT_MV_LEFT       5
#define ACT_MV_STOP       6
#define ACT_EXIT          7
#define ACT_MV_STOPX      8
#define ACT_MV_STOPY      9
#define ACT_MV_UP         10
#define ACT_MV_DOWN       11
#define ACT_MOUSECL_LEFT  12
#define ACT_MOUSECL_RIGHT 13
#define ACT_RETURN        17
#define ACT_K1 14
#define ACT_K2 15
#define ACT_K3 16


#endif

