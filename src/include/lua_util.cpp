#include "include/lua_util.h"
#include <cstdlib>


void error(lua_State* lua, const char* format, ...) {
    va_list argp;
    va_start(argp, format);
    vfprintf(stderr, format, argp);
    va_end(argp);
    lua_close(lua);
    exit(EXIT_FAILURE);
}

void runScript(const std::string& name) {
    lua_State* lua = luaL_newstate();
    int e = luaL_loadfile(lua, name.c_str()) || lua_pcall(lua, 0, 0, 0);
    if (e) {
        error(lua, "fail to run script: %s, %s\n", name.c_str(), lua_tostring(lua, -1));
    }
    lua_close(lua);
}

void runScriptWithLibOpen(const std::string& name) {
    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);
    int e = luaL_loadfile(lua, name.c_str()) || lua_pcall(lua, 0, 0, 0);
    if (e) {
        error(lua, "fail to run script: %s, %s\n", name.c_str(), lua_tostring(lua, -1));
    }
    lua_close(lua);
}
