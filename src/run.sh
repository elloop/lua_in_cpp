#! /bin/zsh
cd ..
mkdir build
cd build
cmake ..
make
cp -r ../src/res/ ./bin/res/
cd bin
./lua_in_cpp
