#pragma once
#include <cstring>
#include <cstdio>
#include "../ix/ix.h"
#include "../rm/rm.h"
#include "utils.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

struct AttrInfo {
	string attrName;
	int attrLen;
	AttrType attrType;
	int offset;

	bool hasIndex;
	bool isNotNULL;
	bool isPrimaryKey;
    bool isForeignKey;

	void* defaultValue;

	string refTable;
	string foreignKeyName;

	friend ostream &operator<<(ostream &out, const AttrInfo &attr) { 
        out << attr.attrName << endl;
		out << attr.attrLen << endl;
		// out << AttrType2Str(attr.attrType) << endl;
		int temp = attr.attrType;
		out << temp << endl;
		out << attr.offset << endl;
		out << attr.hasIndex << endl;
		out << attr.isNotNULL << endl;
		out << attr.isPrimaryKey << endl;


		
        return out;            
    }

	friend istream &operator>>(istream &in, AttrInfo &attr) {
		in >> attr.attrName;
		in >> attr.attrLen;
		int temp;
		in >> temp;
		attr.attrType = (AttrType)temp;
		in >> attr.offset;
		in >> attr.hasIndex;
		in >> attr.isNotNULL;
		in >> attr.isPrimaryKey;
	}
};

struct Condition {
    int offset;
    AttrType attrType;
    int attrLen;
    CompareOP op;
	char *value;

    bool isValue = true;
    int rhsOff = -1;

    Condition() {}
    ~Condition() {
        if(this->isValue)
            delete [] this->value;
        this->value = nullptr;
    }

    Condition(const Condition& rhs) {
        // cout << "copy" << endl;
        this->offset = rhs.offset;
        attrType = rhs.attrType;
        attrLen = rhs.attrLen;
        op = rhs.op;
        isValue = rhs.isValue;
        rhsOff = rhs.rhsOff;
        if(isValue) {
            value = new char[attrLen];
            memcpy(value, rhs.value, attrLen);
        }
    }

    void set(int off, AttrType type, int len, CompareOP op, void* value, bool isValue = true, int rhsOff = -1) {
        offset = off;
        attrType = type;
        attrLen = len;
        this->op = op;

        this->isValue = isValue;
        if (isValue) {
            this->value = new char [len];
            memcpy(this->value, value, len);
        } else {
            this->value = nullptr;
            this->rhsOff = rhsOff;
        }
    }

    bool satisfy(void* pData, void* rhsData = nullptr) {
        // cout << "checking " << offset << endl;
        if (op == NO_OP) return true;
        char* attr = ((char*)pData) + offset;

        if(!this->isValue) {
            if (!rhsData)
                this->value = ((char*)pData) + rhsOff;
            else 
                this->value = ((char*)rhsData) + rhsOff;
        }
        int tmp = compareAttr(attr, value, attrType, attrLen);
        // cout << tmp << endl;
		if (op == EQ_OP) return tmp == 0;
		if (op == GE_OP) return tmp >= 0;
		if (op == LE_OP) return tmp <= 0;
		if (op == GT_OP) return tmp > 0;
		if (op == LT_OP) return tmp < 0;
		if (op == NE_OP) return tmp != 0;
		
    }
};

struct Conditions {
    vector<Condition> conds;

    void addCond(Condition a) {
        conds.push_back(a);
    }
    bool satisfy(void *pData) {
        for(int i = 0; i < conds.size(); ++i) {
            if(!conds[i].satisfy(pData)) return false;
        }
        return true;
    }
};


class Table {
    public:
	string tableName;
	int attrNum;
	int recordSize;

	vector<AttrInfo> attrVec;
	vector<int> primaryIDVec;
	

	RM_RecordManager* rm = nullptr;
	IX_IndexManager* ix = nullptr;


	void init(string name, RM_RecordManager* rm, IX_IndexManager* ix) {
		tableName = name;
		recordSize = 0;
		attrNum = 0;
        this->rm = rm;
        this->ix = ix;

	}

    

