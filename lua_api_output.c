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

#include <lua_api_output.h>
#include <lua_irssi.h>

#define ADD_KV_PAIR(interpreter, key, value) \
    lua_pushstring(interpreter, key); \
    lua_pushnumber(interpreter, value); \
    lua_rawset(interpreter, -3);

int lua_api_print(lua_State *interpreter)
{
    const char *message;
    int n;
    int msglevel;

    n = lua_gettop(interpreter);

    if (2 < n || 0 >= n)
    {
        wrong_number_of_arguments("print");
        return LUA_FAILURE;
    }

    if (2 != n)
    {
        msglevel = MSGLEVEL_CLIENTCRAP;
        message = lua_tostring(interpreter, -1);
    }
    else
    {
        msglevel = lua_tonumber(interpreter, -1);
        message = lua_tostring(interpreter, -2);
    }

    printtext(NULL, NULL, msglevel, "%s", message);

    return LUA_SUCCESS;
}

void register_lua_output_api(lua_State *interpreter)
{
    lua_newtable(interpreter);

    ADD_KV_PAIR(interpreter, "crap", MSGLEVEL_CRAP);
    ADD_KV_PAIR(interpreter, "msgs", MSGLEVEL_MSGS);
    ADD_KV_PAIR(interpreter, "public", MSGLEVEL_PUBLIC);
    ADD_KV_PAIR(interpreter, "notices", MSGLEVEL_NOTICES);
    ADD_KV_PAIR(interpreter, "snotes", MSGLEVEL_SNOTES);
    ADD_KV_PAIR(interpreter, "ctcps", MSGLEVEL_CTCPS);
    ADD_KV_PAIR(interpreter, "actions", MSGLEVEL_ACTIONS);
    ADD_KV_PAIR(interpreter, "joins", MSGLEVEL_JOINS);
    ADD_KV_PAIR(interpreter, "parts", MSGLEVEL_PARTS);
    ADD_KV_PAIR(interpreter, "quits", MSGLEVEL_QUITS);
    ADD_KV_PAIR(interpreter, "kicks", MSGLEVEL_KICKS);
    ADD_KV_PAIR(interpreter, "modes", MSGLEVEL_MODES);
    ADD_KV_PAIR(interpreter, "topics", MSGLEVEL_TOPICS);
    ADD_KV_PAIR(interpreter, "wallops", MSGLEVEL_WALLOPS);
    ADD_KV_PAIR(interpreter, "invites", MSGLEVEL_INVITES);
    ADD_KV_PAIR(interpreter, "nicks", MSGLEVEL_NICKS);
    ADD_KV_PAIR(interpreter, "dcc", MSGLEVEL_DCC);
    ADD_KV_PAIR(interpreter, "dccmsgs", MSGLEVEL_DCCMSGS);
    ADD_KV_PAIR(interpreter, "clientnotice", MSGLEVEL_CLIENTNOTICE);
    ADD_KV_PAIR(interpreter, "clientcrap", MSGLEVEL_CLIENTCRAP);
    ADD_KV_PAIR(interpreter, "clienterror", MSGLEVEL_CLIENTERROR);
    ADD_KV_PAIR(interpreter, "hilight", MSGLEVEL_HILIGHT);
    ADD_KV_PAIR(interpreter, "all", MSGLEVEL_ALL);
    ADD_KV_PAIR(interpreter, "nohilight", MSGLEVEL_NOHILIGHT);
    ADD_KV_PAIR(interpreter, "no_act", MSGLEVEL_NO_ACT);
    ADD_KV_PAIR(interpreter, "never", MSGLEVEL_NEVER);
    ADD_KV_PAIR(interpreter, "lastlog", MSGLEVEL_LASTLOG);

    lua_setglobal(interpreter, "msglevel");
}

void lua_api_output_init()
{
}

void lua_api_output_deinit()
{
}
