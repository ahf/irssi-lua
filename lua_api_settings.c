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
#include <lua_core.h>

#include <glib.h>

static GHashTable *lua_settings = NULL;

static void lua_settings_free(gpointer key, gpointer list, gpointer user_data) {
    g_list_foreach(list, (GFunc)g_free, user_data);
    g_list_free(list);
}

static void lua_add_setting(lua_State *interpreter, const char *key) {
    GList *list;
    char *script = get_caller_name(interpreter);

    g_return_if_fail(NULL != script);

    list = g_hash_table_lookup(lua_settings, script);
    list = g_list_append(list, g_strdup(key));
    g_hash_table_insert(lua_settings, script, list);
    g_free(script);
}

static void lua_remove_setting(lua_State *interpreter, const char *key) {
    GList *list, *pos;
    char *script = get_caller_name(interpreter);

    g_return_if_fail(NULL != script);

    list = g_hash_table_lookup(lua_settings, script);

    pos = glist_find_icase_string(list, key);

    if (NULL != pos) {
        list = g_list_remove(list, pos->data);
        g_hash_table_insert(lua_settings, script, list);
    }

    g_free(script);
}

static void sig_lua_script_destroyed(char *script) {
    GList *list;

    list = g_hash_table_lookup(lua_settings, script);

    if (NULL != list) {
        GList *tmp;

        for (tmp = list; NULL != tmp; tmp = tmp->next)
            settings_remove(tmp->data);

        lua_settings_free(script, list, NULL);
        g_hash_table_remove(lua_settings, script);
    }
}

void lua_api_settings_init() {
    lua_settings = g_hash_table_new(g_str_hash, g_str_equal);

    signal_add("lua script destroyed", (SIGNAL_FUNC)sig_lua_script_destroyed);
}

void lua_api_settings_deinit() {
    g_hash_table_foreach(lua_settings, lua_settings_free, NULL);
    g_hash_table_destroy(lua_settings);

    signal_remove("lua script destroyed", (SIGNAL_FUNC)sig_lua_script_destroyed);
}

int lua_api_settings_get_str(lua_State *interpreter) {
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_get_str");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushstring(interpreter, settings_get_str(key));

    return LUA_SUCCESS;
}

int lua_api_settings_get_int(lua_State *interpreter) {
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_get_int");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_int(key));

    return LUA_SUCCESS;
}

int lua_api_settings_get_bool(lua_State *interpreter) {
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_get_bool");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushboolean(interpreter, settings_get_bool(key));

    return LUA_SUCCESS;
}

int lua_api_settings_get_time(lua_State *interpreter) {
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_get_time");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_time(key));

    return LUA_SUCCESS;
}

int lua_api_settings_get_level(lua_State *interpreter) {
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_get_level");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_level(key));

    return LUA_SUCCESS;
}

int lua_api_settings_get_size(lua_State *interpreter) {
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_get_size");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_size(key));

    return LUA_SUCCESS;
}

int lua_api_settings_set_str(lua_State *interpreter) {
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter)) {
        arity_mismatch("settings_set_str");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    settings_set_str(key, value);

    return LUA_SUCCESS;
}

int lua_api_settings_set_int(lua_State *interpreter) {
    const char *key;
    int value;

    if (2 != lua_gettop(interpreter)) {
        arity_mismatch("settings_set_int");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tonumber(interpreter, -1);

    settings_set_int(key, value);

    return LUA_SUCCESS;
}

int lua_api_settings_set_bool(lua_State *interpreter) {
    const char *key;
    int value;

    if (2 != lua_gettop(interpreter)) {
        arity_mismatch("settings_set_bool");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_toboolean(interpreter, -1);

    settings_set_bool(key, value);

    return LUA_SUCCESS;
}

int lua_api_settings_set_time(lua_State *interpreter) {
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter)) {
        arity_mismatch("settings_set_time");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_time(key, value))
        return LUA_FAILURE;

    return LUA_SUCCESS;
}

