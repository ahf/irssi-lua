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

#include <lua_commands.h>
#include <lua_irssi.h>
#include <lua_loader.h>
#include <lua_core.h>

static void lua_cmd_default(const char *data, SERVER_REC *server, void *item)
{
    if (! *data)
        data = "list";

    command_runsub("lua", data, server, item);
}

static void lua_cmd_load(const char *data)
{
    void *free_arg;
    const char *script;

    if (! cmd_get_params(data, &free_arg, 1, &script))
        return;

    if ('\0' == *script)
        cmd_param_error(CMDERR_NOT_ENOUGH_PARAMS);

    lua_load_script(script);

    cmd_params_free(free_arg);
}

static void lua_cmd_unload(const char *data)
{
    void *free_arg;
    const char *script;

    if (! cmd_get_params(data, &free_arg, 1, &script))
        return;

    if ('\0' == *script)
        cmd_param_error(CMDERR_NOT_ENOUGH_PARAMS);

    lua_unload_script(script);

    cmd_params_free(free_arg);
}

static void print_lua_script(gpointer key, gpointer interpreter, gpointer user_data)
{
    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "%s", key);
}

static void lua_cmd_list(const char *data)
{
    g_hash_table_foreach(get_currently_loaded_scripts(), print_lua_script, NULL);
}

void lua_commands_init()
{
    command_bind("lua", NULL, (SIGNAL_FUNC)lua_cmd_default);
    command_bind("lua load", NULL, (SIGNAL_FUNC)lua_cmd_load);
    command_bind("lua unload", NULL, (SIGNAL_FUNC)lua_cmd_unload);
    command_bind("lua list", NULL, (SIGNAL_FUNC)lua_cmd_list);
}

void lua_commands_deinit()
{
    command_unbind("lua", (SIGNAL_FUNC)lua_cmd_default);
    command_unbind("lua load", (SIGNAL_FUNC)lua_cmd_load);
    command_unbind("lua unload", (SIGNAL_FUNC)lua_cmd_unload);
    command_unbind("lua list", (SIGNAL_FUNC)lua_cmd_list);
}
