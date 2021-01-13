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
#include "../utils/errorHandler.h"
using namespace std;

struct AttrInfo {
	string attrName;
	int attrLen;
	AttrType attrType;
	int offset;

	bool hasIndex;
	bool isNotNULL;

	void* defaultValue;


	friend ostream &operator<<(ostream &out, const AttrInfo &attr) { 
        out << attr.attrName << endl;
		out << attr.attrLen << endl;
		// out << AttrType2Str(attr.attrType) << endl;
		int temp = attr.attrType;
		out << temp << endl;
		out << attr.offset << endl;
		out << attr.hasIndex << endl;
		out << attr.isNotNULL << endl;

		
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
        return in;
	}
};

struct Condition {
    int offset;
    AttrType attrType;
    int attrLen;
    CompareOP op;
	char *value = nullptr;

    bool isValue = true;
    int rhsOff = -1;

    Condition() {}
    ~Condition() {
        // if(this->isValue && this->value)
        //     delete [] this->value;
        // this->value = nullptr;
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

        if(value[0] == 1) {
            if(attr[0] == 1 && op == EQ_OP) return true;
            if(attr[0] != 1 && op == NE_OP) return true;
            return false;
        }
        if(attr[0] == 1) return false;
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
    bool satisfy(void *pData, void *rhsData = nullptr) {
        for(int i = 0; i < conds.size(); ++i) {
            if(!conds[i].satisfy(pData, rhsData)) return false;
        }
        return true;
    }
};

struct multiCol {
    vector<int> idVec;
    bool eq(const multiCol& rhs) {
        if(idVec.size() != rhs.idVec.size()) return false;
        for(int i = 0; i < idVec.size(); ++i) {
            if(idVec[i] != rhs.idVec[i]) return false;
        }
        return true;
    }
    friend ostream &operator<<(ostream &out, const multiCol& t) { 
        out << t.idVec.size() << endl;
        for(auto i: t.idVec) {
            out << i << endl;
        }
        return out;            
    }
    friend istream &operator>>(istream &in, multiCol& t) {
		int size;
        in >> size;
        for(int i = 0; i < size; ++i) {
            int tmp;
            in >> tmp;
            t.idVec.push_back(tmp);
        }
        return in;
	}
    
};


class Table {
    public:
	string tableName;
	int attrNum;
	int recordSize;

	vector<AttrInfo> attrVec;
	
    
    string pkName = "pk";
    multiCol primaryKey;
    
    vector<string> idxNameVec;
    vector<multiCol> indexVec;
    
    vector<string> fkNameVec;
    vector<multiCol > foreignKeyVec; 
    vector<string > refTableVec;
    vector<multiCol > refColVec;


	

	RM_RecordManager* rm = nullptr;
	IX_IndexManager* ix = nullptr;

    string stringfy(multiCol &m) {
        string tmp = "(";
        for (auto i: m.idVec) {
            tmp += attrVec[i].attrName + ", ";
        }
        tmp[tmp.length() - 2] = ')';
        return tmp;
    }

    friend ostream &operator<<(ostream &out, const Table &table) { 
        out << table.tableName << endl;
        out << table.attrNum << endl;
        out << table.recordSize << endl;
        for(auto &attr: table.attrVec) {
            out << attr;
        }
        out << table.pkName << endl;
        out << table.primaryKey;

        out << table.idxNameVec.size() << endl;
        for(auto &s: table.idxNameVec) {
            out << s << endl;
        }

        out << table.indexVec.size() << endl;
        for(auto &s: table.indexVec) {
            out << s;
        }

        out << table.fkNameVec.size() << endl;
        for(auto &s: table.fkNameVec) {
            out << s << endl;
        }

        out << table.foreignKeyVec.size() << endl;
        for(auto &s: table.foreignKeyVec) {
            out << s;
        }

        out << table.refTableVec.size() << endl;
        for(auto &s: table.refTableVec) {
            out << s << endl;
        }

        out << table.refColVec.size() << endl;
        for(auto &s: table.refColVec) {
            out << s;
        }

        return out;            
    }

