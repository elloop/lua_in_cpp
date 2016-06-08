_Pragma("once")

#include "lua_51/lua.hpp"
#include <string>

void error(lua_State* lua, const char* format, ...);
void runScript(const std::string& name);
void runScriptWithLibOpen(const std::string& name);
