#include "../rm.h"
// #include "rm_internal.h"
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>

using namespace std;

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
    uint tmp_data[4] = {1, 5, 3, 4}; 
    // puts("before");
    for(int i = 0; i < 1000; ++i) {
        tmp_data[0] = i;
        fh->insertRecord(tmp_data, rid);
    }
    // printf("%d %d\n", rid.pageID, rid.slotID);
    // for(int i = 0; i < 50; ++i) {
    //     rid.set(1, i);
    //     fh->deleteRecord(rid);
    // }


    uint* data = new uint[5];

    RM_FileScan* fs = new RM_FileScan();
    int value = 980;
    fs->OpenScan(fh, INTEGER_TYPE, 4, 0, NO_OP, &value);

    while(true) {
        if(fs->next(data)) {
            cout << data[0] <<" "<< data[1] <<" "<< data[2] << endl;
        } else break;
    }

    cout << "done" << endl;
    
    rm->closeFile(fileID);


    rm->destroyFile(name);



    // printf("%d", sizeof(te));

}