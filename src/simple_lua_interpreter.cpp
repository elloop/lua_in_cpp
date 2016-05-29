#include "simple_lua_interpreter.h"
#include "lua_51/lua.hpp"
#include <cstring>

void simple_lua_interprator() {

    printf("Entering lua VM......\n");
    printf("DONE! Please input your lua command:\n");

    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);

    char buff[256];
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        int error = luaL_loadbuffer(lua, buff, strlen(buff), "line") || lua_pcall(lua, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(lua, -1));
            lua_pop(lua, 1);
        }
    }

    lua_close(lua);
}
