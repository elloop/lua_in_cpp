#include "lua_so.h"
#include "include/inc.h"
#include <dirent.h>
#include <errno.h>

using namespace elloop;

static int l_listdir(lua_State* lua) {
    const char* pathName = luaL_checkstring(lua, 1);

    DIR* dir;
    dir = opendir(pathName);
    if (!dir) {
        lua_pushnil(lua);
        lua_pushstring(lua, strerror(errno));
        return 2;
    }

    lua_newtable(lua);                      //  stack: table

    int i = 1;
    dirent* entry;
    while (entry = readdir(dir)) {
        lua_pushnumber(lua, i++);           //  stack: table key
        lua_pushstring(lua, entry->d_name); //  stack: table key value
        lua_settable(lua, -3);
    }

    closedir(dir);
    return 1;
}

static int l_mapArray(lua_State* lua) {
    luaL_checktype(lua, 1, LUA_TTABLE);
    luaL_checktype(lua, 2, LUA_TFUNCTION);
    size_t n = lua_objlen(lua, 1);
    for (int i=1; i<=n; ++i) {
        lua_pushvalue(lua, 2);
        lua_rawgeti(lua, 1, i);
        lua_call(lua, 1, 1);
        lua_rawseti(lua, 1, i);
    }
    return 0;
}

static const struct luaL_Reg dirutil[] = {
    {"listdir", l_listdir},
    {"mapArray", l_mapArray},
    {NULL, NULL}
};

int luaopen_ellua(lua_State* lua) {
    luaL_register(lua, "ellua", dirutil);
    return 1;
}

