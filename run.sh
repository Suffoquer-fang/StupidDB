#!/bin/bash

mkdir build

cd build 

cmake ..

make

make test 


# g++ testfilesystem.cpp -o main
# ./main
# rm main
# g++ test_rm.cpp -o main
# ./main
# rm main