#! /bin/zsh
cd ..
mkdir build
cd build
cmake ..
make

cp -r ../src/res/ ./bin/res/                             # copy resources.

cp ./compile_commands.json ../compile_commands.json      # update compeletion database for ycm.

cd bin
./lua_in_cpp
