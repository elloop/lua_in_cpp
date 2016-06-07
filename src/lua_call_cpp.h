#include "lua_51/lua.h"
#include "lua_51/lualib.h"
#include "lua_51/lauxlib.h"

#define LUA_ELLIB "ellua"
LUALIB_API int (luaopen_ellua)(lua_State* lua);

/*
 *
 *
 *
 *Undefined symbols for architecture x86_64:
  "_luaopen_ellua", referenced from:
      _lualibs in linit.c.o
ld: symbol(s) not found for architecture x86_64
*/
