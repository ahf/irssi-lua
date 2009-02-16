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

#ifndef GUARD_LUA_LOADER_H
#define GUARD_LUA_LOADER_H 1

#include <glib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct
{
    char *script_name;
    lua_State *interpreter;
} lua_script_t;

lua_script_t *get_script(const char *script_name);

GList *get_currently_loaded_scripts();

void lua_load_script(const char *script_name);
void lua_unload_script(const char *script_name);

void lua_loader_init();
void lua_loader_deinit();

#endif
