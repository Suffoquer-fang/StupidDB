#include "filesystem/fs.h"
#include "record.h"
#include "rm_internal.h"



class RM_FileHandle {
    int fileID;
    FileManager *fm;
    BufPageManager *bpm;

    RM_FileConfig fileConfig;


    RM_FileHandle(FileManager *fm, BufPageManager *bpm, int fileID) {
        this->fileID = fileID;
        this->fm = fm;
        this->bpm = bpm;

        int tmp_index;
        BufType data = bpm->getPage(fileID, 0, tmp_index);
        memcpy(&fileConfig, data, sizeof(RM_FileConfig));
        
        bpm->access(tmp_index);
    }

    ~RM_FileHandle() {}

    Record getRecord() {

    }

    bool insertRecord() {

    }

    
};