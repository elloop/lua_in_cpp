#include "extend_program_demo.h"
#include "lua_function_caller.h"
#include "print_lua_stack.h"
#include "simple_lua_interpreter.h"
#include "include/inc.h"


int main() {
    // simple_lua_interprator();
    // testPrintStackFunction();
    // testExtendProgram();
    // testLuaCaller();

    runScriptWithLibOpen("res/call_cpp.lua");

    return 0;
}
