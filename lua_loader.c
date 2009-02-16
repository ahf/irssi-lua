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

static GList *lua_scripts = NULL;
static lua_script_t *current_lua_script = NULL;

static void free_lua_script(lua_script_t *t)
{
    if (t->interpreter)
        lua_close(t->interpreter);

    g_free(t->script_name);
    g_free(t);
}

lua_script_t *get_current_script()
{
    return current_lua_script;
}

GList *get_currently_loaded_scripts()
{
    return lua_scripts;
}

lua_script_t *get_script(const char *script_name)
{
    GList *tmp;

    for (tmp = lua_scripts; NULL != tmp; tmp = tmp->next)
    {
        lua_script_t *t = tmp->data;
        if (0 == strcmp(script_name, (char *)t->script_name))
            return t;
    }

    return NULL;
}

void lua_load_script(const char *script_name)
{
    struct stat stat_buf;
    lua_script_t *script;

    if (NULL != get_script(script_name))
    {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Script \"%s\" already loaded.", script_name);
        return;
    }

    if (0 != stat(script_name, &stat_buf))
    {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Script \"%s\" not found.", script_name);
        return;
    }

    script = malloc(sizeof(lua_script_t));
    g_assert(script);

    script->interpreter = luaL_newstate();
    script->script_name = g_strdup(script_name);

    if (script->interpreter == NULL)
    {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Unable to create lua interpreter");
        free_lua_script(script);
        return;
    }

    luaL_openlibs(script->interpreter);
    register_lua_api(script->interpreter);
    current_lua_script = script;

    if (luaL_loadfile(script->interpreter, script_name) != 0)
    {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Unable to load script: %s", lua_tostring(script->interpreter, -1));
        free_lua_script(script);
        return;
    }

    if (lua_pcall(script->interpreter, 0, 0, 0) != 0)
    {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Unable to execute the script: %s", lua_tostring(script->interpreter, -1));
        free_lua_script(script);
        return;
    }

    lua_scripts = g_list_append(lua_scripts, script);

    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "Script \"%s\" loaded.", script_name);
}

void lua_unload_script(const char *script_name)
{
    lua_script_t *script;

    if (NULL == (script = get_script(script_name)))
    {
        printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, "Script \"%s\" not loaded.", script_name);
        return;
    }
    else
    {
        signal_emit("lua script destroyed", 1, script);
        free_lua_script(script);
        lua_scripts = g_list_remove(lua_scripts, script);
    }

    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "Script \"%s\" unloaded.", script_name);
}

void lua_loader_init()
{
}

void lua_loader_deinit()
{
    g_list_foreach(lua_scripts, (GFunc)free_lua_script, NULL);
}
