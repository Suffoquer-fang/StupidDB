#include "ix/ix.h"
#include <cstdio>
#include <cstring>





int main() {

    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);

    IX_IndexHandle* ih = new IX_IndexHandle();
    

    int fileID;
    fm->createFile("1ix.txt");
    fm->openFile("1ix.txt", fileID);

    ih->bpm = bpm;
    ih->fm = fm;
    ih->fileID = fileID;
    ih->fileConfig.init(INTEGER, 4);

    ih->fileConfig.maxKeyNum = 4;

    IX_BPlusTreeNode *root = ih->convertPageToNode(ih->fileConfig.rootNode);
    root->init(true);
    root->curNum = 0;

    root->debug();

    ih->forceWrite(root);
    delete root;


    printf("maxKey: %d \n\n", ih->fileConfig.maxKeyNum);
    printf("treeInfo: %d \n\n", ih->fileConfig.treeNodeInfoSize);

    int attr = 5;
    RID rid;
    rid.set(77, 0);
    ih->insertEntry(&attr, rid);

    root = ih->convertPageToNode(ih->fileConfig.rootNode);
    root->debug();

    attr = 10;
    ih->insertEntry(&attr, rid);

    root = ih->convertPageToNode(ih->fileConfig.rootNode);
    root->debug();

    attr = 1;
    ih->insertEntry(&attr, rid);

    root = ih->convertPageToNode(ih->fileConfig.rootNode);
    root->debug();

 
    attr = 0;
    rid.set(0 + 7, 0);
    ih->insertEntry(&attr, rid);
    
    ih->debug(ih->fileConfig.rootNode);
    
    printf("************\n\n");

    attr = 1;
    rid.set(1 + 7, 0);
    ih->insertEntry(&attr, rid);
    
    ih->debug(ih->fileConfig.rootNode);

    printf("************\n\n");

    attr = 2;
    rid.set(2 + 7, 0);
    ih->insertEntry(&attr, rid);
    
    ih->debug(ih->fileConfig.rootNode);

    return 0;
}