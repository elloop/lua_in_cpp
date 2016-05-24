#include "extend_program_demo.h"
#include "include/inc.h"

static const char* kScriptName = "res/extend_demo.lua";

void test_read_global_frome_lua(lua_State* lua, const char* fileName, int& w, int& h) {
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

int getIntField(lua_State* lua, const char* key) {
    lua_pushstring(lua, key);
    lua_gettable(lua, -2);
    if (!lua_isnumber(lua, -1)) {
        error(lua, "%s field in table is not a number", key);
    }
    int result = lua_tonumber(lua, -1);
    lua_pop(lua, 1);
    return result;
}

void test_read_lua_table(lua_State* lua) {
    int r(0), g(0), b(0);

    const char* tableName = "background";
    lua_getglobal(lua, tableName);
    if (!lua_istable(lua, -1)) {
        error(lua, "%s is not a table", tableName);
    }

    r = getIntField(lua, "r");
    g = getIntField(lua, "g");
    b = getIntField(lua, "b");

    psln(r);
    psln(g);
    psln(b);
}

void test_extend_program() {
    lua_State* lua = luaL_newstate();

    // read lua global
    int width(0), height(0);
    test_read_global_frome_lua(lua, kScriptName, width, height);
    psln(width);
    psln(height);

    // read lua table.
    test_read_lua_table(lua);

    
    lua_close(lua);
}

