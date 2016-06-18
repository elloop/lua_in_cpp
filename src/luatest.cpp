#include "luatest.h"
#include "include/inc.h"

using namespace elloop;

void testLuaRegistry() {
    auto lua = luaL_newstate();

    // save a str in registry.
    static char key = 'k';
    const char* str = "save in lua registry";
    lua_pushlightuserdata(lua, (void*)&key);
    lua_pushstring(lua, str);
    lua_settable(lua, LUA_REGISTRYINDEX);

    lua_pushlightuserdata(lua, (void*)&key);
    lua_gettable(lua, LUA_REGISTRYINDEX);
    const char* savedStr = lua_tostring(lua, -1);
    psln(savedStr);

    lua_close(lua);

}

void runLuaTest() {
    testLuaRegistry();
}

