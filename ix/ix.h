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
            fm->closeFile(fileID);

            return true;
        }

        bool deleteIndex() {}

        

};