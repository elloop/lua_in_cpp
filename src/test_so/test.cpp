#include "lua_51/lua.hpp"

int l_add(lua_State* lua) {
    int i = luaL_checknumber(lua, 1);
    lua_pushnumber(lua, i+10);
    return 1;
}


static const luaL_reg testlib[] = {
    {"add", l_add},
    {NULL, NULL}
};


extern "C" int luaopen_test(lua_State* lua) {
    luaL_register(lua, "test", testlib);
    return 1;
}