	friend istream &operator>>(istream &in, Table &table) {
		in >> table.tableName ;
        in >> table.attrNum ;

        in >> table.recordSize ;
        for(int i = 0; i < table.attrNum; ++i) {
            AttrInfo attr;
            in >> attr;
            table.attrVec.push_back(attr);
        }

        in >> table.pkName;
        in >> table.primaryKey;
        int size;

        in >> size ;
        for(int i = 0; i < size; ++i) {
            string tmp;
            in >> tmp;
            table.idxNameVec.push_back(tmp);
        }

        in >> size ;
        for(int i = 0; i < size; ++i) {
            multiCol tmp;
            in >> tmp;
            table.indexVec.push_back(tmp);
        }

        in >> size ;
        for(int i = 0; i < size; ++i) {
            string tmp;
            in >> tmp;
            table.fkNameVec.push_back(tmp);
        }

        in >> size ;
        for(int i = 0; i < size; ++i) {
            multiCol tmp;
            in >> tmp;
            table.foreignKeyVec.push_back(tmp);
        }
        in >> size ;
        for(int i = 0; i < size; ++i) {
            string tmp;
            in >> tmp;
            table.refTableVec.push_back(tmp);
        }

        in >> size ;
        for(int i = 0; i < size; ++i) {
            multiCol tmp;
            in >> tmp;
            table.refColVec.push_back(tmp);
        }
        return in;
	}


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


    int findFirstWithIndex(Conditions& conds, Condition &ret) {
        for(auto& cond: conds.conds) {
            if(!cond.isValue) continue;
            for(int i = 0; i < attrVec.size(); ++i) {
                if(attrVec[i].offset == cond.offset && attrVec[i].hasIndex) {
                    ret = cond;
                    return i;
                }
            }
        }
        return -1;
    }



    bool createIndex(string& attr, bool primary, RM_FileHandle* fh) {
        int attrID = findAttr(attr);
        if(attrID == -1) {
            ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_NOT_EXIST);
            ErrorHandler::instance().push_arg(attr);
            return false;
        }
        AttrInfo& attrInfo = attrVec[attrID];

        if(attrInfo.hasIndex) return true;
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
            char* pData = ((char*)data) + attrInfo.offset;

            ih->insertEntry(pData, rid);
        }
        delete [] data;
        delete scan;
        delete ih;

