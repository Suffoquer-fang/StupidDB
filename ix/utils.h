#ifndef IX_INTERNAL
#define IX_INTERNAL

#include "../utils/constants.h"

struct IX_BPlusTreeNode {
    bool isLeafNode;
    int curNum;
    int prevNode;
    int nextNode;
    int parentNode;
    
    unsigned int* keys;
    unsigned int* rids;

    void init(bool isLeaf = false, int pre = -1, int nxt = -1, int par = -1) {
        isLeafNode = isLeaf;
        curNum = 0;
        prevNode = pre;
        nextNode = nxt;
        parentNode = par;
    }
};

struct IX_FileConfig {
    AttrType attrType;
    int attrLength;
    int rootNode;
    int curNodeNum;
    int maxKeyNum;
    int treeNodeInfoSize;
    int maxKeySize;

    void init(AttrType attr) {
        attrType = attr;
        
    }
};











#endif