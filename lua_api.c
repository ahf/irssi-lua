#include <lua_api.h>
#include <lua_irssi.h>
#include <lua_loader.h>

#define LUA_OK 1
#define LUA_ERROR 0

static int lua_api_print(lua_State *interpreter)
{
    const char *message;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    message = lua_tostring(interpreter, -1);

    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "%s", message);

    return LUA_OK;
}

static const luaL_Reg irssi_lua_functions[] = {
    { "print", lua_api_print },
    { NULL, NULL }
};

void register_lua_api(lua_State *interpreter)
{
    luaL_openlib(interpreter, "irssi", irssi_lua_functions, 0);
}
