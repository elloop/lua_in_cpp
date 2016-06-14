cmake_minimum_required ( VERSION 3.0)
project(lua_in_cpp)

# export compilation_database for YouCompleteMe Plugin in VIM.
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

include_directories(${PROJECT_SOURCE_DIR}/src)

set(CXX_FLAGS -std=c++11 -g -Wall -fPIC -fvisibility=hidden)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

if (APPLE)
    set(CMAKE_CXX_COMPILER      "clang++" )
endif(APPLE)

set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG " )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib/)

message("==================== script for" ${PROJECT_NAME} " ==================== ")
set(LUA_SRC
    # lua source codes
    src/lua_51/lapi.c
    src/lua_51/lauxlib.c
    src/lua_51/lbaselib.c
    src/lua_51/lcode.c
    src/lua_51/ldblib.c
    src/lua_51/ldebug.c
    src/lua_51/ldo.c
    src/lua_51/ldump.c
    src/lua_51/lfunc.c
    src/lua_51/lgc.c
    src/lua_51/linit.c
    src/lua_51/liolib.c
    src/lua_51/llex.c
    src/lua_51/lmathlib.c
    src/lua_51/lmem.c
    src/lua_51/loadlib.c
    src/lua_51/lobject.c
    src/lua_51/lopcodes.c
    src/lua_51/loslib.c
    src/lua_51/lparser.c
    src/lua_51/lstate.c
    src/lua_51/lstring.c
    src/lua_51/lstrlib.c
    src/lua_51/ltable.c
    src/lua_51/ltablib.c
    src/lua_51/ltm.c
    src/lua_51/lundump.c
    src/lua_51/lvm.c
    src/lua_51/lzio.c
    src/lua_51/print.c
    #src/lua_51/lua.c
    #src/lua_51/luac.c
)

set(SRC_LIST
    src/main.cpp
    src/include/lua_util.cpp
    src/simple_lua_interpreter.cpp
    src/print_lua_stack.cpp
    src/extend_program_demo.cpp
    src/lua_function_caller.cpp
    src/c_array_oper.cpp

    ${LUA_SRC}
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Clang Compiler
endif()

if (APPLE)
    message("platform: OS X")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
    add_definitions( -DLUA_USE_MACOSX )     # enable dynamic linking for lua.
endif(APPLE)

foreach(src ${SRC_LIST})
    message(${src})
endforeach()

add_executable(${PROJECT_NAME} ${SRC_LIST})


set(LUA_SO_NAME ellua)
message("==================== script for " ${LUA_SO_NAME} "==================== ")

set(LUA_SO_SRC
    src/lua_so.cpp
    ${LUA_SRC}
)

foreach(src ${LUA_SO_SRC})
    message(${src})
endforeach()

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fvisibility=hidden" )

if (APPLE)
    add_library(${LUA_SO_NAME} MODULE ${LUA_SO_SRC})        # a bunlde on mac os
else (APPLE)
    add_library(${LUA_SO_NAME} SHARED ${LUA_SO_SRC})        # will be a dylib on mac.
endif(APPLE)

# specify a new name for ${LUA_SO_NAME}
#set_target_properties(${LUA_SO_NAME} PROPERTIES OUTPUT_NAME dog)   # will generate a libdog.so instead of libellua.so

