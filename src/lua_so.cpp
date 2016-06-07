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

static const struct luaL_Reg dirutil[] = {
    {"listdir", l_listdir},
    {NULL, NULL}
};

int luaopen_ellua(lua_State* lua) {
    luaL_register(lua, "ellua", dirutil);
    return 1;
}

