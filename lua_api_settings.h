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

#ifndef GUARD_LUA_API_SETTINGS_H
#define GUARD_LUA_API_SETTINGS_H 1

#include <lua_api.h>

void lua_api_settings_init();
void lua_api_settings_deinit();

int lua_api_settings_get_str(lua_State *interpreter);
int lua_api_settings_get_int(lua_State *interpreter);
int lua_api_settings_get_bool(lua_State *interpreter);
int lua_api_settings_get_time(lua_State *interpreter);
int lua_api_settings_get_level(lua_State *interpreter);
int lua_api_settings_get_size(lua_State *interpreter);

int lua_api_settings_set_str(lua_State *interpreter);
int lua_api_settings_set_int(lua_State *interpreter);
int lua_api_settings_set_bool(lua_State *interpreter);
int lua_api_settings_set_time(lua_State *interpreter);
int lua_api_settings_set_level(lua_State *interpreter);
int lua_api_settings_set_size(lua_State *interpreter);

int lua_api_settings_add_str(lua_State *interpreter);
int lua_api_settings_add_int(lua_State *interpreter);
int lua_api_settings_add_bool(lua_State *interpreter);
int lua_api_settings_add_time(lua_State *interpreter);
int lua_api_settings_add_level(lua_State *interpreter);
int lua_api_settings_add_size(lua_State *interpreter);

int lua_api_settings_remove(lua_State *interpreter);

#endif