int lua_api_settings_set_level(lua_State *interpreter) {
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter)) {
        arity_mismatch("settings_set_level");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_level(key, value))
        return LUA_FAILURE;

    return LUA_SUCCESS;
}

int lua_api_settings_set_size(lua_State *interpreter) {
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter)) {
        arity_mismatch("settings_set_size");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_size(key, value))
        return LUA_FAILURE;

    return LUA_SUCCESS;
}

int lua_api_settings_add_str(lua_State *interpreter)
{
    const char *section;
    const char *key;
    const char *default_value;

    if (3 != lua_gettop(interpreter)) {
        arity_mismatch("settings_add_str");
        return LUA_FAILURE;
    }

    section = lua_tostring(interpreter, -3);
    key = lua_tostring(interpreter, -2);
    default_value = lua_tostring(interpreter, -1);

    lua_add_setting(interpreter, key);
    settings_add_str_module(MODULE_NAME"/scripts", section, key, default_value);

    return LUA_SUCCESS;
}

int lua_api_settings_add_int(lua_State *interpreter) {
    const char *section;
    const char *key;
    int default_value;

    if (3 != lua_gettop(interpreter)) {
        arity_mismatch("settings_add_int");
        return LUA_FAILURE;
    }

    section = lua_tostring(interpreter, -3);
    key = lua_tostring(interpreter, -2);
    default_value = lua_tonumber(interpreter, -1);

    lua_add_setting(interpreter, key);
    settings_add_int_module(MODULE_NAME"/scripts", section, key, default_value);

    return LUA_SUCCESS;
}

int lua_api_settings_add_bool(lua_State *interpreter) {
    const char *section;
    const char *key;
    int def = 0;

    if (3 != lua_gettop(interpreter)) {
        arity_mismatch("settings_add_bool");
        return LUA_FAILURE;
    }

    section = lua_tostring(interpreter, -3);
    key = lua_tostring(interpreter, -2);
    def = lua_toboolean(interpreter, -1);

    lua_add_setting(interpreter, key);
    settings_add_bool_module(MODULE_NAME"/scripts", section, key, def);

    return LUA_SUCCESS;
}

int lua_api_settings_add_time(lua_State *interpreter) {
    const char *section;
    const char *key;
    const char *default_value;

    if (3 != lua_gettop(interpreter)) {
        arity_mismatch("settings_add_time");
        return LUA_FAILURE;
    }

    section = lua_tostring(interpreter, -3);
    key = lua_tostring(interpreter, -2);
    default_value = lua_tostring(interpreter, -1);

    lua_add_setting(interpreter, key);
    settings_add_str_module(MODULE_NAME"/scripts", section, key, default_value);

    return LUA_SUCCESS;
}

int lua_api_settings_add_level(lua_State *interpreter) {
    const char *section;
    const char *key;
    const char *default_value;

    if (3 != lua_gettop(interpreter)) {
        arity_mismatch("settings_add_level");
        return LUA_FAILURE;
    }

    section = lua_tostring(interpreter, -3);
    key = lua_tostring(interpreter, -2);
    default_value = lua_tostring(interpreter, -1);

    lua_add_setting(interpreter, key);
    settings_add_str_module(MODULE_NAME"/scripts", section, key, default_value);

    return LUA_SUCCESS;
}

int lua_api_settings_add_size(lua_State *interpreter) {
    const char *section;
    const char *key;
    const char *default_value;

    if (3 != lua_gettop(interpreter)) {
        arity_mismatch("settings_add_size");
        return LUA_FAILURE;
    }

    section = lua_tostring(interpreter, -3);
    key = lua_tostring(interpreter, -2);
    default_value = lua_tostring(interpreter, -1);

    lua_add_setting(interpreter, key);
    settings_add_str_module(MODULE_NAME"/scripts", section, key, default_value);

    return LUA_SUCCESS;
}

int lua_api_settings_remove(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter)) {
        arity_mismatch("settings_remove");
        return LUA_FAILURE;
    }

    key = lua_tostring(interpreter, -1);

    lua_remove_setting(interpreter, key);
    settings_remove(key);

    return LUA_SUCCESS;
}
