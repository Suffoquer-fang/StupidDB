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
	BufType curBuf;

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
	}

	bool next() {

	}

	bool satisfy() {
		
	}



	bool GetNextRec(Record &rec) {

	}
	bool CloseScan();
};