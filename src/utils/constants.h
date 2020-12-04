#pragma once

enum AttrType {
	INTEGER,
	FLOAT,
	STRING,
};

enum CompareOP { EQ, LT, GT, LE, GE, NE, NO_OP };

int compareAttr(void* a, void* b, AttrType attrType, int attrLen) {
    bool less = false;
    bool eql = false;
    switch (attrType)
    {
        case INTEGER:
            eql = *((int*)a) == *((int*)b);
            less = *((int*)a) < *((int*)b);
            break;
        case FLOAT:
            eql = *((float*)a) == *((float*)b);
            less = *((float*)a) < *((float*)b);
            break;
        case STRING:
            return memcmp(a, b, attrLen);
            break;
            
        default:
            break;
        
    }

    return less ? -1 : (eql ? 0 : 1);
}
