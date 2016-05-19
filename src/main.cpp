#include <iostream>
#include "lua.hpp"

void simple_lua_interprator(lua_State* lua) {
    char buff[256];
    luaL_openlibs(lua);
    
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        int error = luaL_loadbuffer(lua, buff, strlen(buff), "line") || lua_pcall(lua, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(lua, -1));
            lua_pop(lua, 1);
        }
    }
}

void print_lua_stack(lua_State* lua) {
    int n = lua_gettop(lua);
    printf("%d\n", n);
    
    for (int i=1; i<=n; ++i) {
        int t = lua_type(lua, i);
        switch (t) {
            case LUA_TNUMBER:
                printf("%s: %.2f\n", lua_typename(lua, t), lua_tonumber(lua, i));
                break;
            case LUA_TBOOLEAN:
                printf("%s: %d\n", lua_typename(lua, t), lua_toboolean(lua, i));
                break;
            case LUA_TSTRING:
                printf("%s: %s\n", lua_typename(lua, t), lua_tostring(lua, i));
                break;
            default:
                // LUA_TTABLE
                // LUA_TTHREAD
                // LUA_TFUNCTION
                // LUA_TLIGHTUSERDATA
                // LUA_TUSERDATA
                // LUA_TNIL
                printf("%s\n", lua_typename(lua, t));
                break;
        }
    }
}

int main() {

    lua_State* lua = luaL_newstate();

    lua_pushnil(lua);
    lua_pushnumber(lua, 1.2);
    lua_pushstring(lua, "hello world");
    lua_pushboolean(lua, 1);
    lua_pushinteger(lua, 100);
    lua_pushthread(lua);
    lua_pushvalue(lua, 2); // duplicate 1.2
    print_lua_stack(lua);

    // TODO: how to push:
    // 1. table
    // 2. uerdata
    // 3. lightuserdata
    // 4. function

    // delete top 2 elements.
    int stack_size = lua_gettop(lua);
    printf("stack size: %d\n", lua_gettop(lua));
    ----stack_size;
    lua_settop(lua, stack_size);
    printf("stack size: %d\n", lua_gettop(lua));
    
    printf("%s\n", lua_typename(lua, stack_size + 2));
    
    lua_close(lua);
    return 0;
}
