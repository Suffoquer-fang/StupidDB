#include "rm/rm.h"
// #include "rm_internal.h"
#include <cstdio>
#include <cstring>

int main() {
    puts("Test Record Manager");
    
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_RecordManager *rm = new RM_RecordManager(fm, bpm);



    rm->createFile("1.txt", 16);
    int fileID;
    rm->openFile("1.txt", fileID);

    RM_FileHandle *fh = rm->getFileHandle(fileID);
    rm->fh->debug();
    int page, slot;
    RID rid;
    uint tmp_data[5] = {1, 2, 3, 4, 5}; 
    // puts("before");
    for(int i = 0; i < 1000; ++i) {
        tmp_data[0] = i;
        fh->insertRecord(tmp_data, rid);
    }
    // printf("%d %d\n", rid.pageID, rid.slotID);
    for(int i = 0; i < 50; ++i) {
        rid.set(1, i);
        fh->deleteRecord(rid);
    }

    Record record;
    rid.set(1, 100);
    fh->getRecord(rid, record);


    rm->fh->debug();
    record.display();
    
    rm->closeFile(fileID);



    // printf("%d", sizeof(te));

}