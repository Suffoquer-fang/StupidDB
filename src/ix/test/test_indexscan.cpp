#include "../ix.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <ctime>

#include <random>
#include <iostream>

using namespace std;

unsigned char h[61];

void printScan(IX_IndexScan* scan) {
    RID rid;
    while(true) {
        if(!scan->next(rid)) break;
        cout << '(' << rid.pageID << ',' << rid.slotID << ')' << ' ';
    }
    cout << endl;
}

bool check(IX_IndexScan* scan, multimap<int, RID> &map) {
    RID rid;
    for(auto it = map.begin(); it != map.end(); it++) {
        
        assert(scan->next(rid));
        assert(rid.equal(it->second));
    }
    assert(!scan->next(rid));
    return true;
}





int main() {
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);

    const char *name = "test_ix_data";
    IX_IndexManager* im = new IX_IndexManager(fm, bpm);
    
    int fileID;
    im->createIndex(name, 1, INTEGER_TYPE, 5);
    im->openIndex(name, 1, fileID);

    IX_IndexHandle *ih = im->getIndexHandle(fileID);

    multimap<int, RID> map;

    ih->fileConfig.maxKeyNum = 3;
    
    int size = 10;
    RID rid;

    char data[5] = {0};

    IX_IndexScan* scan = new IX_IndexScan();
    char value[5] = {0};

    for(int i = 0; i < size; ++i) {
        int key = i;
        rid.set(i, 1);

        data[0] = 0;
        memcpy(data + 1, &key, 4);

        ih->insertEntry(data, rid);
        map.insert(make_pair(key, rid));
        cout << "insert " << i << endl;
    }

    // data[0] = 1;
    memset(data, 0, sizeof(data));
    data[0] = 1;

    rid.set(1, 2);
    ih->insertEntry(data, rid);

    rid.set(2, 2);
    ih->insertEntry(data, rid);

    scan->openScan(ih, NO_OP, value);
    printScan(scan);

    int tmp = 2;
    memcpy(value + 1, &tmp, 4);
    scan->openScan(ih, LE_OP, value);
    printScan(scan);

    memset(value, 0, sizeof(value));
    value[0] = 1;
    scan->openScan(ih, EQ_OP, value);
    printScan(scan);
    // check(scan, map);

    // for(int i = 0; i < 100; ++i) {
    //     cout << "delete " << i << endl;
    //     int time = rand() % map.size();
    //     auto it = map.begin();
    //     while(--time)
    //         it++;
    //     int key = it->first;
    //     RID temp = it->second;

    //     ih->deleteEntry(&key, temp);
    //     map.erase(it);
    // }

    
    // scan->openScan(ih, NO_OP, &value);
    // // printScan(scan);
    // check(scan, map);


    im->destroyIndex(name, 1);
}