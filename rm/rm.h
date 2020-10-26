#include "../filesystem/fs.h"
#include "rm_internal.h"
#include "filehandle.h"
#include <cstring>

class RM_RecordManager {
    public:
        FileManager *fm;
        BufPageManager *bpm;
        RM_RecordManager(FileManager *fm, BufPageManager *bpm) {
            this->fm = fm;
            this->bpm = bpm;
        }
        ~RM_RecordManager() {}

        bool createFile(const char* name,  int recordSize) {
            bool ret = fm->createFile(name);
            if(!ret) return false;

            RM_FileConfig fileConfig;
            fileConfig.init(recordSize);

            int fileID, index;
            if(!fm->openFile(name, fileID)) return false;
            BufType buf = bpm->getPage(fileID, 0, index);
            memcpy(buf, &fileConfig, sizeof(RM_FileConfig));

            bpm->writeBack(index);
            fm->closeFile(fileID);

            return true;

        }
        bool destroyFile(const char* name) {
            
            unlink(name);
            return true;
        }
        bool openFile(const char* name, int& fileID) {
            return fm->openFile(name, fileID);
        }
        bool closeFile(int fileID) {
            return fm->closeFile(fileID);
        }
};