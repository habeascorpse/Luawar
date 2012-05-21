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
#ifndef LUNA_H
#define LUNA_H
/*
#include <lua.hpp>

/**
	@author Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz <habeas_corpse@yahoo.com.br>
*/


/*	this is a Template Class that provide the bind code from C++
		to Lua script access
		To bind code to lua,use this template with your class
		puting static const Luna<youclass>::RegType Register[];
		and: static const char className[];
		to Register class put the follow code:
		const char Person::className[] = "Person";
		const Luna<yourclass>::RegType Person::Register[] = {
		{ "yourclass",&yourclasse::yourfunction},
		... }
*/
/*
template<class T> class Luna {
	public:
		static void Register(lua_State *L) {
			lua_pushcfunction(L, &Luna<T>::constructor);
			lua_setglobal(L, T::className);

			luaL_newmetatable(L, T::className);
			lua_pushstring(L, "__gc");
			lua_pushcfunction(L, &Luna<T>::gc_obj);
			lua_settable(L, -3);
		}

		static int constructor(lua_State *L) {
			T* obj = new T(L);

			lua_newtable(L);
			lua_pushnumber(L, 0);
			T** a = (T**)lua_newuserdata(L, sizeof(T*));
			*a = obj;
			luaL_getmetatable(L, T::className);
			lua_setmetatable(L, -2);
			lua_settable(L, -3); // table[0] = obj;

			for (int i = 0; T::Register[i].name; i++) {
				lua_pushstring(L, T::Register[i].name);
				lua_pushnumber(L, i);
				lua_pushcclosure(L, &Luna<T>::thunk, 1);
				lua_settable(L, -3);
			}
			return 1;
		}

		static int thunk(lua_State *L) {
			int i = (int)lua_tonumber(L, lua_upvalueindex(1));
			lua_pushnumber(L, 0);
			lua_gettable(L, 1);

			T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
			lua_remove(L, -1);
			return ((*obj)->*(T::Register[i].mfunc))(L);
		}

		static int gc_obj(lua_State *L) {
			T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
			delete (*obj);
			return 0;
		}
		struct RegType {
			const char *name;
			int(T::*mfunc)(lua_State*);
		};
};
*/
#endif
