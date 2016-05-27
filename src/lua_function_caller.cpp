#include "lua_function_caller.h"

void callLuaFunction(const std::string& funcName, const std::string& signature, ...) {
    lua_State* lua = luaL_newstate();

    lua_getglobal(lua, funcName.c_str());
    if (!lua_isfunction(lua, -1)) {
        error(lua, "%s should be a function", funcName.c_str());
    }

    va_list varg;
    va_start(varg, signature);

    auto iter = signature.begin();
    while (iter != signature.end()) {
        if (*iter == "") {
            
        }
        ++iter;
    }

    va_end(varg);
    lua_close(lua);

}
