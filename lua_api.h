/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef GUARD_LUA_API_H
#define GUARD_LUA_API_H 1

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void register_lua_api(lua_State *interpreter);

#endif
