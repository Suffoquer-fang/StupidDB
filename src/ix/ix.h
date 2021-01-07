#pragma once
#include "../filesystem/fs.h"
#include "indexhandle.h"
#include "indexscan.h"
#include <cstring>

class IX_IndexManager {
    public:
        FileManager *fm;
        BufPageManager *bpm;
        
        IX_IndexManager(FileManager *fm, BufPageManager *bpm) {
            this->fm = fm;
            this->bpm = bpm;
        }

        ~IX_IndexManager() {}


        string getFileName(const char* name, int indexNo) {
            string ret = string(name) + "." + std::to_string(indexNo);
            return ret;
        }
        
        bool createIndex(const char* name, int indexNo, AttrType attrType, int attrLen) {
            
            const char* realName = getFileName(name, indexNo).c_str();
            bool ret = fm->createFile(realName);
            if(!ret) return false;

            IX_FileConfig fileConfig;
            fileConfig.init(attrType, attrLen);
            // puts("init\n");
            // printf("sss %d\n", fileConfig.treeNodeInfoSize);
            int fileID, index;
            if(!fm->openFile(realName, fileID)) return false;
            BufType buf = bpm->getPage(fileID, 0, index);
            memcpy(buf, &fileConfig, sizeof(IX_FileConfig));
            bpm->markDirty(index);
            bpm->writeBack(index);
            
            int index2;
            BufType buf2 = bpm->getPage(fileID, 1, index2);
            IX_BPlusTreeNode *root = new IX_BPlusTreeNode();
            root->init(true, 0, 0, 0);
            root->curNum = 0;

            memcpy(buf2, root, fileConfig.treeNodeInfoSize);
            
            bpm->markDirty(index2);
            bpm->writeBack(index2);

            delete root;
            
            // printf("init done\n");
            
            
            fm->closeFile(fileID);

            return true;
        }

        bool destroyIndex(const char* name, int indexNo) {
            const char* realName = getFileName(name, indexNo).c_str();
            unlink(realName);
            return true;
        }


        bool openIndex(const char* name, int indexNo, int& fileID) {
            const char* realName = getFileName(name, indexNo).c_str();
            bool ret = fm->openFile(realName, fileID);
            if(!ret) return false;
            
            return true;
        }
        bool closeIndex(int fileID) {
            bpm->close();
            return fm->closeFile(fileID);
        }

        IX_IndexHandle* getIndexHandle(int fileID) {
            IX_IndexHandle* ret = new IX_IndexHandle(fm, bpm, fileID);
            return ret;
        }

        

};