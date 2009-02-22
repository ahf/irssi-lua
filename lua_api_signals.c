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

#include <lua_api_signals.h>
#include <lua_irssi.h>

int lua_api_signal_stop(lua_State *interpreter)
{
    if (0 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("signal_stop");
        return LUA_FAILURE;
    }

    signal_stop();

    return LUA_SUCCESS;
}

void lua_api_signalss_init()
{
}

void lua_api_signalss_deinit()
{
}
