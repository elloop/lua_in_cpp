#! /bin/zsh
mkdir build
cd build
cmake ..
make
cp -r ../src/res/ ./bin/
cp ./compile_commands.json ../compile_commands.json      # update compeletion database for ycm.

