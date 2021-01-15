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


            rm->closeFile(fileID);

            rename((tableName + "-temp").c_str(), tableName.c_str());
            dbConfig.tableVec[tableID] = newTable;

            for(int i = 0; i < newTable.attrNum; ++i) {
                if(newTable.attrVec[i].hasIndex) {
                    FormatPrinter::debug("create index " + newTable.attrVec[i].attrName);
                    dbConfig.tableVec[tableID].attrVec[i].hasIndex = false;
                    dbConfig.tableVec[tableID].createIndex(newTable.attrVec[i].attrName, false, new_fh);
                }
            }



            delete [] data;
            delete old_fh;
            delete new_fh;

            return true;
        }

        bool alterDropCol(string tableName, string colName) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }

            Table &temp = dbConfig.tableVec[tableID];
            int attrID = temp.findAttr(colName);
            if(attrID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_NOT_EXIST);
                ErrorHandler::instance().push_arg(colName);
                return false;
            }

            //check other foreignkey
            if(temp.primaryKey.contains(attrID)) {
                for(auto &table: dbConfig.tableVec) {
                    for(auto &name: table.refTableVec) {
                        if(name == tableName) {
                            ErrorHandler::instance().set_error_code(RC::ERROR_DROP_REF_COLUMN);
                            ErrorHandler::instance().push_arg(colName);
                            ErrorHandler::instance().push_arg(name);
                            return false;
                        }
                    }
                }
            }




            int fileID = fileIDMap[tableName];
            RM_FileHandle* old_fh = rm->getFileHandle(fileID);
            
            Table newTable;
            newTable.init(tableName, rm, ix);
            for(int i = 0; i < temp.attrNum; ++i) {
                if(i == attrID) continue;
                newTable.addAttr(temp.attrVec[i]);
            }
            
            if(!temp.primaryKey.contains(attrID)) {
                newTable.primaryKey = temp.primaryKey;
                for(auto& i: newTable.primaryKey.idVec) {
                    if(i > attrID) i -= 1;
                }
            }



            for(int i = 0; i < temp.foreignKeyVec.size(); ++i) {
                if(temp.foreignKeyVec[i].contains(attrID)) continue;
                newTable.fkNameVec.push_back(temp.fkNameVec[i]);
                multiCol tempMultiCol = temp.foreignKeyVec[i];
                for(auto &t: tempMultiCol.idVec) {
                    if(t > attrID) t -= 1;
                }
                newTable.foreignKeyVec.push_back(tempMultiCol);
            }

            for(int i = 0; i < temp.idxNameVec.size(); ++i) {
                if(temp.indexVec[i].contains(attrID)) continue;
                newTable.idxNameVec.push_back(temp.idxNameVec[i]);
                multiCol tempMultiCol = temp.indexVec[i];
                for(auto &t: tempMultiCol.idVec) {
                    if(t > attrID) t -= 1;
                }
                newTable.indexVec.push_back(tempMultiCol);
            }

            for(auto &table: dbConfig.tableVec) {
                for(int i = 0; i < table.foreignKeyVec.size(); ++i) {
                    if(table.fkNameVec[i] == tableName) {
                        for(auto &t: table.foreignKeyVec[i].idVec) {
                            if(t > attrID) t -= 1;
                        }
                    }
                }
            }


            int newFileID;

            rm->createFile((tableName + "-temp").c_str(), newTable.recordSize);
            rm->openFile((tableName + "-temp").c_str(), newFileID);

            RM_FileHandle* new_fh = rm->getFileHandle(newFileID);

            uint* data = new uint[new_fh->fileConfig.recordSize];
            uint* old_data = new uint[old_fh->fileConfig.recordSize];
            RM_FileScan oldScan;
            RID rid;
            oldScan.OpenScan(old_fh, STRING_TYPE, 0, 0, NO_OP, nullptr);
            while(true) {
                if(!oldScan.next(old_data)) break;
                for(int i = 0; i < newTable.attrNum; ++i) {
                    int old_id = i < attrID ? i : i + 1;
                    char* old_attr = (char*)old_data + temp.attrVec[old_id].offset;
                    char* new_attr = (char*)data + newTable.attrVec[i].offset;
                    memcpy(new_attr, old_attr, newTable.attrVec[i].attrLen);
                }

                // cout << "debug" << endl;
                // for(int i = 0; i < temp.recordSize; ++i) {
                //     cout << ((char*)old_data)[i] - '\0' << " ";
                // }
                // cout << endl;
                // for(int i = 0; i < newTable.recordSize; ++i) {
                //     cout << ((char*)data)[i] - '\0' << " ";
                // }
                // cout << endl;


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

            for(int i = 0; i < newTable.attrNum; ++i) {
                if(newTable.attrVec[i].hasIndex) {
                    dbConfig.tableVec[tableID].attrVec[i].hasIndex = false;
                    dbConfig.tableVec[tableID].createIndex(newTable.attrVec[i].attrName, false, new_fh);
                }
            }


            rm->closeFile(fileID);

            delete [] data;
            delete [] old_data;
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

        bool dropIndex(string &tableName, string &idxName) {
            int tableID = findTable(tableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }
            Table& temp = dbConfig.tableVec[tableID];
            for(int i = 0; i < temp.idxNameVec.size(); ++i) {
                if(temp.idxNameVec[i] == idxName) {
                    temp.idxNameVec.erase(temp.idxNameVec.begin() + i);
                    temp.indexVec.erase(temp.indexVec.begin() + i);
                    return true;
                }
            }
            ErrorHandler::instance().set_error_code(RC::ERROR_INDEX_NOT_EXIST);
            ErrorHandler::instance().push_arg(idxName);
            return false;
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

        bool addForeignKey() {
            int tableID = findTable(tableName);
            int refTableID = findTable(refTableName);
            if(tableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }
            if(refTableID == -1) {
                ErrorHandler::instance().set_error_code(RC::ERROR_TABLE_NOT_EXIST);
                ErrorHandler::instance().push_arg(tableName);
                return false;
            }


            Table &table = dbConfig.tableVec[tableID];
            Table &ref = dbConfig.tableVec[refTableID];

            if(colList.size() != refColList.size()) {
                ErrorHandler::instance().set_error_code(RC::ERROR_COLUMN_NUM_NOT_MATCH);
                ErrorHandler::instance().push_arg(to_string(colList.size()));
                ErrorHandler::instance().push_arg(to_string(refColList.size()));
                
                return false;
            }


            for(auto& s: table.fkNameVec) {
                if(s == fkName) {
                    ErrorHandler::instance().set_error_code(RC::ERROR_FOREIGNKEY_ALREADY_EXIST);
                    ErrorHandler::instance().push_arg(fkName);
                    return false;
                }
            }

            vector<string> attrs;
            for(auto &col: colList) {
                attrs.push_back(col.colName);
            }

            vector<string> refAttrs;
            for(auto &col: refColList) {
                refAttrs.push_back(col.colName);
            }

            vector<int> attrIDs;
            vector<int> refIDs;
            table.convertAttrToID(attrs, attrIDs);
            ref.convertAttrToID(refAttrs, refIDs);

            

            for(int i = 0; i < attrIDs.size(); ++i) {
                int attrID = attrIDs[i];
                int refID = refIDs[i];
                if(table.attrVec[attrID].attrType != ref.attrVec[refID].attrType) {
                    cout << "ERROR: Column Type Not Match" << endl;
                    return;
                }
                if(table.attrVec[attrID].attrLen != ref.attrVec[refID].attrLen) {
                    cout << "ERROR: Column Length Not Match" << endl;
                    return;
                }
            }

            multiCol temp, refTemp;
            temp.idVec = attrIDs;
            refTemp.idVec = refIDs;

            if(!ref.primaryKey.eq(refTemp)) {
                cout << "ERROR: Reference Not Primary Key" << endl;
                return;
            }

            table.fkNameVec.push_back(fkName);
            table.foreignKeyVec.push_back(temp);

            table.refTableVec.push_back(refTableName);
            table.refColVec.push_back(refTemp);



        }

        bool dropForeignKey() {}



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

            return true;

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