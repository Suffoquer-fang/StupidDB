#pragma once
#include "../filesystem/fs.h"
#include "filehandle.h"
#include "filescan.h"
#include <cstring>

class RM_RecordManager {
    public:
        FileManager *fm;
        BufPageManager *bpm;
        RM_FileHandle *fh;

        RM_RecordManager(FileManager *fm, BufPageManager *bpm) {
            this->fm = fm;
            this->bpm = bpm;
        }
        ~RM_RecordManager() {
            bpm->close();
        }

        bool createFile(const char* name,  int recordSize) {
            bool ret = fm->createFile(name);
            if(!ret) return false;

            RM_FileConfig fileConfig;
            fileConfig.init(recordSize);
            // puts("init");
            int fileID, index;
            if(!fm->openFile(name, fileID)) return false;
            BufType buf = bpm->getPage(fileID, 0, index);
            memcpy(buf, &fileConfig, sizeof(RM_FileConfig));
            bpm->markDirty(index);
            bpm->writeBack(index);
            fm->closeFile(fileID);

            return true;

        }
        bool destroyFile(const char* name) {
            unlink(name);
            return true;
        }
        bool openFile(const char* name, int& fileID) {
            bool ret = fm->openFile(name, fileID);
            if(!ret) return false;
            
            return true;
        }
        bool closeFile(int fileID) {
            fh = nullptr;
            bpm->close();
            return fm->closeFile(fileID);
        }

        RM_FileHandle* getFileHandle(int fileID) {
            this->fh = new RM_FileHandle(fm, bpm, fileID);
            return fh;
        }
};