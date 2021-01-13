cd ql
flex lex.l && bison -d parser.y 
cd ..
g++ -std=c++11 -march=x86-64 main.cpp ql/*.c -o main
