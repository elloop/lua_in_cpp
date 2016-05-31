#include "lua_function_caller.h"
#include "include/inc.h"
#include <algorithm>
#include <iterator>

using namespace elloop;

void callLuaFunction(const std::string& script, const std::string& funcName, const std::string& signature, ...) {
    lua_State* lua = luaL_newstate();

    if (luaL_loadfile(lua, script.c_str()) || lua_pcall(lua, 0, 0, 0)) {
        error(lua, "fail to load script: %s, %s", script.c_str(), lua_tostring(lua, -1));
    }

    lua_getglobal(lua, funcName.c_str());
    if (!lua_isfunction(lua, -1)) {
        error(lua, "%s should be a function", funcName.c_str());
    }

    va_list varg;
    va_start(varg, signature);

    int argCount(0);
    std::string returnStr;
    auto iter = signature.begin();
    while (iter != signature.end()) {
        if (*iter == '>') {
            copy(++iter, signature.end(), std::back_inserter(returnStr));
            break;
        }
        else if (*iter == 'd') {
            lua_pushnumber(lua, va_arg(varg, double));
        }
        else if (*iter == 'i') {
            lua_pushinteger(lua, va_arg(varg, int));
        }
        else if (*iter == 's') {
            lua_pushstring(lua, va_arg(varg, char*));
        }
        else if (*iter == 'b') {
            lua_pushboolean(lua, va_arg(varg, bool));
        }
        else {
            error(lua, "unknown arg type: %c", *iter);
        }
        ++iter;
        ++argCount;
    }

    psln(returnStr);
    int numberOfReturn = returnStr.length();
    if (lua_pcall(lua, argCount, numberOfReturn, 0) != 0) {
        error(lua, "fail to call %s", funcName.c_str());
    }

    iter = returnStr.begin();
    int returnValueLeft = numberOfReturn;
    while (iter != returnStr.end()) {
        if (returnValueLeft < 1) {
            error(lua, "too much return value specified in signature");
        }

        if (*iter == 'd') {
            if (!lua_isnumber(lua, -returnValueLeft)) {
                error(lua, "%d-th return value should be double", numberOfReturn - returnValueLeft + 1);
            }
            *va_arg(varg, double*) = lua_tonumber(lua, -returnValueLeft);
        }     
        else if (*iter == 'i') {
            if (!lua_isnumber(lua, -returnValueLeft)) {
                error(lua, "%d-th return value should be int", numberOfReturn - returnValueLeft + 1);
            }
            *va_arg(varg, int*) = lua_tointeger(lua, -returnValueLeft);
        }
        else if (*iter == 'b') {
            if (!lua_isboolean(lua, -returnValueLeft)) {
                error(lua, "%d-th return value should be boolean", numberOfReturn - returnValueLeft + 1);
            }
            *va_arg(varg, bool*) = lua_toboolean(lua, -returnValueLeft);
        }
        else {
            error(lua, "unsupported return type: %c", *iter);
        }
        ++iter;
        --returnValueLeft;
    }
    va_end(varg);
    lua_close(lua);
    pv("function call %s(...) complete!\n", funcName.c_str());
}

void testLuaCaller() {

    std::string scriptName("res/extend_demo.lua");

    int x, y, z;
    x = 10; y = 20; z = 0;
    callLuaFunction(scriptName, "add", "ii>i", x, y, &z);
    psln(z);

    int n(10);
    const char* prefix = "hello";
    callLuaFunction(scriptName, "concat", "si", prefix, n);

    double dx, dy, dz;
    dx = 1.2, dy = 1.3, dz = 0;
    callLuaFunction(scriptName, "add", "dd>d", dx, dy, &dz);
    psln(dz);

    bool bx, by, bz;
    bx = false, by = false, bz = true;
    callLuaFunction(scriptName, "fufudezheng", "bb>b", bx, by, &bz);
    psln(bz);

}

