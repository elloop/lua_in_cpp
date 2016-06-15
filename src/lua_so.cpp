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
    while ((entry = readdir(dir)) != NULL) {
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

static int l_split(lua_State* lua) {
    const char* str = luaL_checkstring(lua, -2);
    const char* delim = luaL_checkstring(lua, -1);
    const char* p;

    int i(1);
    lua_newtable(lua);      // the return value: a table.
    while ((p = strchr(str, *delim)) != NULL) {
        lua_pushlstring(lua, str, p - str + 1);
        lua_rawseti(lua, -2, i++);
        str = p + 1;
    }

    lua_pushstring(lua, str);
    lua_rawseti(lua, -2, i);

    return 1;       // return the table.
}

static const struct luaL_Reg ellibs[] = {
    {"listdir", l_listdir},
    {"mapArray", l_mapArray},
    {"splitStr", l_split},
    {NULL, NULL}
};

int luaopen_ellua(lua_State* lua) {
    luaL_register(lua, "ellua", ellibs);
    return 1;
}

