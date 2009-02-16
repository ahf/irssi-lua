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

#include <lua_api_settings.h>
#include <lua_irssi.h>

int lua_api_settings_get_str(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_str");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushstring(interpreter, settings_get_str(key));

    return LUA_OK;
}

int lua_api_settings_get_int(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_int");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_int(key));

    return LUA_OK;
}

int lua_api_settings_get_bool(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_bool");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushboolean(interpreter, settings_get_bool(key));

    return LUA_OK;
}

int lua_api_settings_get_time(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_time");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_time(key));

    return LUA_OK;
}

int lua_api_settings_get_level(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_level");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_level(key));

    return LUA_OK;
}

int lua_api_settings_get_size(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_size");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_size(key));

    return LUA_OK;
}

int lua_api_settings_set_str(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_str");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    settings_set_str(key, value);

    return LUA_OK;
}

int lua_api_settings_set_int(lua_State *interpreter)
{
    const char *key;
    int value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_int");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tonumber(interpreter, -1);

    settings_set_int(key, value);

    return LUA_OK;
}

int lua_api_settings_set_bool(lua_State *interpreter)
{
    const char *key;
    int value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_bool");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tonumber(interpreter, -1);

    settings_set_bool(key, value);

    return LUA_OK;
}

int lua_api_settings_set_time(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_time");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_time(key, value))
        return LUA_ERROR;

    return LUA_OK;
}

int lua_api_settings_set_level(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_level");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_level(key, value))
        return LUA_ERROR;

    return LUA_OK;
}

int lua_api_settings_set_size(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_size");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_size(key, value))
        return LUA_ERROR;

    return LUA_OK;
}
