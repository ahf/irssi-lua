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

#include <lua_loader.h>
#include <lua_irssi.h>
#include <lua_api.h>

static GHashTable *lua_scripts = NULL;

static void free_lua_script_hash_table_entry(gpointer key, gpointer interpreter, gpointer user_data) {
    g_free(key);
    lua_close(interpreter);
}

GHashTable *get_currently_loaded_scripts() {
    return lua_scripts;
}

lua_State *get_script(const char *script_name) {
    return g_hash_table_lookup(lua_scripts, script_name);
}

void lua_load_script(const char *script_name) {
    struct stat stat_buf;
    lua_State *interpreter;
    char *script;

    if (NULL != get_script(script_name)) {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Script \"%s\" already loaded.", script_name);
        return;
    }

    if (0 != stat(script_name, &stat_buf)) {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Script \"%s\" not found.", script_name);
        return;
    }

    interpreter = luaL_newstate();

    if (NULL == interpreter) {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Unable to create lua interpreter");
        return;
    }

    luaL_openlibs(interpreter);
    script = g_strdup(script_name);
    register_lua_api(interpreter, script);

    if (0 != luaL_loadfile(interpreter, script_name)) {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Unable to load script: %s", lua_tostring(interpreter, -1));
        lua_close(interpreter);
        g_free(script);
        return;
    }

    if (0 != lua_pcall(interpreter, 0, 0, 0)) {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Unable to execute the script: %s", lua_tostring(interpreter, -1));
        lua_close(interpreter);
        g_free(script);
        return;
    }

    g_hash_table_insert(lua_scripts, script, interpreter);

    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "Script \"%s\" loaded.", script_name);
}

void lua_unload_script(const char *script_name) {
    void *key;
    void *interpreter;

    if (g_hash_table_lookup_extended(lua_scripts, script_name, &key, &interpreter)) {
        signal_emit("lua script destroyed", 1, script_name);
        g_hash_table_remove(lua_scripts, script_name);
        g_free(key);
        lua_close(interpreter);
    } else {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Script \"%s\" not loaded.", script_name);
        return;
    }

    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "Script \"%s\" unloaded.", script_name);
}

void lua_loader_init() {
    lua_scripts = g_hash_table_new(g_str_hash, g_str_equal);
}

void lua_loader_deinit() {
    g_hash_table_foreach(lua_scripts, free_lua_script_hash_table_entry, NULL);
    g_hash_table_destroy(lua_scripts);
}
