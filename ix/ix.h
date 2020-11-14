#include "../filesystem/fs.h"
#include "indexhandle.h"
#include <cstring>

class IX_IndexManager {
    public:
        FileManager *fm;
        BufPageManager *bpm;
        IX_IndexHandle *ih;
        
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

            bool ret = fm->createFile(getFileName(name, indexNo).c_str());
            if(!ret) return false;

            IX_FileConfig fileConfig;
            fileConfig.init(attrType, attrLen);
            // puts("init");
            int fileID, index;
            if(!fm->openFile(name, fileID)) return false;
            BufType buf = bpm->getPage(fileID, 0, index);
            memcpy(buf, &fileConfig, sizeof(IX_FileConfig));
            bpm->markDirty(index);
            bpm->writeBack(index);
            
            
            BufType buf = bpm->getPage(fileID, 1, index);
            IX_BPlusTreeNode *root = new IX_BPlusTreeNode();
            root->init(true, -1, -1, -1);
            root->curNum = 0;

            memcpy(buf, root, fileConfig.treeNodeInfoSize);
            
            bpm->markDirty(index);
            bpm->writeBack(index);

            delete root;
            
            
            
            
            fm->closeFile(fileID);

            return true;
        }

        bool deleteIndex() {}


        bool openIndex(const char* name, int& fileID) {
            bool ret = fm->openFile(name, fileID);
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