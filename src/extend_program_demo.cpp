#include "extend_program_demo.h"
#include "include/inc.h"

using namespace elloop;

static const char* kScriptName = "res/extend_demo.lua";

void testReadGlobalFromeLua(lua_State* lua, const char* fileName, int& w, int& h) {
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

// in Lua 5.1, lua_getfield is a special version of lua_gettable for string index.
// lua_getfield(L, -1, key) 
//
// is equal to:
//
// lua_pushstring(L, key);
// lua_gettable(L, -2);
//
// likely, lua_settable(L, table_index) is equal to : lua_push***(L, value) && lua_setfield(L, table_index, key);
//
int getIntFieldInLua51(lua_State* lua, const char* key) {
    lua_getfield(lua, -1, key);
    if (!lua_isnumber(lua, -1)) {
        error(lua, "%s field in table is not a number", key);
    }
    int result = lua_tonumber(lua, -1);
    lua_settop(lua, -2); // equals to lua_pop(lua, 1);
    return result;
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

void testReadLuaTable(lua_State* lua) {
    int r(0), g(0), b(0);

    pcln("in testReadLuaTable");
    psln(lua_gettop(lua)); // just to see if the stack is empty.

    const char* tableName = "background";
    lua_getglobal(lua, tableName);
    if (!lua_istable(lua, -1)) {
        error(lua, "%s is not a table", tableName);
    }

    pln("get field r, g, b use lua_gettable(state, table_index)");
    r = getIntField(lua, "r");
    g = getIntField(lua, "g");
    b = getIntField(lua, "b");
    psln(r);
    psln(g);
    psln(b);

    pln("get field r, g, b use lua_getfield(state, table_index, key)");
    r = getIntFieldInLua51(lua, "r");
    g = getIntFieldInLua51(lua, "g");
    b = getIntFieldInLua51(lua, "b");
    psln(r);
    psln(g);
    psln(b);

    pcln("end testReadLuaTable");
    psln(lua_gettop(lua));
    psln(lua_typename(lua, lua_type(lua, lua_gettop(lua)))); // stack top is a table.
}

void testCallLuaFunction(lua_State* lua) {
    double result(0);
    double x(20);
    double y(22);
    const char* funcName = "add";

    pcln("enter testCallLuaFunction");
    psln(lua_gettop(lua));

    pv("calling lua function %s\n", funcName);
    lua_getglobal(lua, funcName);
    lua_pushnumber(lua, x);
    lua_pushnumber(lua, y);
    if (lua_pcall(lua, 2, 1, 0)) {
        error(lua, "fail to call function : %s", lua_tostring(lua, -1));
    }

    if (!lua_isnumber(lua, -1)) {
        error(lua, "should return a number");
    }
    result = lua_tonumber(lua, -1);
    lua_pop(lua, 1);
    pv("%s(x=%.2f, y=%.2f) = %.2f\n", funcName, x, y, result);

    pcln("end testCallLuaFunction");
    psln(lua_gettop(lua));
}

void testExtendProgram() {
    lua_State* lua = luaL_newstate();

    pcln("read lua global var");
    int width(0), height(0);
    testReadGlobalFromeLua(lua, kScriptName, width, height);
    psln(width);
    psln(height);

    pcln("read lua table");
    testReadLuaTable(lua);

    pcln("call lua function");
    testCallLuaFunction(lua);

    lua_close(lua);
}

