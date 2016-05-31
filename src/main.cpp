#include "extend_program_demo.h"
#include "lua_function_caller.h"
#include "print_lua_stack.h"
#include "simple_lua_interpreter.h"

#include "lua_51/lua.hpp"
#include "include/inc.h"
#include <string>

using namespace elloop;
using namespace std;

int main() {

    // simple_lua_interprator();
    // testPrintStackFunction();
    // testExtendProgram();
    // testLuaCaller();

    lua_State* lua = luaL_newstate();

    luaL_loadfile(lua, "res/config.lua");

    lua_pcall(lua, 0, 0, 0);

    lua_getglobal(lua, "f");

    if (!lua_isfunction(lua, -1)) {
        error(lua, "f is not a function");
    }

    lua_pushnumber(lua, 10);

    int luaError = lua_pcall(lua, 1, 1, 0);
    if (luaError) {
        error(lua, "fail to call f: %s", lua_tostring(lua, -1));
    }

    double result = lua_tonumber(lua, -1);

    psln(result); // result = 10*10 + 2 * 10 + 100 = 220

    lua_close(lua);

    return 0;
}
