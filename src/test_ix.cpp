#include "ix/ix.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>






int main() {

    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);

    const char *name = "test_ix_data";
    IX_IndexManager* im = new IX_IndexManager(fm, bpm);
    
    int fileID;
    im->createIndex(name, 1, INTEGER, 4);
    im->openIndex(name, 1, fileID);

    IX_IndexHandle *ih = im->getIndexHandle(fileID);
    // ih->fileConfig.init(INTEGER, 4);
    ih->fileConfig.maxKeyNum = 5;

    ih->debug(ih->fileConfig.rootNode);


    printf("maxKey: %d \n\n", ih->fileConfig.maxKeyNum);
    printf("treeInfo: %d \n\n", ih->fileConfig.treeNodeInfoSize);

    int attr = 0;
    RID rid;
    
    map<int, RID> test_map;
    

    for(int i = 0; i < 500; ++i) {
        attr = 2 * i;
        rid.set(i + 1, 2 * i);
        ih->insertEntry(&attr, rid);
        test_map.insert(pair<int, RID>(attr, rid));
    }

    for(int i = 499; i >= 0; --i) {
        attr = 2 * i + 1;
        rid.set(i + 1, 2 * i);
        ih->insertEntry(&attr, rid);
        test_map.insert(pair<int, RID>(attr, rid));
    }

    for(int i = 20; i < 100; ++i) {
        attr = 2 * i;
        rid.set(i + 1, 2 * i);
        ih->deleteEntry(&attr, rid);
        test_map.erase(attr);
    }


    vector<int> key_vec;
    vector<RID> rid_vec;

    ih->iterLeaves(key_vec, rid_vec);

    int i = 0;
    for(auto it = test_map.begin(); it != test_map.end(); ++it) {
        // printf("%d-(%d-%d) ", it->first, (it->second).pageID, (it->second).slotID);
        assert(it->first == key_vec[i]);
        assert((it->second).pageID == rid_vec[i].pageID);
        assert((it->second).slotID == rid_vec[i].slotID);
        i += 1;

    }

    int id, index;

    attr = 20;
    rid.set(1, 2);
    ih->insertEntry(&attr, rid);
    ih->insertEntry(&attr, rid);
    ih->insertEntry(&attr, rid);
    printf("%d\n", ih->searchFirstEntry(&attr, id, index));
    printf("%d %d\n", id, index);
    ih->debug(id);
    // ih->debug(9);

    IX_IndexScan* is = new IX_IndexScan();
    is->openScan(ih, LT, &attr);
    puts("open");
    while(is->next(rid)) {
        printf("%d %d\n", rid.slotID, rid.pageID);
    }


    im->destroyIndex(name, 1);

    return 0;
}