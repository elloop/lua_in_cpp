#include "extend_program_demo.h"
#include "lua_function_caller.h"
#include "print_lua_stack.h"
#include "simple_lua_interpreter.h"
#include "c_array_oper.h"
#include "include/inc.h"
#include "luatest.h"


int main() {
    // simple_lua_interprator();
    // testPrintStackFunction();
    // testExtendProgram();
    // testLuaCaller();
    // testArrayOperApi();
    runScriptWithLibOpen("res/call_cpp.lua");

    // runLuaTest();

    return 0;
}

