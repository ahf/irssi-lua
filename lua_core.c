#include <lua_core.h>
#include <lua_loader.h>
#include <lua_irssi.h>
#include <lua_commands.h>

void lua_init()
{
    lua_loader_init();
    lua_commands_init();

    module_register(MODULE_NAME, "core");
}

void lua_deinit()
{
    lua_loader_deinit();
    lua_commands_deinit();
}
