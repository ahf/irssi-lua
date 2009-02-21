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

#include <lua_debug.h>

#include <glib.h>

void print_stack(lua_State *interpreter)
{
    int i;
    int size = lua_gettop(interpreter);

    for (i = 1; i <= size; i++)
    {
        int type = lua_type(interpreter, i);

        switch (type)
        {
            case LUA_TSTRING:
                g_warning("%i: String: %s", i, lua_tostring(interpreter, i));
                break;

            case LUA_TNUMBER:
                g_warning("%i: Number: %f", i, lua_tonumber(interpreter, i));
                break;

            case LUA_TBOOLEAN:
                g_warning("%i: Bool: %s", i, lua_toboolean(interpreter, i) ? "true" : "false");
                break;

            default:
                g_warning("%i: Typename: %s", i, lua_typename(interpreter, type));
                break;
        }
    }
}