	void addAttr(AttrInfo attr) {
		attrVec.push_back(attr);
		attrNum += 1;
		attrVec[attrNum - 1].offset = recordSize;
        attrVec[attrNum - 1].attrLen += 1;

		recordSize += attr.attrLen + 1;
	}




    bool createIndex(const string attr, bool unique, RM_FileHandle* fh) {
        int attrID = findAttr(attr);
        if(attrID == -1) return false;
        AttrInfo attrInfo = attrVec[attrID];

        if(attrInfo.hasIndex) return false;
        attrVec[attrID].hasIndex = true;

        ix->createIndex(tableName.c_str(), attrID, attrInfo.attrType, attrInfo.attrLen);
        int indexID;
        ix->openIndex(tableName.c_str(), attrID, indexID);
        IX_IndexHandle* ih = ix->getIndexHandle(indexID);

        RM_FileScan *scan = new RM_FileScan();
        scan->OpenScan(fh, attrInfo.attrType, attrInfo.attrLen, attrInfo.offset, NO_OP, nullptr);
        
        uint *data = new uint[fh->fileConfig.recordSize];
        RID rid;
        
        while(true) {
            if(!scan->next(data, rid)) break;
            // cout << "insert " << rid.pageID << " " << rid.slotID << endl;
            char* pData = ((char*)data) + attrInfo.offset;

            if(unique && ih->checkEntryExist(pData)) {
                cout << "multiple" << endl;
                delete [] data;
                delete scan;
                delete ih;
                delete fh;
                ix->closeIndex(indexID);
                return false;
            }
            ih->insertEntry(pData, rid);
        }
        delete [] data;
        delete scan;

        delete ih;
        delete fh;

        ix->closeIndex(indexID);
        return true;
    }

    bool dropIndex(const string attr) {

        int attrID = findAttr(attr);
        if(attrID == -1) return false;

        if(attrVec[attrID].hasIndex == false)
            return false;
        attrVec[attrID].hasIndex = false;
        ix->destroyIndex(tableName.c_str(), attrID);

        return true;
    }

    bool addPrimaryKey(const string attr, RM_FileHandle* fh) {
        int attrID = findAttr(attr);
        if(attrID == -1) return false;

        if(primaryIDVec.size() > 0) return false;

        AttrInfo attrInfo = attrVec[attrID];
        primaryIDVec.push_back(attrID);
        attrVec[attrID].isPrimaryKey = true;


        
        bool ret = createIndex(attr, true, fh);
        if(!ret) {
            primaryIDVec.clear();
            attrVec[attrID].isPrimaryKey = false;
        }
        return ret;
    }

    bool dropPrimaryKey() {}

    bool checkValidRecord(void* pData) {
        return true;
        for(int i = 0; i < attrNum; ++i) {
            char* attr = (char*)pData + attrVec[i].offset;

            if(attrVec[i].isNotNULL && attr[0] != 0) {
                cout << "insert NULL to notNULL" << endl;
                return false;
            }

            if(attrVec[i].isPrimaryKey) {
                if(checkRecordIndexExist(attr, i)) {
                    cout << "Primary Key Repeat" << endl;
                    return false;
                }
            }
        }
        return true;
    }

    bool insertRecord(void* pData, RM_FileHandle* fh) {
        if(!checkValidRecord(pData)) return false;
        
        RID rid;
        bool ret = fh->insertRecord((uint*)pData, rid);
        if(!ret) return false;

        // cout << "fh insert done" << endl;
        for(int i = 0; i < attrNum; ++i) {
            char* attr = (char*)pData + attrVec[i].offset;

            if(attrVec[i].hasIndex) {
                insertRecordIndex(attr, rid, i);
            }
        }
        return true;
    }

    bool insertRecordIndex(void* attr, RID rid, int attrID) {
        int indexID;
        ix->openIndex(tableName.c_str(), attrID, indexID);
        IX_IndexHandle *ih = ix->getIndexHandle(indexID);

        bool ret = ih->insertEntry(attr, rid);
        delete ih;
        return ret;
    }

