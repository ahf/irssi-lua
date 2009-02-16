#include <lua_api.h>
#include <lua_irssi.h>
#include <lua_loader.h>

static int lua_api_settings_get_str(lua_State *interpreter)
{
    const char *key;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    key = lua_tostring(interpreter, -1);

    lua_pushstring(interpreter, settings_get_str(key));

    return LUA_OK;
}

static int lua_api_settings_get_int(lua_State *interpreter)
{
    const char *key;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_int(key));

    return LUA_OK;
}

static int lua_api_settings_get_bool(lua_State *interpreter)
{
    const char *key;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    key = lua_tostring(interpreter, -1);

    lua_pushboolean(interpreter, settings_get_bool(key));

    return LUA_OK;
}

static int lua_api_settings_get_time(lua_State *interpreter)
{
    const char *key;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_time(key));

    return LUA_OK;
}

static int lua_api_settings_get_level(lua_State *interpreter)
{
    const char *key;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_level(key));

    return LUA_OK;
}

static int lua_api_settings_get_size(lua_State *interpreter)
{
    const char *key;
    int n;

    n = lua_gettop(interpreter);

    if (n != 1)
        return LUA_ERROR;

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_size(key));

    return LUA_OK;
}

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
    { "settings_get_str", lua_api_settings_get_str },
    { "settings_get_int", lua_api_settings_get_int },
    { "settings_get_bool", lua_api_settings_get_bool },
    { "settings_get_time", lua_api_settings_get_time },
    { "settings_get_level", lua_api_settings_get_level },
    { "settings_get_size", lua_api_settings_get_size },
    { NULL, NULL }
};

void register_lua_api(lua_State *interpreter)
{
    luaL_openlib(interpreter, "irssi", irssi_lua_functions, 0);
}
