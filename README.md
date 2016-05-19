# lua_in_cpp

# English

## install

**1. clone branch master, and enter root dir of this project.**

**2. build with cmake (version 3.0+ recommended, if your camke version is below 3.0, please edit `cmake_minimum_required` field in CMakeLists.txt of this project.)**

```c++
mkdir build && cd build
cmake ..
make
```

then you will find the executable file: `lua_in_cpp` under `build/lua_in_cpp/bin/`.

you can also cutomize the build process by editing the CMakeLists.txt of this project.

# 中文说明

## 安装

**1. 克隆这个项目，并切换到项目根目录**

**2. 使用cmake来构建项目(推荐的cmake版本是3.0+, 如果你的版本低于3.0，请自行修改项目CMakeLists.txt的`cmake_minimum_required`字段)**

```c++
mkdir build && cd build
cmake ..
make
```

Make成功后，你会在`build/lua_in_cpp/bin/`目录下发现可执行文件: `lua_in_cpp`.

你也可以通过修改项目的CMakeLists.txt文件来定制构建过程。

