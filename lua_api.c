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
#include <lua_api_signals.h>

static const luaL_Reg irssi_lua_functions[] = {
    { "print", lua_api_print },
    { "printtext", lua_api_print },
    { "level2bits", lua_api_level2bits },
    { "bits2level", lua_api_bits2level },
    { "combine_level", lua_api_combine_level },

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

    { "signal_stop", lua_api_signal_stop },
    { "signal_stop_by_name", lua_api_signal_stop_by_name },

    { NULL, NULL }
};

void arity_mismatch(const char *function_name) {
    printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Arity mismatch for function \"%s\"", function_name);
}

void register_lua_api(lua_State *interpreter, const char *script_name) {
    luaL_openlib(interpreter, "Irssi", irssi_lua_functions, 0);

    lua_newtable(interpreter);
    lua_pushstring(interpreter, "script_name");
    lua_pushstring(interpreter, script_name);
    lua_rawset(interpreter, -3);
    lua_setglobal(interpreter, "__irssi_script_information__");

    register_lua_output_api(interpreter);
}

char *get_caller_name(lua_State *interpreter) {
    char *script_name;

    lua_getglobal(interpreter, "__irssi_script_information__");
    lua_pushstring(interpreter, "script_name");
    lua_gettable(interpreter, -2);
    script_name = g_strdup(lua_tostring(interpreter, -1));
    lua_pop(interpreter, 2);

    return script_name;
}

void lua_api_init() {
    lua_api_settings_init();
    lua_api_commands_init();
    lua_api_signals_init();
    lua_api_output_init();
}

void lua_api_deinit()
{
    lua_api_settings_deinit();
    lua_api_commands_deinit();
    lua_api_signals_deinit();
    lua_api_output_deinit();
}
