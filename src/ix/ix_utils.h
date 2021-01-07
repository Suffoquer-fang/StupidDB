#ifndef IX_INTERNAL
#define IX_INTERNAL

#include "../utils/constants.h"
#include "../rm/record.h"

struct IX_BPlusTreeNode {
    bool isLeafNode;
    int curNum;
    int prevNode;
    int nextNode;
    int parentNode;
    int selfID;
    
    char* keys;
    unsigned int* rids;

    void init(bool isLeaf = false, int pre = -1, int nxt = -1, int par = -1) {
        isLeafNode = isLeaf;
        curNum = 0;
        prevNode = pre;
        nextNode = nxt;
        parentNode = par;
    }

    char* getIthKeyPointer(int i, int attrLen) {return keys + i * attrLen;}
    unsigned int getIthPage(int i) {return rids[2 * i];}
    unsigned int getIthSlot(int i) {return rids[2 * i + 1];}

    void setRID(int i, RID rid) {
        rids[2 * i] = rid.pageID;
        rids[2 * i + 1] = rid.slotID;
    }

    void setRID(int i, int pageID, int slotID) {
        rids[2 * i] = pageID;
        rids[2 * i + 1] = slotID;
    }


    void debug() {
        printf("nodeID: %d, parent: %d, prev %d, next %d\n", selfID, parentNode, prevNode, nextNode);
        printf("childNum: %d\n", curNum);
        for(int i = 0; i < min(curNum, 10); ++i)
            printf("%d: %d - %d   ", i, *(getIthKeyPointer(i, 4)), getIthPage(i));
        printf("\n\n");


    }


};

struct IX_FileConfig {
    AttrType attrType;
    int attrLength;
    int rootNode;
    int curNodeNum;
    int maxKeyNum;
    int treeNodeInfoSize;
    int maxRidSize;

    void init(AttrType attr, int attrLen) {
        attrType = attr;
        attrLength = attrLen;
        rootNode = 1;
        curNodeNum = 1;

        
        treeNodeInfoSize = (sizeof(IX_BPlusTreeNode) - 2 * sizeof(unsigned int *));
        maxKeyNum = (PAGE_INT_NUM - treeNodeInfoSize) * sizeof(uint) / (sizeof(RID) + attrLen) - 1;
        maxRidSize = sizeof(RID) * maxKeyNum / sizeof(uint);
        maxKeyNum -= 1;

    }
};










#endif