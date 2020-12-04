#include "../utils/constants.h"
#include "filehandle.h"

class RM_FileScan {
   public:
	RM_FileHandle *fh;
	CompareOP op;
	void *value;
	AttrType attrType;
	int attrLen;
	int attrOff;

	RID curRID;
	unsigned int* curData;

	RM_FileScan() {
	}

	~RM_FileScan() {}

	bool OpenScan(RM_FileHandle *fh, AttrType attrType, int attrLength,
				  int attrOffset, CompareOP op, void *value) {
		this->fh = fh;
		this->op = op;
		this->value = value;
		this->attrType = attrType;
		this->attrLen = attrLength;
		this->attrOff = attrOffset;

		curRID.set(1, -1);
		curData = nullptr;
	}

	bool nextRecord() {
		bool ret = fh->getNextValidRID(curRID);
		if(!ret) {
			curData = nullptr;
			return false;
		}
		fh->getRecord(curRID, curData);
		return true;
	}
	bool next(unsigned int* ret) {
		while(true) {
			if(!nextRecord()) return false;
			if(satisfy()) break;
		}
		memcpy(ret, curData, fh->fileConfig.recordSize * sizeof(uint));
		return true;
	}

	bool next(unsigned int* ret, RID &rid) {
		bool ret = next(ret);
		if(ret)
			rid.set(curRID.pageID, curRID.slotID);
		else 
			rid.set(-1, -1);
		return ret;
	}

	bool satisfy() {
		if(!curData) return false;
		char* pData = ((char*)curData) + attrOff;
		int tmp = compareAttr(pData, value, attrType, attrLen);
		if (op == EQ) return tmp == 0;
		if (op == GE) return tmp >= 0;
		if (op == LE) return tmp <= 0;
		if (op == GT) return tmp > 0;
		if (op == LT) return tmp < 0;
		if (op == NE) return tmp != 0;
		if (op == NO_OP) return true;
	}



	bool GetNextRec(Record &rec) {

	}
	bool CloseScan();
};