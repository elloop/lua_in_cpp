cmake_minimum_required ( VERSION 3.0)
project(lua_in_cpp)

# export compilation_database for YouCompleteMe Plugin in VIM.
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )


include_directories(${PROJECT_SOURCE_DIR}/)

set(CXX_FLAGS -std=c++11 -g -Wall)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER      "clang++" )
set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG " )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin/)

set(SRC_LIST
    src/main.cpp
    src/extend_program_demo.cpp
    src/include/lua_util.cpp
    src/lapi.c
    src/lauxlib.c
    src/lbaselib.c
    src/lcode.c
    src/ldblib.c
    src/ldebug.c
    src/ldo.c
    src/ldump.c
    src/lfunc.c
    src/lgc.c
    src/linit.c
    src/liolib.c
    src/llex.c
    src/lmathlib.c
    src/lmem.c
    src/loadlib.c
    src/lobject.c
    src/lopcodes.c
    src/loslib.c
    src/lparser.c
    src/lstate.c
    src/lstring.c
    src/lstrlib.c
    src/ltable.c
    src/ltablib.c
    src/ltm.c
    src/lundump.c
    src/lvm.c
    src/lzio.c
    src/print.c
    )

foreach(src ${SRC_LIST})
    #message("src: " ${src})
endforeach()

add_executable(${PROJECT_NAME} ${SRC_LIST})

