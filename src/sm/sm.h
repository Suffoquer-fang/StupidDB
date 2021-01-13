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


#include <dirent.h>
#include <iomanip> 
#include "../utils/errorHandler.h"
#include "../utils/formatPrinter.h"

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

        ~SM_SystemManager() {
            cout << "CLOSE" << endl;
            closeDB();
        }

        bool openDB(const char *dbName) {
            if(chdir(dbName) != 0) {
                ErrorHandler::instance().set_error_code(RC::ERROR_DB_NOT_EXIST);
                ErrorHandler::instance().push_arg(string(dbName));
                return false;
            }
            dbConfig.dbName = string(dbName);
            bool ret = readDBConfigFromMeta();
            if(!ret) return false;

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
            return true;
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



        bool createTable(Table &table) {

            table.rm = rm;
            table.ix = ix;

            for(int i = 0; i < dbConfig.tableNum; ++i) {
                if(dbConfig.tableVec[i].tableName == table.tableName) {
                    ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_ALREADY_EXIST);
                    ErrorHandler::instance().push_arg(table.tableName);
                    return false;
                }
            }
            dbConfig.tableVec.push_back(table);
            dbConfig.tableNum += 1;
            bool ret = rm->createFile(table.tableName.c_str(), table.recordSize);
            if(!ret) return false;

            int fileID;
            rm->openFile(table.tableName.c_str(), fileID);
            fileIDMap[table.tableName] = fileID;

            return true;
        }



        bool dropTable(string &tableName) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

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

        bool alterAddCol(string tableName, AttrInfo &attr) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            Table &temp = dbConfig.tableVec[tableID];
            int attrID = temp.findAttr(attr.attrName);
            if(attrID != -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_CLOUMN_ALREARY_EXIST);
                ErrorHandler::instance().push_arg(attr.attrName);
                return false;
            }

            // return true;

            int fileID = fileIDMap[tableName];
            RM_FileHandle* old_fh = rm->getFileHandle(fileID);
            
            Table newTable = dbConfig.tableVec[tableID];
            newTable.addAttr(attr);

            int newFileID;

            rm->createFile((tableName + "-temp").c_str(), newTable.recordSize);
            rm->openFile((tableName + "-temp").c_str(), newFileID);

            RM_FileHandle* new_fh = rm->getFileHandle(newFileID);

            uint* data = new uint[new_fh->fileConfig.recordSize];

            RM_FileScan oldScan;
            RID rid;
            oldScan.OpenScan(old_fh, STRING_TYPE, 0, 0, NO_OP, nullptr);
            while(true) {
                if(!oldScan.next(data)) break;
                char *attr = (char*)data + temp.recordSize;
                attr[0] = 1;
                new_fh->insertRecord(data, rid);
            }

            fileIDMap[tableName] = newFileID;
            rm->destroyFile(tableName.c_str());

            for(int i = 0; i < temp.attrNum; ++i) {
                if(temp.attrVec[i].hasIndex) {
                    ix->destroyIndex(tableName.c_str(), i);
                }
            }

            rename((tableName + "-temp").c_str(), tableName.c_str());
            dbConfig.tableVec[tableID] = newTable;

            delete [] data;
            delete old_fh;
            delete new_fh;

            return true;
        }


        bool createIndex(string &tableName, string &idxName, vector<string>& attrs) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }
            Table &temp = dbConfig.tableVec[tableID];
            multiCol new_idx;
            for(auto col: attrs) {
                int attrID = dbConfig.tableVec[tableID].findAttr(col);
                if(attrID == -1) {
                    ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_NOT_EXIST);
                    ErrorHandler::instance().push_arg(col);
                    return false;
                }
                new_idx.idVec.push_back(attrID);
            }

            for(auto name: temp.idxNameVec) {
                if(name == idxName) {
                    ErrorHandler::instance().set_error_code(RC::ERROR_INDEX_ALREADY_EXIST);
                    ErrorHandler::instance().push_arg(name);
                    return false;
                }
            }

            temp.indexVec.push_back(new_idx);
            temp.idxNameVec.push_back(idxName);

            int fileID = fileIDMap[tableName];
            RM_FileHandle* fh = rm->getFileHandle(fileID);
            for (auto& col: attrs) {
                temp.createIndex(col, false, fh);
            }

            delete fh;
            return true;
        }

        bool addPrimaryKey(string &tableName,  string &pkName, vector<string> &attrs) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            bool ret = dbConfig.tableVec[tableID].addPrimaryKey(pkName, attrs, fh);
            delete fh;
            return ret;
        }

        bool dropPrimaryKey(string &tableName, string &pkName, bool check) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            bool ret = dbConfig.tableVec[tableID].dropPrimaryKey(pkName, check);
            return ret;
        }



        bool checkPrimaryKeyNotExist(string tableName, void* pData) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

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
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            if(!checkValidRecord(tableName, pData)) return false;

            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            bool ret = dbConfig.tableVec[tableID].insertRecord(pData, fh);

            delete fh;
            return ret;
        }



        bool selectFromTable(string tableName, Conditions& conds, vector<RID> &rids) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);
            
            bool ret = dbConfig.tableVec[tableID].selectRIDs(rids, conds, fh);
            
            return ret;
        }

        // bool selectFromTableAndPrint(string tableName, Conditions conds) {
        //     int tableID = findTable(tableName);
        //     if(tableID == -1) return false;

        //     vector<RID> rids;
        //     int fileID = fileIDMap[tableName];
        //     RM_FileHandle *fh = rm->getFileHandle(fileID);
        //     dbConfig.tableVec[tableID].selectRIDs(rids, conds, fh);

        //     for(int i = 0; i < rids.size(); ++i) {
        //         cout << dbConfig.tableVec[tableID].stringfy(rids[i], fh, vector<int>()) << endl;
        //     }
        //     delete fh;
        //     return true;
        // }

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
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

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
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            vector<RID> rids;
            int fileID = fileIDMap[tableName];
            RM_FileHandle *fh = rm->getFileHandle(fileID);

            dbConfig.tableVec[tableID].selectRIDs(rids, conds, fh);
            

            for(int i = 0; i < rids.size(); ++i) {
                dbConfig.tableVec[tableID].updateRecord(rids[i], sets, fh);
            }

        }

        void showTables() {
            FormatPrinter::set_blue();
            FormatPrinter::instance().setLineWidth(10);
            FormatPrinter::instance().printHeaderLine();
            FormatPrinter::instance().printString("TABLES", -1, 1, 1, 1, 1);
            FormatPrinter::instance().printMidLine();
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                FormatPrinter::instance().printString(dbConfig.tableVec[i].tableName, -1, 1, 1, 1, 1);
            }

            FormatPrinter::instance().printHeaderLine();
        }

    

        bool readDBConfigFromMeta() {
            ifstream ism;
            
            ism.open("./meta.db");

            ism >> dbConfig.tableNum;
            
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                Table table;
                ism >> table;
                dbConfig.tableVec.push_back(table);
            }

            ism.close();

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


        bool renameTable(string oldName, string newName) {
            int tableID = findTable(oldName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(oldName);
                return false;
            }

            if(findTable(newName) != -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(newName);
                return false;
            }

            dbConfig.tableVec[tableID].tableName = newName;
            
            for(int i = 0; i < dbConfig.tableNum; ++i) {
                Table &temp = dbConfig.tableVec[i];
                for(auto &t: temp.refTableVec) {
                    if (t == oldName)
                        t = newName;
                }
            }

            fileIDMap[newName] = fileIDMap[oldName];
            rename(oldName.c_str(), newName.c_str());
            rename((oldName + ".*").c_str(), (newName + ".*").c_str());
            return true;
        }

        

};