/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2009 Alexander Færøy <ahf@irssi.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GUARD_LUA_API_H
#define GUARD_LUA_API_H 1

#include <lua_loader.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define LUA_SUCCESS 1
#define LUA_FAILURE 0

void register_lua_api(lua_State *interpreter, const char *script_name);
void wrong_number_of_arguments(const char *function_name);

void lua_api_init();
void lua_api_deinit();

#endif
