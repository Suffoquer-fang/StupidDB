cd src/ql
flex lex.l && bison -d parser.y 
cd ../..
g++ -std=c++11 src/main.cpp src/ql/*.c -o main
