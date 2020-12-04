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

class SM_SystemManager {
    private:
        DBConfig dbConfig;
        map<string, int> fileIDMap;

        RM_RecordManager *rm;
        IX_IndexManager *ix;

    public:
        SM_SystemManager(RM_RecordManager *rm, IX_IndexManager *ix) {
            this->ix = ix;
            this->rm = rm;
        }

        ~SM_SystemManager() {}

        bool openDB(const char *dbName) {
            cout << "openDB" << endl;
            chdir(dbName);
            cout << "read ";
            bool ret = readDBConfigFromMeta();
            if(!ret) return false;

            int fileID;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(!rm->openFile(dbConfig.tableVec[i].tableName.c_str(), fileID))
                    return false;
                fileIDMap[dbConfig.tableVec[i].tableName] = fileID;
            }
        }               
        bool closeDB() {
            bool ret = writeDBConfigToMeta();
            if(!ret) return false;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(!rm->closeFile(fileIDMap[dbConfig.tableVec[i].tableName]))
                    return false;
            }
            fileIDMap.clear();
            return true;
        }              

        bool createTable(Table table) {
            cout << "create" << endl;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(dbConfig.tableVec[i].tableName == table.tableName) {
                    return false;
                }
            }
            // cout << "create" << endl;
            dbConfig.tableVec.push_back(table);
            dbConfig.tableNum += 1;
            bool ret = rm->createFile(table.tableName.c_str(), table.recordSize);
            if(!ret) return false;

            for(int i = 0; i < table.attrNum; ++i) {
                if(table.attrVec[i].hasIndex) {
                    AttrInfo attrInfo = table.attrVec[i];
                    ix->createIndex(table.tableName.c_str(), i, attrInfo.attrType, attrInfo.attrLen);
                }
            }
            return true;
        }



        bool dropTable(const string tableName) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            rm->destroyFile(tableName.c_str());
            Table table = dbConfig.tableVec[tableID];

            for(int i = 0; i < table.attrNum; ++i) {
                if(table.attrVec[i].hasIndex) {
                    ix->destroyIndex(tableName.c_str(), i);
                }
            }

            dbConfig.tableVec.erase(dbConfig.tableVec.begin() + tableID);
            dbConfig.tableNum -= 1;
            return true;
        }   

        bool createIndex (const string tableName, const string attr) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            int attrID = findAttrFromTable(attr, tableID);
            if(attrID == -1) return false;

            AttrInfo attrInfo = dbConfig.tableVec[tableID].attrVec[attrID];

            if(attrInfo.hasIndex) return false;
            dbConfig.tableVec[tableID].attrVec[attrID].hasIndex = true;

            int fileID = fileIDMap[tableName];
            RM_FileHandle* fh = rm->getFileHandle(fileID);

            
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
            delete fh;

            ix->closeIndex(indexID);
            return true;

        }


        bool dropIndex(const string tableName, const string attr) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            int attrID = findAttrFromTable(attr, tableID);
            if(attrID == -1) return false;

            if(dbConfig.tableVec[tableID].attrVec[attrID].hasIndex == false)
                return false;
            dbConfig.tableVec[tableID].attrVec[attrID].hasIndex = false;
            ix->destroyIndex(tableName.c_str(), attrID);

            return true;
        }
        

        bool readDBConfigFromMeta() {
            cout << "read ";
            ifstream ism;
            
            ism.open("meta.db");
            ism >> dbConfig.dbName;
            ism >> dbConfig.tableNum;

            for(int i = 0; i < dbConfig.tableNum; ++i) {
                Table table;
                ism >> table.tableName;
                ism >> table.attrNum;
                ism >> table.recordSize;

                for(int j = 0; j < table.attrNum; ++j) {
                    AttrInfo attrInfo;
                    ism >> attrInfo.attrName;
                    ism >> attrInfo.attrLen;

                    string tmp;
                    ism >> tmp;
                    if(tmp == "INTEGER") {
                        attrInfo.attrType = INTEGER;
                    } else if(tmp == "FLOAT") {
                        attrInfo.attrType = FLOAT;
                    } else {
                        attrInfo.attrType = STRING;
                    }
                    ism >> attrInfo.offset;

                    ism >> tmp;
                    attrInfo.hasIndex = tmp != "NOT";

                    table.attrVec.push_back(attrInfo);
                }
                dbConfig.tableVec.push_back(table);
            }

            ism.close();

            cout << "read ";
            cout << dbConfig.dbName << endl;
        }

        bool writeDBConfigToMeta() {
            ofstream outfile;
            outfile.open("meta.db");
            outfile << dbConfig.dbName << endl;
            outfile << dbConfig.tableNum << endl;

            for(int i = 0; i < dbConfig.tableNum; ++i) {
                Table table = dbConfig.tableVec[i];
                outfile << table.tableName << endl;
                outfile << table.attrNum << endl;
                outfile << table.recordSize << endl;

                for(int j = 0; j < table.attrNum; ++j) {
                    
                    outfile << stringfy(table.attrVec[j]);
                }
            }
            outfile.close();
        }

        string stringfy(AttrInfo attrInfo) {
            string ret = "";
            ret += attrInfo.attrName + "\n";
            ret += to_string(attrInfo.attrLen) + "\n";

            if(attrInfo.attrType == INTEGER) {
                ret += "INTEGER\n";
            } else if(attrInfo.attrType == FLOAT) {
                ret += "FLOAT\n";
            } else 
                ret += "STRING\n";

            ret += to_string(attrInfo.offset) + "\n";
            ret += attrInfo.hasIndex ? "INDEX\n" : "NOT\n";
            return ret;
        }

        

        int findTable(const string tableName) {
            // int ret = -1;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(dbConfig.tableVec[i].tableName == tableName)
                    return i;
            }
            return -1;
        }

        int findAttrFromTable(const string attr, int tableID) {
            Table table = dbConfig.tableVec[tableID];

            for(int i = 0; i < table.attrNum; ++i) {
                if(table.attrVec[i].attrName == attr) {
                    return i;
                }
            }
            return -1;
        }

};