        ix->closeIndex(indexID);
        return true;
    }

    bool dropIndex(string &attr) {

        int attrID = findAttr(attr);
        if(attrID == -1) {
            ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_NOT_EXIST);
            ErrorHandler::instance().push_arg(attr);
            ErrorHandler::instance().push_arg(tableName);
            return false;
        }
        if(attrVec[attrID].hasIndex == false) {
            ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_HAS_NOT_INDEX);
            ErrorHandler::instance().push_arg(attr);
            ErrorHandler::instance().push_arg(tableName);
        }
        attrVec[attrID].hasIndex = false;
        ix->destroyIndex(tableName.c_str(), attrID);

        return true;
    }

    bool addPrimaryKey(string& pk, vector<string> attrs, RM_FileHandle* fh) {
        
        if(primaryKey.idVec.size() > 0) {
            ErrorHandler::instance().set_error_code(RC::ERROR_PRIMARYKEY_EXIST);
            ErrorHandler::instance().push_arg(tableName);
            return false;
        }

        this->pkName = pk;

        for(auto &attr: attrs) {
            int attrID = findAttr(attr);
            if(attrID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_NOT_EXIST);
                ErrorHandler::instance().push_arg(attr);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            primaryKey.idVec.push_back(attrID);

            attrVec[attrID].isNotNULL = true;
            bool ret = createIndex(attr, false, fh);
            if(!ret) {
                primaryKey.idVec.clear();
                return false;
            }
        }
        
        return true;
    }

    bool dropPrimaryKey(string& pk, bool checkName = false) {
        if(primaryKey.idVec.size() == 0) {
            ErrorHandler::instance().set_error_code(RC::ERROR_PRIMARYKEY_NOT_EXIST);
            ErrorHandler::instance().push_arg(tableName);
            return false;
        }
        if(checkName && pk != pkName) {
            ErrorHandler::instance().set_error_code(RC::ERROR_PRIMARYKEY_WRONG_PKNAME);
            ErrorHandler::instance().push_arg(pk);
            ErrorHandler::instance().push_arg(pkName);
            ErrorHandler::instance().push_arg(tableName);
            return false;
        }

        primaryKey.idVec.clear();
        return true;

    }

    bool checkValidRecord(void* pData, RM_FileHandle* fh) {
        // return true;
        for(int i = 0; i < attrNum; ++i) {
            char* attr = (char*)pData + attrVec[i].offset;

            if(attrVec[i].isNotNULL && attr[0] != 0) {
                ErrorHandler::instance().set_error_code(RC::ERROR_NOT_NULL_CONFLICT);
                ErrorHandler::instance().push_arg(attrVec[i].attrName);
                return false;
            }
        }
        bool ret = checkPrimaryKey(pData, fh);
        if(!ret) {
            cout << "ERROR: Multiple Primary Key" << endl;
        }
        return ret;
    }

    bool checkPrimaryKey(void* pData, RM_FileHandle* fh) {
        if(primaryKey.idVec.size() == 0) return true;
        return !checkMultiColExist(pData, primaryKey, fh);
    }


    bool checkMultiColExist(void* pData, multiCol& cols, RM_FileHandle* fh) {
        Conditions conds;
        for(auto id: cols.idVec) {
            Condition cond;
           
            AttrInfo& attr = attrVec[id];
            char *value = (char*) pData + attr.offset;
            cond.set(attr.offset, attr.attrType, attr.attrLen, EQ_OP, value, true, -1);
            conds.addCond(cond);
        }

        vector<RID> rids;
        selectRIDs(rids, conds, fh);
        return rids.size() > 0;
    }

    bool insertRecord(void* pData, RM_FileHandle* fh) {
        if(!checkValidRecord(pData, fh)) return false;
        
        RID rid;
        bool ret = fh->insertRecord((uint*)pData, rid);
        if(!ret) return false;

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
        ix->closeIndex(indexID);
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
        ix->closeIndex(indexID);
        delete ih;
        return ret;
    }

    bool checkRecordIndexExist(void* attr, int attrID) {
        int indexID;
        ix->openIndex(tableName.c_str(), attrID, indexID);
        IX_IndexHandle *ih = ix->getIndexHandle(indexID);
        bool ret = ih->checkEntryExist(attr);
        ix->closeIndex(indexID);
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
        if(!checkValidRecord(pdata, fh)) {
            insertRecord(data, fh);
        } else {
            insertRecord(pdata, fh);
        }

        delete [] data;
        return true;
    }



    bool selectRIDs(vector<RID> &retRIDs, Conditions& conds, RM_FileHandle* fh) {
        // for(int i = 0;)

        
        Condition cond;
        int first = findFirstWithIndex(conds, cond);
        // int first = -1;
        // first = -1;
        // cout << first << endl;
        if(first != -1) {
            int indexID = 0;
            ix->openIndex(tableName.c_str(), first, indexID);
            IX_IndexHandle* ih = ix->getIndexHandle(indexID);

            IX_IndexScan* scan = new IX_IndexScan();
            scan->openScan(ih, cond.op, cond.value);


            uint *data = new uint[fh->fileConfig.recordSize];
            RID rid;
            
            while(true) {
                if(!scan->next(rid)) break;
                fh->getRecord(rid, data);

                if(conds.satisfy(data)) {
                    retRIDs.push_back(rid);
                } 
            }
            delete [] data;
            ix->closeIndex(indexID);
            delete ih;
            delete scan;

            return true;

        } else {

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
    }


    string stringfy(RID rid, RM_FileHandle* fh, vector<int> offs) {
        uint *data = new uint[fh->fileConfig.recordSize];
        // cout << rid.pageID << " " << rid.slotID << endl;
        fh->getRecord(rid, data);
        // cout << "stringfy " << ((char*)data)[4] << endl;
        string ret = "| ";

        if(offs.size() == 0) {
            for(int i = 0; i < attrNum; ++i) {
                char* attr = (char*)data + attrVec[i].offset;
                ret += Attr2Str(attr, attrVec[i].attrType, attrVec[i].attrLen);
                ret += " | ";
            }
        } else {
            for(auto i : offs) {
                char* attr = (char*)data + attrVec[i].offset;
                ret += Attr2Str(attr, attrVec[i].attrType, attrVec[i].attrLen);
                ret += " | ";
            }
        }
        // ret += "\n";
        delete [] data;
        return ret;

    }


    bool convertAttrToID(vector<string>& attrs, vector<int>& ret) {
        for(auto &name: attrs) {
            int id = findAttr(name);
            if(id == -1) {
                cout << "Column '" << name << "' Not Exists" << endl;
                return false;
            }
            ret.push_back(id);
        }
        return true;
    }

    // void showTable() {
    //     for(int i = 0; i < attrVec.size(); ++i) {

    //     }
    // }
    











    

    int findAttr(const string& attr) {

        for(int i = 0; i < attrNum; ++i) {
            if(attrVec[i].attrName == attr) {
                return i;
            }
        }
        return -1;
    }
};