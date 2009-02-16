/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef GUARD_LUA_API_SETTINGS_H
#define GUARD_LUA_API_SETTINGS_H 1

#include <lua_api.h>

int lua_api_settings_get_str(lua_State *interpreter);
int lua_api_settings_get_int(lua_State *interpreter);
int lua_api_settings_get_bool(lua_State *interpreter);
int lua_api_settings_get_time(lua_State *interpreter);
int lua_api_settings_get_level(lua_State *interpreter);
int lua_api_settings_get_size(lua_State *interpreter);

#endif
