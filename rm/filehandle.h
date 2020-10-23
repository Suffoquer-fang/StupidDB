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

    bool getRecord(int pageID, int slotID, Record &record) {
        int index;
        BufType buf = bpm->getPage(this->fileID, pageID, index);
        bpm->access(index);


        int curRecordNum = buf[0];
        if(slotID >= curRecordNum) return false;
        unsigned int *bitmap = &buf[2];
        if(!getBitFromLeft(bitmap, slotID, curRecordNum)) return false;

        unsigned int *pdata = buf + fileConfig.pageConfigSize + slotID * fileConfig.recordSize;
        record.setRecord(fileConfig.recordSize, pageID, slotID, pdata);
        
        return true;
    }

    bool insertRecord(const unsigned int *pdata, int &pageID, int &slotID) {
        

        int index;
        BufType buf = bpm->getPage(fileID, fileConfig.curFreePage, index);
        unsigned int &curRecordNum = buf[0];
        unsigned int* bitmap = &buf[2];

        int freeSlotID = getFirstBitFromLeft(bitmap, curRecordNum, 0);
        if(freeSlotID == -1) return false;

        unsigned int* data = buf + fileConfig.pageConfigSize + freeSlotID * fileConfig.recordSize;
        memcpy(data, pdata, fileConfig.recordSize);

        curRecordNum += 1;
        setBitFromLeft(bitmap, freeSlotID, curRecordNum, 1);
        bpm->markDirty(index);

        pageID = fileConfig.curFreePage;
        slotID = freeSlotID;

        if(curRecordNum >= fileConfig.maxPageRecordNum) {
           updateFreePage(buf[1]);  
        }
        return true;
    }

    void updateFreePage(int nxtFree) {
        fileConfig.curFreePage = nxtFree;
        if(nxtFree >= fileConfig.curPageNum) {
            int index;
            BufType newPage = bpm->getPage(fileID, fileConfig.curPageNum, index);
            memset(newPage, 0, PAGE_SIZE);
            newPage[1] = ++fileConfig.curPageNum;
        }
        
        int index;
        BufType buf = bpm->getPage(fileID, 0, index);
        memcpy(buf, &(fileConfig), sizeof(RM_FileConfig));
        bpm->markDirty(index);
    }


    
    
};