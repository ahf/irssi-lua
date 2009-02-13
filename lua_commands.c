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

static void lua_cmd_list(const char *data)
{
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
