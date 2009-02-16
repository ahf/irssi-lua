/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef GUARD_LUA_LOADER_H
#define GUARD_LUA_LOADER_H 1

#include <glib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

gboolean script_loaded(const char *script_name);

GHashTable *get_currently_loaded_scripts();

void lua_load_script(const char *script_name);
void lua_unload_script(const char *script_name);

void lua_loader_init();
void lua_loader_deinit();

#endif
