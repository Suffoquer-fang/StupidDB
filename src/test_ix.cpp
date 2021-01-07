#include "ix/ix.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <ctime>

#include <random>




unsigned char h[61];
int main() {

    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);

    const char *name = "test_ix_data";
    IX_IndexManager* im = new IX_IndexManager(fm, bpm);
    
    int fileID;
    im->createIndex(name, 1, INTEGER_TYPE, 4);
    im->openIndex(name, 1, fileID);

    IX_IndexHandle *ih = im->getIndexHandle(fileID);
    // ih->fileConfig.init(INTEGER, 4);
    // ih->fileConfig.maxKeyNum = 8;

    ih->debug(ih->fileConfig.rootNode);


    printf("maxKey: %d \n\n", ih->fileConfig.maxKeyNum);
    printf("treeInfo: %d \n\n", ih->fileConfig.treeNodeInfoSize);

    int attr = 0;
    RID rid;
    
    map<int, RID> test_map;
    int datasize = 1e6;
    vector<int> datavec(datasize, 0);
    for(int i = 0; i < datasize; ++i)
        datavec[i] = rand();
    
    // std::shuffle(datavec.begin(), datavec.end());

    auto start = clock();

    for(int i = 0; i < datasize; ++i) {

        attr = datavec[i];
        // if(test_map.find(attr) != test_map.end()) continue;
        rid.set(1, 1);
        ih->insertEntry(&attr, rid);
        // test_map.insert(pair<int, RID>(attr, rid));
        // if(i % 10000 == 0)
        //     cout << "insert " << i << endl;
    }

    cout << (clock() - start) * 1.0/ CLOCKS_PER_SEC << endl;
    // start = clock();
    // cout << ih->time_cnt / CLOCKS_PER_SEC << endl;
    // cout << ih->down / CLOCKS_PER_SEC << endl;
    // cout << ih->up / CLOCKS_PER_SEC << endl;
   

    // for(int i = 20; i < 31000; ++i) {
    //     attr = datavec[i];
    //     rid.set(1, 1);
    //     ih->deleteEntry(&attr, rid);
    //     test_map.erase(attr);
    // }
    // cout << (clock() - start) * 1.0/ CLOCKS_PER_SEC << endl;

    vector<int> key_vec;
    vector<RID> rid_vec;

    // ih->iterLeaves(key_vec, rid_vec);
    // // attr = 7394;
    // // ih->searchEntry(&attr, rid_vec);
    // // for(int i = 0; i < rid_vec.size(); ++i) {
    // //     printf("(%d-%d)\n",  rid_vec[i].pageID, rid_vec[i].slotID);
    // // }
    int i = 0;
    for(auto it = test_map.begin(); it != test_map.end(); ++it) {
        // printf("%d-(%d-%d) ", it->first, (it->second).pageID, (it->second).slotID);
        // printf("%u-(%d-%d)\n", (uint)(key_vec[i]), rid_vec[i].pageID, rid_vec[i].slotID);
        if(it->first != key_vec[i]) {
            printf("%u-(%d-%d) ", it->first, (it->second).pageID, (it->second).slotID);
            printf("%u-(%d-%d)\n", (uint)(key_vec[i]), rid_vec[i].pageID, rid_vec[i].slotID);
        }
        assert((it->second).pageID == rid_vec[i].pageID);
        assert((it->second).slotID == rid_vec[i].slotID);
        i += 1;

    }

    


    im->destroyIndex(name, 1);

    return 0;
}