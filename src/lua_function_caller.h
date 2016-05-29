_Pragma("once")

#include "lua_51/lua.hpp"
#include <string>

void callLuaFunction(const std::string& script, const std::string& funcName, const std::string& signature, ...);

void testLuaCaller();

