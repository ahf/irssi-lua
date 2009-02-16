/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef GUARD_LUA_API_H
#define GUARD_LUA_API_H 1

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define LUA_OK 1
#define LUA_ERROR 0

void register_lua_api(lua_State *interpreter);
void wrong_number_of_arguments(const char *function_name);

#endif
