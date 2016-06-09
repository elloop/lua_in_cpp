# lua_in_cpp

# English

## install

**1. clone branch , and enter root dir of this project.**

**2. run run.sh, things will be generated under build/bin/**

Notice: you will need cmake, 3.0 recommended.

you can also cutomize the build process by editing the CMakeLists.txt of this project.

## Version of Lua source codes in this project is 5.1.

# 中文说明

## 安装

**1. 克隆这个项目，并切换到项目根目录**

**2. 运行根目录的run.sh完成解释器的构建和资源的拷贝, 生成的可执行程序和资源在根目录的build/bin/文件夹下**

注意：需用到cmake(推荐的cmake版本是3.0+, 如果你的版本低于3.0，请自行修改项目CMakeLists.txt的`cmake_minimum_required`字段)


通过修改项目的CMakeLists.txt文件来定制构建过程。

## Lua源代码的版本是5.1


todo: fail to load module ... is not a bundle. 

HAVE DONE:

- try cpp dynamic lib, nm -gm output the luaopen symbol.

- try c dynamic lib, nm -gm output the luaopen symbol.

