_Pragma("once")

#include "lua_51/lua.hpp"

#define EL_EXPORT __attribute__((visibility("default"))) extern

EL_EXPORT int luaopen_ellua(lua_State* lua);

//int luaopen_ellua(lua_State* lua);

