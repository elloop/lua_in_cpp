#include "extend_program_demo.h"
#include "include/inc.h"

static const char* kScriptName = "res/extend_demo.lua";

void read_global_frome_lua(lua_State* lua, const char* fileName, int& w, int& h) {
    if (luaL_loadfile(lua, fileName) || lua_pcall(lua, 0, 0, 0)) {
        error(lua, "fail to run script: %s", lua_tostring(lua, -1));
    }

    lua_getglobal(lua, "width");
    lua_getglobal(lua, "height");
    if (!lua_isnumber(lua, -2)) {
        error(lua, "width should be a number\n");
    }
    if (!lua_isnumber(lua, -1)) {
        error(lua, "height should be a number\n");
    }
    w = lua_tointeger(lua, -2);
    h = lua_tointeger(lua, -1);
}

void test_extend_program() {
    lua_State* lua = luaL_newstate();
    int width(0), height(0);
    psln(width);
    psln(height);
    read_global_frome_lua(lua, kScriptName, width, height);
    psln(width);
    psln(height);
}

