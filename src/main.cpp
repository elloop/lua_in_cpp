#include <iostream>
#include "src/lua.hpp"
#include "src/include/inc.h"
#include "src/extend_program_demo.h"

using namespace elloop;

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

void printLuaStack(lua_State* lua) {
    pln("========= content of stack from bottom to top: ===========");
    int stackSize = lua_gettop(lua);
    for (int i=1; i<=stackSize; ++i) {
        printf("%d\t", i);
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
    psln(stackSize);
}

#define PUSH_NIL(L, SSIZE)          lua_pushnil((L));           ++(SSIZE);
#define PUSH_NUMBER(L, D, SSIZE)    lua_pushnumber((L), (D));   ++(SSIZE);
#define PUSH_STRING(L, S, SSIZE)    lua_pushstring((L), (S));   ++(SSIZE);
#define PUSH_BOOLEAN(L, B, SSIZE)   lua_pushboolean((L), (B));  ++(SSIZE);
#define PUSH_INTEGER(L, N, SSIZE)   lua_pushinteger((L), (N));  ++(SSIZE);
#define PUSH_THREAD(L, SSIZE)       lua_pushthread((L));        ++(SSIZE);
#define PUSH_TABLE(L, SSIZE)        lua_newtable((L));          ++(SSIZE);

void testPrintStackFunction() {

    lua_State* lua = luaL_newstate();

    int stackSize = lua_gettop(lua);
    assert(stackSize == 0);

    // push things of all lua type.
    
    lua_pushnil(lua);                   ++stackSize; // 1
    lua_pushnumber(lua, 1.2);           ++stackSize; // 2
    lua_pushstring(lua, "hello world"); ++stackSize; // 3
    lua_pushboolean(lua, 1);            ++stackSize; // 4
    lua_pushinteger(lua, 100);          ++stackSize; // 5
    lua_pushthread(lua);                ++stackSize; // 6
    lua_newtable(lua);                  ++stackSize; // 7

    // push a pair into table
    lua_pushstring(lua, "key1");
    lua_setfield(lua, -2, "value1");     // this will pop the "key1" from stack.

    // push another pair into table
    lua_pushstring(lua, "key2");
    lua_pushstring(lua, "value2");
    lua_settable(lua, -3);              // this will pop "key2" and "value2" from stack.

    assert(stackSize == 7);
    assert(stackSize == lua_gettop(lua));

    printLuaStack(lua);

    cr;
    pln("duplicate second elem from bottom which is 1.2");
    lua_pushvalue(lua, 2); 
    printLuaStack(lua);

    cr;
    pln("delete top 2 elements");
    lua_pop(lua, 2);            // or lua_settop(lua, stackSize - 2);
    printLuaStack(lua);

    lua_close(lua);

    // TODO: how to push:
    // 2. uerdata
    // 3. lightuserdata
    // 4. function
}

int main() {

    // test_extend_program();

    testPrintStackFunction();

    return 0;
}
