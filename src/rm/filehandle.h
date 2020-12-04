#pragma once

#include "../filesystem/fs.h"
#include "record.h"
#include "utils.h"

class RM_FileHandle {

	int fileID;
	FileManager *fm;
	BufPageManager *bpm;

	RM_FileConfig fileConfig;

	friend class RM_FileScan;
	friend class SM_SystemManager;

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

	void debug() {
		printf("debug %d %d \n", fileConfig.curFreePage, fileConfig.curPageNum);
	}

	int recordOff(int slotID) {
		return fileConfig.pageConfigSize + fileConfig.bitmapSize +
			   slotID * fileConfig.recordSize;
	}

	bool getRecord(RID rid, Record &record) {
		int pageID = rid.pageID;
		int slotID = rid.slotID;

		int index;
		BufType buf = bpm->getPage(this->fileID, pageID, index);
		bpm->access(index);

		if (slotID >= fileConfig.maxPageRecordNum) return false;
		unsigned int *bitmap = buf + fileConfig.pageConfigSize;
		if (!getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum))
			return false;

		unsigned int *pdata = buf + recordOff(slotID);
		// printf("pp %d %d \n", *pdata, *(pdata + 1));
		record.setRecord(fileConfig.recordSize, pageID, slotID, pdata);

		return true;
	}

	bool getRecord(RID rid, unsigned int* &ret) {
		int pageID = rid.pageID;
		int slotID = rid.slotID;

		int index;
		BufType buf = bpm->getPage(this->fileID, pageID, index);
		bpm->access(index);

		if (slotID >= fileConfig.maxPageRecordNum) return false;
		unsigned int *bitmap = buf + fileConfig.pageConfigSize;
		if (!getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum))
			return false;

		unsigned int *pdata = buf + recordOff(slotID);
		// printf("pp %d %d \n", *pdata, *(pdata + 1));
		ret = pdata;
		return true;
	}

	bool insertRecord(const unsigned int *pdata, RID &rid) {
		updateFreePage(fileConfig.curFreePage);

		int index;
		BufType buf = bpm->getPage(fileID, fileConfig.curFreePage, index);
		unsigned int &curRecordNum = buf[0];
		unsigned int *bitmap = buf + fileConfig.pageConfigSize;

		// puts("init");

		int freeSlotID =
			getFirstBitFromLeft(bitmap, fileConfig.maxPageRecordNum, 0);
		if (freeSlotID == -1) return false;
		// printf("%d %d %d\n", freeSlotID, fileConfig.maxPageRecordNum,
		// fileConfig.bitmapSize);
		unsigned int *data = buf + recordOff(freeSlotID);
		// printf("%d %d \n", *buf, *(buf + 1));
		memcpy(data, pdata, fileConfig.recordSize * sizeof(uint));

		curRecordNum += 1;
		setBitFromLeft(bitmap, freeSlotID, fileConfig.maxPageRecordNum, 1);
		bpm->markDirty(index);

		int pageID = fileConfig.curFreePage;
		int slotID = freeSlotID;
		rid.set(pageID, slotID);

		if (curRecordNum >= fileConfig.maxPageRecordNum) {
			updateFreePage(buf[1]);
		}
		return true;
	}

	bool deleteRecord(RID rid) {
		int pageID = rid.pageID;
		int slotID = rid.slotID;
		int index;
		BufType buf = bpm->getPage(fileID, pageID, index);
		unsigned int &curRecordNum = buf[0];
		unsigned int *bitmap = buf + fileConfig.pageConfigSize;
		int valid = getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum);
		if (!valid) return false;

		curRecordNum -= 1;
		setBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum, 0);

		if (curRecordNum == fileConfig.maxPageRecordNum - 1) {
			buf[1] = fileConfig.curFreePage;
			updateFreePage(pageID);
		}
		if (curRecordNum == 0) {
			fileConfig.curPageNum -= 1;
			updateFileConfig();
		}
		bpm->markDirty(index);
		return true;
	}

	bool updateRecord(const unsigned int *pdata, RID rid) {
		int pageID = rid.pageID;
		int slotID = rid.slotID;

		int index;
		BufType buf = bpm->getPage(fileID, pageID, index);
		unsigned int *bitmap = buf + fileConfig.pageConfigSize;
		int valid = getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum);
		if (!valid) return false;

		unsigned int *data =
			buf + fileConfig.pageConfigSize + slotID * fileConfig.recordSize;
		memcpy(data, pdata, fileConfig.recordSize * sizeof(uint));

		return true;
	}

	void updateFreePage(int nxtFree) {
		fileConfig.curFreePage = nxtFree;
		if (nxtFree >= fileConfig.curPageNum) {
			int index;
			BufType newPage =
				bpm->getPage(fileID, fileConfig.curPageNum, index);
			memset(newPage, 0, PAGE_SIZE);
			newPage[1] = ++fileConfig.curPageNum;
			bpm->markDirty(index);
		}

		updateFileConfig();
	}

	void updateFileConfig() {
		int index;
		BufType buf = bpm->getPage(fileID, 0, index);
		memcpy(buf, &(fileConfig), sizeof(RM_FileConfig));
		bpm->markDirty(index);
	}

	bool getNextValidRID(RID &cur) {
		int pageID = cur.pageID;
		int slotID = cur.slotID;
		int index;
		BufType buf = bpm->getPage(fileID, pageID, index);
		unsigned int *bitmap = buf + fileConfig.pageConfigSize;

		while(true) {
			slotID += 1;
			if (slotID >= fileConfig.maxPageRecordNum) {
				slotID = 0;
				pageID += 1;
				if (pageID >= fileConfig.curPageNum) {
					return false;
				}
				buf = bpm->getPage(fileID, pageID, index);
				bitmap = buf + fileConfig.pageConfigSize;
			}

			
			if (getBitFromLeft(bitmap, slotID, fileConfig.maxPageRecordNum)) {
				cur.pageID = pageID;
				cur.slotID = slotID;
				return true;
			}
		}
		return false;
		
	}

	
};