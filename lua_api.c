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

#include <lua_api.h>
#include <lua_irssi.h>
#include <lua_loader.h>

#include <lua_api_settings.h>
#include <lua_api_output.h>
#include <lua_api_commands.h>

void wrong_number_of_arguments(const char *function_name)
{
    printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Wrong number of arguments for function \"%s\"", function_name);
}

static const luaL_Reg irssi_lua_functions[] = {
    { "print", lua_api_print },

    { "settings_get_str", lua_api_settings_get_str },
    { "settings_get_int", lua_api_settings_get_int },
    { "settings_get_bool", lua_api_settings_get_bool },
    { "settings_get_time", lua_api_settings_get_time },
    { "settings_get_level", lua_api_settings_get_level },
    { "settings_get_size", lua_api_settings_get_size },

    { "settings_set_str", lua_api_settings_set_str },
    { "settings_set_int", lua_api_settings_set_int },
    { "settings_set_bool", lua_api_settings_set_bool },
    { "settings_set_time", lua_api_settings_set_time },
    { "settings_set_level", lua_api_settings_set_level },
    { "settings_set_size", lua_api_settings_set_size },

    { "settings_add_str", lua_api_settings_add_str },
    { "settings_add_int", lua_api_settings_add_int },
    { "settings_add_bool", lua_api_settings_add_bool },
    { "settings_add_time", lua_api_settings_add_time },
    { "settings_add_level", lua_api_settings_add_level },
    { "settings_add_size", lua_api_settings_add_size },

    { "settings_remove", lua_api_settings_remove },

    { NULL, NULL }
};

void register_lua_api(lua_State *interpreter, const char *script_name)
{
    luaL_openlib(interpreter, "Irssi", irssi_lua_functions, 0);

    lua_newtable(interpreter);
    lua_pushstring(interpreter, "script_name");
    lua_pushstring(interpreter, script_name);
    lua_rawset(interpreter, -3);
    lua_setglobal(interpreter, "__irssi_script_information__");
}

const char *get_caller_name(lua_State *interpreter)
{
    const char *script_name;

    lua_getglobal(interpreter, "__irssi_script_information__");
    lua_pushstring(interpreter, "script_name");
    lua_gettable(interpreter, -2);
    script_name = lua_tostring(interpreter, -1);

    g_warning("Script name: %s", script_name);

    return script_name;
}

void lua_api_init()
{
    lua_api_settings_init();
    lua_api_commands_init();
}

void lua_api_deinit()
{
    lua_api_settings_deinit();
    lua_api_commands_deinit();
}
