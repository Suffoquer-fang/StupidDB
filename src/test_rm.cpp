#include "rm/rm.h"
// #include "rm_internal.h"
#include <cstdio>
#include <cstring>
#include <cassert>


unsigned char h[61];
int main() {
    puts("Test Record Manager");
    
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_RecordManager *rm = new RM_RecordManager(fm, bpm);

    const char *name = "rm_test_data.txt";

    rm->createFile(name, 16);
    int fileID;
    rm->openFile(name, fileID);

    RM_FileHandle *fh = rm->getFileHandle(fileID);
    rm->fh->debug();
    int page, slot;
    RID rid;
    uint tmp_data[4] = {1, 2, 3, 4}; 
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
    

    uint* data;

    for(int i = 100; i < 200; ++i) {
        rid.set(1, i);
        fh->getRecord(rid, record);
        record.getData(data);
        
        assert(data[0] == i);
        assert(data[3] == 4);
    }
    
    rm->closeFile(fileID);


    rm->destroyFile(name);



    // printf("%d", sizeof(te));

}