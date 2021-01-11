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

#include <iomanip> 

using namespace std;

class SM_SystemManager {
    public:
        DBConfig dbConfig;
        map<string, int> fileIDMap;
        map<string, int> indexIDMap;

        RM_RecordManager *rm;
        IX_IndexManager *ix;

    public:
        SM_SystemManager(RM_RecordManager *rm, IX_IndexManager *ix) {
            this->ix = ix;
            this->rm = rm;
        }

        ~SM_SystemManager() {}

        bool openDB(const char *dbName) {
            cout << "www read" << endl;
            chdir(dbName);
            cout << "read " << dbName << endl;
            dbConfig.dbName = string(dbName);
            bool ret = readDBConfigFromMeta();
            if(!ret) return false;
            // cout << "read done" << endl;

            int fileID;
            int indexID;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(!rm->openFile(dbConfig.tableVec[i].tableName.c_str(), fileID))
                    return false;
                fileIDMap[dbConfig.tableVec[i].tableName] = fileID;

              
            }

            for(int i = 0; i < dbConfig.tableNum; ++i) {
                dbConfig.tableVec[i].ix = ix;
                dbConfig.tableVec[i].rm = rm;
            }
            // cout << "success" << endl;
        }               
        bool closeDB() {
            bool ret = writeDBConfigToMeta();
            if(!ret) return false;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(!rm->closeFile(fileIDMap[dbConfig.tableVec[i].tableName]))
                    return false;
            }
            fileIDMap.clear();
            indexIDMap.clear();
            return true;
        }



        bool createTable(Table table) {
            // cout << "create" << endl;

            table.rm = rm;
            table.ix = ix;

            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(dbConfig.tableVec[i].tableName == table.tableName) {
                    cout << "ERROR: Table Already Exists" << endl;
                    return false;
                }
            }
            // cout << "create" << endl;
            dbConfig.tableVec.push_back(table);
            dbConfig.tableNum += 1;
            bool ret = rm->createFile(table.tableName.c_str(), table.recordSize);
            if(!ret) return false;

            // for(int i = 0; i < table.attrNum; ++i) {
            //     if(table.attrVec[i].hasIndex) {
            //         AttrInfo attrInfo = table.attrVec[i];
            //         ix->createIndex(table.tableName.c_str(), i, attrInfo.attrType, attrInfo.attrLen);
            //     }
            // }

            int fileID;
            rm->openFile(table.tableName.c_str(), fileID);
            fileIDMap[table.tableName] = fileID;

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

        bool addPrimaryKey(const string tableName,  vector<string> attrs) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            // cout << "mmmmm" << endl;
            bool ret = dbConfig.tableVec[tableID].addPrimaryKey(attrs, fh);
            // cout << "mmmmm" << endl;
            delete fh;
            return ret;
        }

        bool checkPrimaryKeyNotExist(string tableName, void* pData) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);

            bool ret = dbConfig.tableVec[tableID].checkPrimaryKey(pData, fh);
            delete fh;
            return ret;
        }


        bool checkValidRecord(string tableName, void* pData) {
            return true;
        }

        bool insertIntoTable(string tableName, void* pData) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            if(!checkValidRecord(tableName, pData)) return false;

            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            bool ret = dbConfig.tableVec[tableID].insertRecord(pData, fh);

            delete fh;
            return ret;
        }



        bool selectFromTable(string tableName, Conditions& conds, vector<RID> &ret) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;
            // cout << "wwwwd" << endl;
            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            // cout << "wwwwd2222" << endl;
            // if(!fh) {
            //     cout << "nulll" << endl;
            // }
            dbConfig.tableVec[tableID].selectRIDs(ret, conds, fh);
            // cout << "wwwwd2222" << endl;
            // delete fh;
            return true;
        }

        bool selectFromTableAndPrint(string tableName, Conditions conds) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            vector<RID> rids;
            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            dbConfig.tableVec[tableID].selectRIDs(rids, conds, fh);

            for(int i = 0; i < rids.size(); ++i) {
                cout << dbConfig.tableVec[tableID].stringfy(rids[i], fh, vector<int>()) << endl;
            }
            delete fh;
            return true;
        }

        bool getRecordString(string tableName, vector<RID> &rids, vector<int> printOffs, vector<string>& ret) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;
            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);

            for(int i = 0; i < rids.size(); ++i) {
                ret.push_back(dbConfig.tableVec[tableID].stringfy(rids[i], fh, printOffs));
            }
            return true;
        }



        bool deleteFromTable(string tableName, Conditions conds) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            vector<RID> rids;
            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            dbConfig.tableVec[tableID].selectRIDs(rids, conds, fh);
            dbConfig.tableVec[tableID].deleteRecords(rids, fh);

            delete fh;
            return true;
            
        }

        bool updateTable(string tableName, vector<Condition>& sets, Conditions conds) {
            int tableID = findTable(tableName);
            if(tableID == -1) return false;

            vector<RID> rids;
            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);

            dbConfig.tableVec[tableID].selectRIDs(rids, conds, fh);
            

            for(int i = 0; i < rids.size(); ++i) {
                dbConfig.tableVec[tableID].updateRecord(rids[i], sets, fh);
            }

        }

        void showTables() {
            cout << setw(10) <<"------------" << endl;
            cout <<  "|" << setiosflags(ios::left)<<setw(10) << "TABLES" << "|" << endl;
            cout << setw(10) <<"+----------+" << endl;
            for(int i = 0; i < dbConfig.tableNum; ++i) {

                cout <<  "|" << setiosflags(ios::left)<<setw(10) << dbConfig.tableVec[i].tableName << "|" << endl;
            
            }

            cout << setw(10) <<"------------" << endl;
        }

    

        bool readDBConfigFromMeta() {
            cout << "start read meta" << endl;
            ifstream ism;
            
            ism.open("./meta.db");
            cout << "open meta" << endl;

            // ism >> dbConfig.dbName;
            ism >> dbConfig.tableNum;
            
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                Table table;
                ism >> table;
                dbConfig.tableVec.push_back(table);
            }

            ism.close();

            cout << "read meta" << endl;
            // cout << dbConfig.dbName << endl;
            return true;
        }

        bool writeDBConfigToMeta() {
            ofstream outfile;
            outfile.open("meta.db");
            // outfile << dbConfig.dbName << endl;
            outfile << dbConfig.tableNum << endl;

            for(int i = 0; i < dbConfig.tableNum; ++i) {
                outfile << dbConfig.tableVec[i];
            }
            outfile.close();
            return true;
        }


    
        int findTable(const string tableName) {
            // int ret = -1;
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(dbConfig.tableVec[i].tableName == tableName)
                    return i;
            }
            return -1;
        }

        

};