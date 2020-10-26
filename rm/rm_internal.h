#ifndef INTERNAL
#define INTERNAL

#include "../filesystem/fs.h"


struct RM_PageConfig {
    int curRecordNum;
    int nextFreePage;
};


struct RM_FileConfig {
    int recordSize;
    int curFreePage;
    int maxPageRecordNum;
    int curPageNum;
    int pageConfigSize;
    int bitmapSize;
    void init(int rSize) {
        recordSize = (rSize + 3) / 4;
        curFreePage = 1;
        curPageNum = 1;

        pageConfigSize = sizeof(RM_PageConfig) / sizeof(int);

        maxPageRecordNum = ((PAGE_INT_NUM - pageConfigSize) * 32 - 31) / (32 * recordSize + 1);

        // n * rs + (n + 31) / 32 + cs <= ps
        // n <= ((ps - cs) * 32 - 31) / (32 * rs + 1)

        bitmapSize = (maxPageRecordNum + 31) / 32;

    }
};

int getBitFromLeft(unsigned int* bitmap, int index, int bitmapSize) {
    if(index >= bitmapSize) return -1;
    return (bitmap[index >> 5] & (1 << (index & 31))) > 0 ? 1 : 0;
}

bool setBitFromLeft(unsigned int* bitmap, int index, int bitmapSize, int bit) {
    if(index >= bitmapSize) return false;
    if(bit) 
        bitmap[index >> 5] |= (1 << (index & 31));
    else
        bitmap[index >> 5] &= ~(1 << (index & 31));
    return true;
}

int getFirstBitFromLeft(unsigned int* bitmap, int bitmapSize, int bit) {
    for(int i = 0; i < bitmapSize; ++i) {
        if(getBitFromLeft(bitmap, i, bitmapSize) == bit)
            return i;
    }
    return -1;
}

#endif