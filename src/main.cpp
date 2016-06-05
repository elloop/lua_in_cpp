#include "extend_program_demo.h"
#include "lua_function_caller.h"
#include "print_lua_stack.h"
#include "simple_lua_interpreter.h"
#include "lua_call_cpp.h"

int main() {
    // simple_lua_interprator();
    // testPrintStackFunction();
    // testExtendProgram();
    // testLuaCaller();

    testCallCpp();

    return 0;
}
