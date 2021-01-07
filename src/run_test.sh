cd ql
flex lex.l && bison -d parser.y 
cd ..
g++ main.cpp ql/*.c -o main
./main < test.in
