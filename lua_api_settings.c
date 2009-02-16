#include <lua_api_settings.h>
#include <lua_irssi.h>

int lua_api_settings_get_str(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_str");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushstring(interpreter, settings_get_str(key));

    return LUA_OK;
}

int lua_api_settings_get_int(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_int");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_int(key));

    return LUA_OK;
}

int lua_api_settings_get_bool(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_bool");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushboolean(interpreter, settings_get_bool(key));

    return LUA_OK;
}

int lua_api_settings_get_time(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_time");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_time(key));

    return LUA_OK;
}

int lua_api_settings_get_level(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_level");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_level(key));

    return LUA_OK;
}

int lua_api_settings_get_size(lua_State *interpreter)
{
    const char *key;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_get_size");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -1);

    lua_pushnumber(interpreter, settings_get_size(key));

    return LUA_OK;
}

int lua_api_settings_set_str(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_str");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    settings_set_str(key, value);

    return LUA_OK;
}

int lua_api_settings_set_int(lua_State *interpreter)
{
    const char *key;
    int value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_int");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tonumber(interpreter, -1);

    settings_set_int(key, value);

    return LUA_OK;
}

int lua_api_settings_set_bool(lua_State *interpreter)
{
    const char *key;
    int value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_bool");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tonumber(interpreter, -1);

    settings_set_bool(key, value);

    return LUA_OK;
}

int lua_api_settings_set_time(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_time");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_time(key, value))
        return LUA_ERROR;

    return LUA_OK;
}

int lua_api_settings_set_level(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_level");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_level(key, value))
        return LUA_ERROR;

    return LUA_OK;
}

int lua_api_settings_set_size(lua_State *interpreter)
{
    const char *key;
    const char *value;

    if (2 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("settings_set_size");
        return LUA_ERROR;
    }

    key = lua_tostring(interpreter, -2);
    value = lua_tostring(interpreter, -1);

    if (! settings_set_size(key, value))
        return LUA_ERROR;

    return LUA_OK;
}
