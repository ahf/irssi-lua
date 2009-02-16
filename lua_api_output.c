#include <lua_api_output.h>
#include <lua_irssi.h>

int lua_api_print(lua_State *interpreter)
{
    const char *message;

    if (1 != lua_gettop(interpreter))
    {
        wrong_number_of_arguments("print");
        return LUA_ERROR;
    }

    message = lua_tostring(interpreter, -1);

    printtext(NULL, NULL, MSGLEVEL_CLIENTCRAP, "%s", message);

    return LUA_OK;
}
