#include "rm.h"
// #include "rm_internal.h"
#include <cstdio>
#include <cstring>

int main() {
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_RecordManager *rm = new RM_RecordManager(fm, bpm);

    rm->createFile("1.txt", 16);
    int fileID;
    rm->openFile("1.txt", fileID);

    puts("open");
    RM_FileHandle *fh = new RM_FileHandle(fm, bpm, fileID);
    int page, slot;
    uint tmp_data[5] = {1, 2, 3, 4, 5}; 
    puts("before");
    for(int i = 0; i < 1000; ++i) {
        tmp_data[0] = i;
        fh->insertRecord(tmp_data, page, slot);
    }
    Record r;
    fh->getRecord(2, 234, r);
    puts("done");

    for(int i = 0; i < 50; ++i)
        fh->deleteRecord(1, i);
    fh->deleteRecord(2, 487);
    fh->insertRecord(tmp_data, page, slot);
    
    printf("%d %d \n", page, slot);
    tmp_data[0] = 6666;
    fh->insertRecord(tmp_data, page, slot);
    printf("%d %d \n", page, slot);
    
    fh->insertRecord(tmp_data, page, slot);
    printf("%d %d \n", page, slot);
    for(int i = 0; i < 300; ++i)
        fh->insertRecord(tmp_data, page, slot);
    printf("%d %d \n", page, slot);
    fh->getRecord(1, 123, r);
    r.display();
    int index;
    BufType buf = bpm->getPage(fileID, 3, index);
    uint &tmp = buf[1];
    buf = bpm->getPage(fileID, 0, index);
    uint &ff = buf[1];
    printf("%d %d\n", ff, tmp);

    fh->deleteRecord(2, 100);
    
    printf("%d %d\n", ff, tmp);
    fh->deleteRecord(1, 203);
    
    printf("%d %d\n", ff, tmp);
    fh->insertRecord(tmp_data, page, slot);
    printf("%d %d\n", ff, tmp);
    
    fh->insertRecord(tmp_data, page, slot);
    printf("%d %d\n", ff, tmp);
    fh->insertRecord(tmp_data, page, slot);
    printf("%d %d\n", ff, tmp);
    
}