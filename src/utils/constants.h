// #ifndef _CONST
// #define _CONST
#pragma once

// #include <stdio.h>
// #include <string>
// #include <vector>
#include <iostream>
#include <cstring>
using namespace std;

enum AttrType {
	INTEGER_TYPE,
	FLOAT_TYPE,
	STRING_TYPE,
    DATE_TYPE
};

enum CompareOP { EQ_OP, LT_OP, GT_OP, LE_OP, GE_OP, NE_OP, NO_OP };

inline int compareAttr(void* a, void* b, AttrType attrType, int attrLen) {
    bool less = false;
    bool eql = false;
    char isnull_a = ((char*)a)[0];
    char isnull_b = ((char*)b)[0];
    if(isnull_a == 1 && isnull_b == 1) return 0;
    if(isnull_a == 0 && isnull_b == 1) return -1;
    if(isnull_a == 1 && isnull_b == 0) return 1;
    a = (char*)a + 1;
    b = (char*)b + 1;
    switch (attrType)
    {
        case INTEGER_TYPE:
            eql = *((int*)a) == *((int*)b);
            less = *((int*)a) < *((int*)b);
            break;
        case FLOAT_TYPE:
            eql = *((float*)a) == *((float*)b);
            less = *((float*)a) < *((float*)b);
            break;
        case STRING_TYPE:
            return memcmp(a, b, attrLen - 1);
            break;
            
        default:
            break;
        
    }

    return less ? -1 : (eql ? 0 : 1);
}

inline string AttrType2Str(AttrType a) {
    if(a == INTEGER_TYPE) return "INTEGER";
    if(a == FLOAT_TYPE) return "FLOAT";
    if(a == STRING_TYPE) return "STRING";
    if(a == DATE_TYPE) return "DATE";
}

inline string Attr2Str(void* pData, AttrType type, int len) {
    if(((char*)pData)[0] != 0) return "NULL";
    pData = (char*)pData + 1;
    if(type == INTEGER_TYPE) {
        // cout << "www " << (*((int*)pData)) << endl;
        return to_string(*((int*)pData));
    }
    if(type == FLOAT_TYPE) {
        return "undone";
    }
    if(type == STRING_TYPE) {
        return string((char*)pData, len - 1);
    }
}

inline void debugCompareOP(CompareOP op) {
    if(op == EQ_OP) cout << "=" << " ";
    if(op == LE_OP) cout << "<=" << " ";
    if(op == GE_OP) cout << ">=" << " ";
    if(op == LT_OP) cout << "<" << " ";
    if(op == GT_OP) cout << ">" << " ";
    if(op == NE_OP) cout << "!=" << " ";
    if(op == NO_OP) cout << "NO_OP" << " ";
}





enum RC {
    
};


// #endif