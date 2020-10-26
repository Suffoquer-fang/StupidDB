#include "../filesystem/fs.h"
#include "record.h"
#include "rm_internal.h"



class RM_FileHandle {
    int fileID;
    FileManager *fm;
    BufPageManager *bpm;

    RM_FileConfig fileConfig;

    public:
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

    int recordOff(int slotID) {
        return fileConfig.pageConfigSize + fileConfig.bitmapSize + slotID * fileConfig.recordSize;
    }

    bool getRecord(int pageID, int slotID, Record &record) {
        int index;
        BufType buf = bpm->getPage(this->fileID, pageID, index);
        bpm->access(index);

        if(slotID >= fileConfig.maxPageRecordNum) return false;
        unsigned int *bitmap = buf + fileConfig.pageConfigSize;
        if(!getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum)) return false;

        puts("succ");
        unsigned int *pdata = buf + recordOff(slotID);
        printf("pp %d %d \n", *pdata, *(pdata + 1));
        record.setRecord(fileConfig.recordSize, pageID, slotID, pdata);
        
        return true;
    }

    bool insertRecord(const unsigned int *pdata, int &pageID, int &slotID) {
        updateFreePage(fileConfig.curFreePage);

        int index;
        BufType buf = bpm->getPage(fileID, fileConfig.curFreePage, index);
        unsigned int &curRecordNum = buf[0];
        unsigned int* bitmap = buf + fileConfig.pageConfigSize;

        // puts("init");

        int freeSlotID = getFirstBitFromLeft(bitmap, fileConfig.maxPageRecordNum, 0);
        if(freeSlotID == -1) return false;
        // printf("%d %d %d\n", freeSlotID, fileConfig.maxPageRecordNum, fileConfig.bitmapSize);
        unsigned int* data = buf + recordOff(freeSlotID);
        // printf("%d %d \n", *buf, *(buf + 1));
        memcpy(data, pdata, fileConfig.recordSize * sizeof(uint));
        
        curRecordNum += 1;
        setBitFromLeft(bitmap, freeSlotID, fileConfig.maxPageRecordNum, 1);
        bpm->markDirty(index);

        pageID = fileConfig.curFreePage;
        slotID = freeSlotID;

        if(curRecordNum >= fileConfig.maxPageRecordNum) {
           updateFreePage(buf[1]);  
        }
        return true;
    }

    bool deleteRecord(int pageID, int slotID) {
        int index;
        BufType buf = bpm->getPage(fileID, pageID, index);
        unsigned int &curRecordNum = buf[0];
        unsigned int* bitmap = buf + fileConfig.pageConfigSize;
        int valid = getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum);
        if(!valid) return false;

        curRecordNum -= 1;
        setBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum, 0);
        

        if(curRecordNum == fileConfig.maxPageRecordNum - 1) {
            buf[1] = fileConfig.curFreePage;
            updateFreePage(pageID);
        }
        bpm->markDirty(index);
        return true;
    }

    bool updateRecord(const unsigned int *pdata, int pageID, int slotID) {
        int index;
        BufType buf = bpm->getPage(fileID, pageID, index);
        unsigned int* bitmap = buf + fileConfig.pageConfigSize;
        int valid = getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum);
        if(!valid) return false;

        unsigned int *data = buf + fileConfig.pageConfigSize + slotID * fileConfig.recordSize;
        memcpy(data, pdata, fileConfig.recordSize * sizeof(uint));

        return true;

    }

    void updateFreePage(int nxtFree) {
        fileConfig.curFreePage = nxtFree;
        if(nxtFree >= fileConfig.curPageNum) {
            int index;
            BufType newPage = bpm->getPage(fileID, fileConfig.curPageNum, index);
            memset(newPage, 0, PAGE_SIZE);
            newPage[1] = ++fileConfig.curPageNum;
            bpm->markDirty(index);
        }
        
        int index;
        BufType buf = bpm->getPage(fileID, 0, index);
        memcpy(buf, &(fileConfig), sizeof(RM_FileConfig));
        bpm->markDirty(index);
    }

    void checkNewPage() {
        if(fileConfig.curFreePage >= fileConfig.curPageNum) {
            int index;
            BufType newPage = bpm->getPage(fileID, fileConfig.curPageNum, index);
            memset(newPage, 0, PAGE_SIZE);
            newPage[1] = ++fileConfig.curPageNum;
        }
    }


    
    
};