    bool deleteRecord(RID rid, RM_FileHandle* fh) {
        char* data = new char [recordSize];
        fh->getRecord(rid, (uint*)data);

        for(int i = 0; i < attrNum; ++i) {
            char* attr = data + attrVec[i].offset;

            if(attrVec[i].hasIndex) {
                deleteRecordIndex(attr, rid, i);
            }
        }  
        fh->deleteRecord(rid);
        delete [] data;
        return true;   
    }

    bool deleteRecordIndex(void* attr, RID rid, int attrID) {
        int indexID;
        ix->openIndex(tableName.c_str(), attrID, indexID);
        IX_IndexHandle *ih = ix->getIndexHandle(indexID);

        bool ret = ih->deleteEntry(attr, rid);
        delete ih;
        return ret;
    }

    bool checkRecordIndexExist(void* attr, int attrID) {
        int indexID;
        ix->openIndex(tableName.c_str(), attrID, indexID);
        IX_IndexHandle *ih = ix->getIndexHandle(indexID);
        bool ret = ih->checkEntryExist(attr);
        delete ih;
        return ret;
    }

    bool insertRecords(vector<void*> pData, int fileID) {
        RM_FileHandle *fh = rm->getFileHandle(fileID);
        RID rid;
        bool ret = true;
        for(int i = 0; i < pData.size(); ++i) {
            ret = fh->insertRecord((uint*)(pData[i]), rid);
            if(!ret) {
                break;
            }
        }
        delete fh;
        return ret;
    }

    bool deleteRecords(vector<RID> rid, RM_FileHandle* fh) {
        bool ret = true;
        for(int i = 0; i < rid.size(); ++i) {
            ret = deleteRecord(rid[i], fh);
            if(!ret) {
                break;
            }
        }
        return ret;
    }

    bool updateRecord(RID rid, vector<Condition>& sets, RM_FileHandle* fh) {
        char* data = new char [recordSize];
        char* pdata = new char [recordSize];
        fh->getRecord(rid, (uint*)data);
        
        memcpy(pdata, data, recordSize);

        for(int i = 0; i < sets.size(); ++i) {
            memcpy(pdata + sets[i].offset, sets[i].value, sets[i].attrLen);
        }


        deleteRecord(rid, fh);
        if(!checkValidRecord(pdata)) {
            insertRecord(data, fh);
        } else {
            insertRecord(pdata, fh);
        }

        delete [] data;
        return true;
    }



    bool selectRIDs(vector<RID> &retRIDs, Conditions conds, RM_FileHandle* fh) {
        // for(int i = 0;)

        RM_FileScan *scan = new RM_FileScan();
        scan->OpenScan(fh, AttrType::STRING_TYPE, 0, 0, NO_OP, nullptr);

        uint *data = new uint[fh->fileConfig.recordSize];
        RID rid;
        while(true) {
            if(!scan->next(data, rid)) break;
            if(conds.satisfy(data)) {
                retRIDs.push_back(rid);
                // cout << "satis " << rid.slotID << endl;
            }
        }
        delete [] data;
        return true;
    }


    string stringfy(RID rid, RM_FileHandle* fh) {
        uint *data = new uint[fh->fileConfig.recordSize];
        // cout << rid.pageID << " " << rid.slotID << endl;
        fh->getRecord(rid, data);
        // cout << "stringfy " << ((char*)data)[4] << endl;
        string ret = "| ";
        for(int i = 0; i < attrNum; ++i) {
            char* attr = (char*)data + attrVec[i].offset;
            ret += Attr2Str(attr, attrVec[i].attrType, attrVec[i].attrLen);
            ret += " | ";
        }
        // ret += "\n";
        delete [] data;
        return ret;

    }

    // void showTable() {
    //     for(int i = 0; i < attrVec.size(); ++i) {

    //     }
    // }
    











    

    int findAttr(const string attr) {

        for(int i = 0; i < attrNum; ++i) {
            if(attrVec[i].attrName == attr) {
                return i;
            }
        }
        return -1;
    }
};