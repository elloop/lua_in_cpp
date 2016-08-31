# lua_in_cpp

# English

## How to run

Just run the ${ROOTDIR}/run.sh. (${ROOTDIR} means the root dir of this repository)

Tools required: CMake, clang++, make

~~**1. clone branch master, and enter root dir of this project.**~~

~~**2. build with cmake (version 3.0+ recommended, if your camke version is below 3.0, please edit `cmake_minimum_required` field in CMakeLists.txt of this project.)**~~

```c++
mkdir build && cd build
cmake ..
make
```

~~then you will find the executable file: `lua_in_cpp` under `build/lua_in_cpp/bin/`.~~

~~or, simpliy you can build and run the project just by running the run.sh script.~~

~~i usually run the run.sh in vim when i'am editing the cpp files under the src/ directory to see the output of the program. There is also a run.sh file under the src/ path.~~ now use Alfred instead.

you can also cutomize the build process by editing the CMakeLists.txt of this project.

## Version of Lua source codes in this project is 5.1.

# 中文说明

## 安装

直接运行: run.sh即可。

工具要求：CMake, clang++, make


~~**1. 克隆这个项目，并切换到项目根目录**~~

~~**2. 使用cmake来构建项目(推荐的cmake版本是3.0+, 如果你的版本低于3.0，请自行修改项目CMakeLists.txt的`cmake_minimum_required`字段)**~~

```c++
mkdir build && cd build
cmake ..
make
```

~~Make成功后，你会在`build/lua_in_cpp/bin/`目录下发现可执行文件: `lua_in_cpp`.~~

你也可以通过修改项目的CMakeLists.txt文件来定制构建过程。

## Lua源代码的版本是5.1

