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

#include <lua_core.h>
#include <lua_loader.h>
#include <lua_irssi.h>
#include <lua_commands.h>
#include <lua_api.h>

void lua_init() {
    lua_loader_init();
    lua_commands_init();
    lua_api_init();

    module_register(MODULE_NAME, "core");
}

void lua_deinit() {
    lua_loader_deinit();
    lua_commands_deinit();
    lua_api_deinit();
}
