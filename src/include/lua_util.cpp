#include <cstdlib>
#include "src/include/lua_util.h"


void error(lua_State* lua, const char* format, ...) {
    va_list argp;
    va_start(argp, format);
    vfprintf(stderr, format, argp);
    va_end(argp);
    lua_close(lua);
    exit(EXIT_FAILURE);
}
