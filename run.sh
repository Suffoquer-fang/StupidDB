#!/bin/bash

g++ testfilesystem.cpp -o main
./main
rm main
g++ test_rm.cpp -o main
./main
rm main