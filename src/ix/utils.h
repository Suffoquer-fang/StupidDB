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
    
    unsigned int* keys;
    unsigned int* rids;

    void init(bool isLeaf = false, int pre = -1, int nxt = -1, int par = -1) {
        isLeafNode = isLeaf;
        curNum = 0;
        prevNode = pre;
        nextNode = nxt;
        parentNode = par;
    }

    unsigned int* getIthKeyPointer(int i, int attrLen) {return keys + i * attrLen;}
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
        for(int i = 0; i < min(curNum, 5); ++i)
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
        maxKeyNum = (PAGE_INT_NUM - treeNodeInfoSize) * sizeof(uint) / (sizeof(RID) + attrLength) - 1;
        maxRidSize = sizeof(RID) * maxKeyNum / sizeof(uint);
        maxKeyNum -= 1;

    }
};




int compareAttr(void* a, void* b, AttrType attrType, int attrLen) {
    bool less = false;
    bool eql = false;
    switch (attrType)
    {
        case INTEGER:
            eql = *((int*)a) == *((int*)b);
            less = *((int*)a) < *((int*)b);
            break;
        case FLOAT:
            eql = *((float*)a) == *((float*)b);
            less = *((float*)a) < *((float*)b);
            break;
        case STRING:
            return memcmp(a, b, attrLen);
            break;
            
        default:
            break;
        
    }

    return less ? -1 : (eql ? 0 : 1);
}






#endif