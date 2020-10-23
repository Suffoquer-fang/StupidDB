// #include "rm.h"
#include "rm_internal.h"
#include <cstdio>
#include <cstring>

int main() {
    unsigned int* tmp = new unsigned int[100];
    memset(tmp, 0, sizeof(tmp) * 4);
    unsigned int *bitmap = &tmp[1];
    // char *bitmap = (char*)tmp;
    // for(int i = 0; i < 60; ++i)
    //     setBitFromLeft(bitmap, i, 300, 0);
    for(int i = 0; i < 20; ++i) 
        printf("%d %d\n", getBitFromLeft(tmp, i*2, 300), getBitFromLeft(tmp, i*2+1, 300));
    for(int i = 0; i < 20; ++i)
        setBitFromLeft(bitmap, i * 2, 300, 1);
    puts("asdasd");
    for(int i = 0; i < 20; ++i) 
        printf("%d %d\n", getBitFromLeft(tmp, i*2, 300), getBitFromLeft(tmp, i*2+1, 300));   

    
}