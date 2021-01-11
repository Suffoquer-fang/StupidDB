cd ql
flex lex.l && bison -d parser.y 
cd ..
g++ -std=c++11 main.cpp ql/*.c -o main
