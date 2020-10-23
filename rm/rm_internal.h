
struct RM_FileConfig {
    int recordSize;
    int curFreePage;
    int maxPageRecordNum;
    int curPageNum;
    int pageConfigSize;
};

struct RM_PageConfig {
    int curRecordNum;
    int nextFreePage;
    unsigned int *bitmap;
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
