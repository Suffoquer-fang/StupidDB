#include "ix/ix.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>






int main() {

    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);

    

    int fileID;
    fm->createFile("1ix.txt");
    fm->openFile("1ix.txt", fileID);

    
    IX_IndexHandle* ih = new IX_IndexHandle(fm, bpm, fileID);
    ih->fileConfig.init(INTEGER, 4);

    ih->fileConfig.maxKeyNum = 8;

    IX_BPlusTreeNode *root = ih->convertPageToNode(ih->fileConfig.rootNode);
    root->init(true);
    root->curNum = 0;

    root->debug();

    ih->forceWrite(root);
    delete root;


    printf("maxKey: %d \n\n", ih->fileConfig.maxKeyNum);
    printf("treeInfo: %d \n\n", ih->fileConfig.treeNodeInfoSize);

    int attr = 0;
    RID rid;
    
    map<int, RID> test_map;
    

    for(int i = 0; i < 50000; ++i) {
        attr = 2 * i;
        rid.set(i + 1, 2 * i);
        ih->insertEntry(&attr, rid);
        test_map.insert(pair<int, RID>(attr, rid));
    }

    for(int i = 49999; i >= 0; --i) {
        attr = 2 * i + 1;
        rid.set(i + 1, 2 * i);
        ih->insertEntry(&attr, rid);
        test_map.insert(pair<int, RID>(attr, rid));
    }


    vector<int> key_vec;
    vector<RID> rid_vec;

    ih->iterLeaves(key_vec, rid_vec);

    // for(int i = 0; i < rid_vec.size(); ++i) {
    //     printf("%d-(%d-%d) ", key_vec[i], rid_vec[i].pageID, rid_vec[i].slotID);
    // }
    // printf("\n");

    


    
    // test_map.insert(pair<int, RID>(1, RID(2, 1)));
    // test_map.insert(pair<int, RID>(2, RID(2, 1)));
    // test_map.insert(pair<int, RID>(3, RID(2, 1)));
    int i = 0;
    for(auto it = test_map.begin(); it != test_map.end(); ++it) {
        // printf("%d-(%d-%d) ", it->first, (it->second).pageID, (it->second).slotID);
        assert(it->first == key_vec[i]);
        assert((it->second).pageID == rid_vec[i].pageID);
        assert((it->second).slotID == rid_vec[i].slotID);
        i += 1;

    }
    puts("pass");



    return 0;
}