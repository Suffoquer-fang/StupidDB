#pragma once

#include <iostream>

#include <unistd.h>
#include "utils.h"
#include "../sm/sm.h"

#include <dirent.h>
#include <iomanip> 

// extern class SM_SystemManager;

using namespace std;

class QL_QueryManager {
   public:
   SM_SystemManager* sm;
   bool isInDB = false;
	QL_QueryManager() {
        // sm = new SM_SystemManager();
    }
	~QL_QueryManager() {}

    void showDatabases() {
        const char *rootDir = "/home/suffoquer/Workspace/2020Autumn/database/StupidDB/src/data/";
        // chdir(rootDir);
        cout << setw(10) <<"------------" << endl;
        cout <<  "|" << setiosflags(ios::left)<<setw(10) << "DATABASES" << "|" << endl;
        cout << setw(10) <<"+----------+" << endl;
        DIR *dir;
        struct dirent *ptr;
        dir=opendir(rootDir);
        while ((ptr=readdir(dir)) != NULL)
         {
            if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
                continue;
             else if(ptr->d_type == 4)    ///dir
             {
                cout <<  "|" << setiosflags(ios::left)<<setw(10) << ptr->d_name << "|" << endl;
             }
         }
        closedir(dir);

        cout << setw(8) <<"------------" << endl;
    }
    void createDatabase(string dbName) {
        const char *rootDir = "/home/suffoquer/Workspace/2020Autumn/database/StupidDB/src/data";
        chdir(rootDir);
        char command[100] = "mkdir ";
        system(strcat(command, dbName.c_str()));
        chdir(dbName.c_str());
        ofstream outfile("meta.db");
        outfile << 0;
        outfile.close();
        chdir(rootDir);
    }
    void dropDatabase(string dbName) {
        const char *rootDir = "/home/suffoquer/Workspace/2020Autumn/database/StupidDB/src/data";
        chdir(rootDir);
        
        char command[100] = "rm -r ";
	    system(strcat(command, dbName.c_str()));
        isInDB = false;
    }
    void useDatabase(string dbName) {
        isInDB = true;
        sm->openDB(dbName.c_str());
    }
    void showTables() {
        sm->showTables();
    }

    void createTable(string tableName, vector<FieldInfo> fieldList) {
        if(!isInDB) {
            cout << "ERROR: Use Database First" << endl;
            return;
        }
        Table table;
        table.init(tableName, nullptr, nullptr);
        
        for(int i = 0; i < fieldList.size(); ++i) {
            AttrInfo attr;
            FieldInfo field = fieldList[i];
            if (field.isPrimaryKey || field.isForeignKey) continue;
            attr.attrName = field.colName;
            attr.attrType = field.type.type;
            attr.attrLen = field.type.attrLen;
            attr.hasIndex = false;
            attr.isNotNULL = field.is_not_null;
            
            table.addAttr(attr);
        }

        sm->createTable(table);

        for(auto &field: fieldList) {
            if(field.isPrimaryKey) {
                alterAddPrimaryKey(tableName, "primary", field.colList);
            }
            if(field.isForeignKey) {
                vector<ColInfo> cols;
                vector<ColInfo> refCols;
                ColInfo col, refCol;
                col.colName = field.colName;
                col.tableName = tableName;
                refCol.colName = field.refColName;
                refCol.tableName = field.refTableName;
                cols.push_back(col);
                refCols.push_back(refCol);
                alterAddForeignKey(tableName, "fkName", cols, field.refTableName, refCols);
            }
        }

        

    }
    void dropTable(string tableName) {
        sm->dropTable(tableName);
    }
    void descTable(string tableName) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        Table &temp = sm->dbConfig.tableVec[tableID];
        int lineSize = 52;
        for(int i = 0; i < lineSize; ++i)
            cout << "-";
        cout << endl;
        
        cout <<  "|" << setiosflags(ios::left)<<setw(50) << tableName << "|" << endl;
        
        cout <<"+";
        for(int i = 0; i < lineSize-2; ++i)
            cout << "-";
        cout <<"+"<< endl;
        for (auto& attr: temp.attrVec) {

            // cout <<  "|" << setiosflags(ios::left) << setw(10) << attr.attrName;
            printf("|%-40s", attr.attrName.c_str());
            // cout << setiosflags(ios::right) << setw(10) << AttrType2Str(attr.attrType) << "|" << endl;
            printf("%10s|\n", AttrType2Str(attr.attrType).c_str());
            
        }
        cout <<"+";
        for(int i = 0; i < lineSize-2; ++i)
            cout << "-";
        cout <<"+"<< endl;

        if(temp.primaryKey.idVec.size() > 0) {
            string tmp = "Primary Key: ";
            tmp += temp.stringfy(temp.primaryKey);
            cout <<  "|" << setiosflags(ios::left)<<setw(50) << tmp << "|" << endl;
        } else {
            cout <<  "|" << setiosflags(ios::left)<<setw(50) << "Primary Key: NULL" << "|" << endl;
        }
        
        cout <<"+";
        for(int i = 0; i < lineSize-2; ++i)
            cout << "-";
        cout <<"+"<< endl;
        
        if(temp.foreignKeyVec.size() == 0) {
            cout <<  "|" << setiosflags(ios::left)<<setw(50) << "Foreign Key: NULL" << "|" << endl;
        
        } else {
            cout <<  "|" << setiosflags(ios::left)<<setw(50) << "Foreign Key: " << "|" << endl;
            for(int i = 0; i < temp.foreignKeyVec.size(); ++i) {
                string tmp = temp.stringfy(temp.foreignKeyVec[i]);
                tmp += " ---> " + temp.refTableVec[i];

                int refID = sm->findTable(temp.refTableVec[i]);
                Table& ref = sm->dbConfig.tableVec[refID];

                tmp += ref.stringfy(ref.primaryKey);
                cout <<  "|" << setiosflags(ios::left)<<setw(50) << tmp << "|" << endl;
            }
        }   
        for(int i = 0; i < lineSize; ++i)
            cout << "-";
        cout << endl;

    }
    void insertIntoTable(string tableName, vector<vector<ValueInfo> > valueLists) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        for(int i = 0; i < valueLists.size(); ++i) {
            char *pData = buildData(tableName, valueLists[i]);

            if(!pData) return;
            if(!checkForeignKey(tableName, pData)) {
                cout << "ERROR: Foreign Key Reference Failed" << endl;
                // cout << 
                return;
            }
            sm->insertIntoTable(tableName, pData);
            delete [] pData;
        }
        

    }
    void deleteFromTable(string tableName, vector<WhereClauseInfo> whereClauseList) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        Conditions conds;

        for(int i = 0; i < whereClauseList.size(); ++i) {
            whereClauseList[i].col.tableName = tableName;
            if(!whereClauseList[i].expr.isValue)
                whereClauseList[i].expr.col.tableName = tableName;
        }


        for(int i = 0; i < whereClauseList.size(); ++i) {
            Condition cond;
            buildCondition(cond, whereClauseList[i]);
            conds.addCond(cond);
        }

        sm->deleteFromTable(tableName, conds);
    }
    
    void updateTable(string tableName, vector<SetClauseInfo> setClauseList, vector<WhereClauseInfo> whereClauseList) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        vector<RID> rids;

        Conditions conds;

        for(int i = 0; i < whereClauseList.size(); ++i) {
            whereClauseList[i].col.tableName = tableName;
            if(!whereClauseList[i].expr.isValue)
                whereClauseList[i].expr.col.tableName = tableName;
        }

        for(int i = 0; i < whereClauseList.size(); ++i) {
            Condition cond;
            buildCondition(cond, whereClauseList[i]);
            conds.addCond(cond);
        }


        vector<Condition> sets;
        for(int i = 0; i < setClauseList.size(); ++i) {
            Condition cond;

            buildSetClause(tableName, cond, setClauseList[i]);
            sets.push_back(cond);
        }
        
        Table &temp = sm->dbConfig.tableVec[tableID];
        
        char *pData = new char[temp.recordSize];
        
        for(int i = 0; i < sets.size(); ++i) {
            memcpy(pData + sets[i].offset, sets[i].value, sets[i].attrLen);
        }

        if(!checkForeignKey(tableName, pData)) {
            cout << "ERROR: Foreign Key Reference Failed" << endl;
            return;
        }


        sm->updateTable(tableName, sets, conds);


    }

    bool isInnerWhere(string tableName, WhereClauseInfo& where) {
        return where.col.tableName == tableName && (where.expr.isValue || where.expr.col.tableName == tableName);
    }

    int findTableIDFromList(string tableName, vector<TableInfo>& tableList) {
        for(int i = 0; i < tableList.size(); ++i) {
            if(tableList[i].tableName == tableName) return i;
        }
        return -1;
    }

    void selectFromTables(SelectorInfo selector, vector<TableInfo> tableList, vector<WhereClauseInfo> whereClauseList = vector<WhereClauseInfo>()) {
        
        if(!isInDB) {
            cout << "ERROR: Use Database First" << endl;
            return;
        }
        if(!selector.isSelectAll) {
            for(int i = 0; i < selector.colList.size(); ++i)
                modifyCol(selector.colList[i], tableList);
        }

        for(int i = 0; i < whereClauseList.size(); ++i) {
            modifyCol(whereClauseList[i].col, tableList);
            if(!whereClauseList[i].expr.isValue)
                modifyCol(whereClauseList[i].expr.col, tableList);
        }



        vector<vector<RID> > joinRIDs;
        for(auto &table: tableList) {
            Conditions conds;

            string tableName = table.tableName;

            for(int i = 0; i < whereClauseList.size(); ++i) {
                if(!isInnerWhere(tableName, whereClauseList[i])) continue;
                Condition cond;
                buildCondition(cond, whereClauseList[i]);
                conds.addCond(cond);
            }

            vector<RID> rids;
            joinRIDs.push_back(rids);
            sm->selectFromTable(tableName, conds, joinRIDs[joinRIDs.size() - 1]);

        }
        Conditions outterConds;
        vector<int> leftTableID;
        vector<int> rhsTableID;
        for(int i = 0; i < whereClauseList.size(); ++i) {
            if(!whereClauseList[i].expr.isValue && whereClauseList[i].col.tableName != whereClauseList[i].expr.col.tableName) {
                Condition cond;
                buildCondition(cond, whereClauseList[i]);
                outterConds.addCond(cond);
                leftTableID.push_back(findTableIDFromList(whereClauseList[i].col.tableName, tableList));
                rhsTableID.push_back(findTableIDFromList(whereClauseList[i].expr.col.tableName, tableList));
            }
        }
        vector<uint*> pDatas;
        vector<RM_FileHandle*> fhs;
        for(int i = 0; i < tableList.size(); ++i) {
            int fileID = sm->fileIDMap[tableList[i].tableName];
            fhs.push_back(sm->rm->getFileHandle(fileID));
            int tableID = sm->findTable(tableList[i].tableName);
            int size = (sm->dbConfig.tableVec[tableID].recordSize + 3) / 4;
            pDatas.push_back(new uint [size]);
        }

        long long maxLine = 1;
        for(auto &i: joinRIDs) {
            maxLine *= i.size();
        }


        vector<int> tableIDs;
        vector<AttrInfo> attrs;

        if(selector.isSelectAll) {
            for(int i = 0; i < tableList.size(); ++i) {
                int tmp = sm->findTable(tableList[i].tableName);
                for(auto& attr: sm->dbConfig.tableVec[tmp].attrVec) {
                    tableIDs.push_back(i);
                    attrs.push_back(attr);
                }

            }
        } else {
            for(auto &col : selector.colList) {
                tableIDs.push_back(findTableIDFromList(col.tableName, tableList));
                int tmp = sm->findTable(col.tableName);
                int attrID = sm->dbConfig.tableVec[tmp].findAttr(col.colName);
                attrs.push_back(sm->dbConfig.tableVec[tmp].attrVec[attrID]);
            }
        }


        
        int lineSize = tableIDs.size() * 20 + 1;
        for(int i = 0; i < lineSize; ++i)
            cout << "-";
        cout << endl;
        cout << "|";
        for(int i = 0; i < tableIDs.size(); ++i) {
            int tableID = tableIDs[i];
            string temp = tableList[tableID].tableName;
            temp += ".";
            temp += attrs[i].attrName;
            printf("%19s|", temp.c_str());
        }
        cout << endl;





        int total = 0;

        for(long long i = 0; i < maxLine; ++i) {
            getIthJoinData(i, joinRIDs, pDatas, fhs);
            if(checkOutterCondition(pDatas, outterConds, leftTableID, rhsTableID)) {
                formatPrint(pDatas, tableIDs, attrs);
                total += 1;
            }

        }

        for(int i = 0; i < lineSize; ++i)
            cout << "-";
        cout << endl;


        cout << "TOTAL RESULTS: " << total << endl;
        for(int i = 0; i < lineSize; ++i)
            cout << "-";
        cout << endl;
    }

    void debug(uint* pData) {
        char* debug = (char*)pData;
        for(int i = 0; i < 5; ++i)
            cout << debug[i] - '0' << ' ';
        cout << endl;
    }

    void formatPrint(vector<uint*> &pDatas, vector<int>& tableIDs, vector<AttrInfo>& attrs) {
        
        int lineSize = tableIDs.size() * 20 + 1;
        cout << "+";
        for(int i = 0; i < lineSize-2; ++i)
            cout << "-";
        cout << "+" << endl;;
        cout << "|";
        
        for(int i = 0; i < tableIDs.size(); ++i) {
            char* attr = (char*)(pDatas[tableIDs[i]]) + attrs[i].offset;
            string temp = Attr2Str(attr, attrs[i].attrType, attrs[i].attrLen);
            // cout << temp.length() << endl;
            if (temp.length() > 15) {
                temp = temp.substr(0, 12) + "...";
            }
            // cout << setiosflags(ios::left) << setw(20) << temp;
            // cout << "|";
            printf("%19s|", temp.c_str());
        }
        cout << endl;
    }

    bool getIthJoinData(int k, vector<vector<RID>> &joinRIDs, vector<uint*> &pDatas, vector<RM_FileHandle* > &fhs) {
        for(int i = joinRIDs.size() - 1; i >= 0; --i) {
            int curID = k % joinRIDs[i].size();
            fhs[i]->getRecord(joinRIDs[i][curID], (pDatas[i]));
            k = k / joinRIDs[i].size();
        }
        return true;
    }
    bool checkOutterCondition(vector<uint*>& pDatas, Conditions& conds, vector<int> &leftTableID, vector<int> &rhsTableID) {
        for(int i = 0; i < conds.conds.size(); ++i) {
            int l = leftTableID[i];
            int r = rhsTableID[i];
            if(!conds.conds[i].satisfy(pDatas[l], pDatas[r])) return false;
        }
        return true;
    }


    void createIndex(string tableName, string idxName, vector<ColInfo> colList) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        Table &temp = sm->dbConfig.tableVec[tableID];
        multiCol new_idx;
        for(auto col: colList) {
            int attrID = sm->dbConfig.tableVec[tableID].findAttr(col.colName);
            new_idx.idVec.push_back(attrID);
        }

        for(auto idx: temp.indexVec) {
            if(idx.eq(new_idx)) {
                cout << "ERROR: Index Already Exists" << endl;
                return;
            }
        }

        temp.indexVec.push_back(new_idx);
        temp.idxNameVec.push_back(idxName);

        cout << tableName << endl;
        int fileID = sm->fileIDMap[tableName];
        RM_FileHandle* fh = sm->rm->getFileHandle(fileID);
        for (auto& col: colList) {
            temp.createIndex(col.colName, false, fh);
        }

        delete fh;
        
    }
    void dropIndex(string idxName) {
        for(auto table: sm->dbConfig.tableVec) {
            alterDropIndex(table.tableName, idxName);
        }
    }
    void alterAddIndex(string tableName, string idxName, vector<ColInfo> colList) {
        createIndex(tableName, idxName, colList);
    }
    void alterDropIndex(string tableName, string idxName) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) return;
        Table &temp = sm->dbConfig.tableVec[tableID];

        for(int i = 0; i < temp.idxNameVec.size(); ++i) {
            if(temp.idxNameVec[i] == idxName) {
                temp.idxNameVec.erase(temp.idxNameVec.begin() + i);
                temp.indexVec.erase(temp.indexVec.begin() + i);
                return;
            }
        }
        cout << "ERROR: Index Not Exists" << endl;
        
    }

    void alterAddfield() {}
    void alterDropCol() {}

    void alterChange() {}

    void alterRename(string oldName, string newName) {
        if(oldName == newName) return;
        int tableID = sm->findTable(oldName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }

        if(sm->findTable(newName) != -1) {
            cout << "ERROR: New Name Already Exists" << endl;
            return;
        }

        sm->dbConfig.tableVec[tableID].tableName = newName;
        
        for(int i = 0; i < sm->dbConfig.tableNum; ++i) {
            Table &temp = sm->dbConfig.tableVec[i];
            for(auto &t: temp.refTableVec) {
                if (t == oldName)
                    t = newName;
            }
        }

        sm->fileIDMap[newName] = sm->fileIDMap[oldName];
        rename(oldName.c_str(), newName.c_str());

        rename((oldName + ".*").c_str(), (newName + ".*").c_str());

    }

    void alterDropPrimaryKey(string tableName, string pkName, bool check) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        if(check) {
            if(pkName != sm->dbConfig.tableVec[tableID].pkName) {
                cout << "ERROR: Primary Key '"<< pkName <<"' Not Exists" << endl;
                return;
            }
        }

        sm->dbConfig.tableVec[tableID].primaryKey.idVec.clear();

    }


    void alterAddPrimaryKey(string tableName, string pkName, vector<ColInfo> colList) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table Not Exists" << endl;
            return;
        }
        Table &temp = sm->dbConfig.tableVec[tableID];
        temp.pkName = pkName;

        vector<string> attrs;
        for(auto &col: colList) {
            attrs.push_back(col.colName);
        }
        // cout << "ssss" << endl;
        bool ret = sm->addPrimaryKey(tableName, attrs);
        // cout << "ssss" << endl;
        if(!ret) {
            cout << "ERROR: Can Not Add Primary Key" << endl;
        }
        

    }
    void alterAddForeignKey(string tableName, string fkName, vector<ColInfo> colList, string refTableName, vector<ColInfo> refColList) {
        int tableID = sm->findTable(tableName);
        int refTableID = sm->findTable(refTableName);
        if(tableID == -1) {
            cout << "ERROR: Table '" << tableName << "' not Exists" << endl;
            return;
        }
        if(refTableID == -1) {
            cout << "ERROR: Table '" << refTableName << "' not Exists" << endl;
            return;
        }


        Table &table = sm->dbConfig.tableVec[tableID];
        Table &ref = sm->dbConfig.tableVec[refTableID];

        if(colList.size() != refColList.size()) {
            cout << "ERROR: Reference Size Not Match" << endl;
            return;
        }


        for(auto& s: table.fkNameVec) {
            if(s == fkName) {
                cout << "ERROR: Foreign Key '" << fkName << "' Already Exists" << endl;
                return;
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
    void alterDropForeignKey(string tableName, string fkName) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            cout << "ERROR: Table '" << tableName << "' not Exists" << endl;
            return;
        }
        Table& table = sm->dbConfig.tableVec[tableID];
        for(int i = 0; i < table.fkNameVec.size(); ++i) {
            if(table.fkNameVec[i] == fkName) {
                table.fkNameVec.erase(table.fkNameVec.begin() + i);
                table.foreignKeyVec.erase(table.foreignKeyVec.begin() + i);
                table.refTableVec.erase(table.refTableVec.begin() + i);
                table.refColVec.erase(table.refColVec.begin() + i);
                return;
            }
        }
        cout << "ERROR: Foreign Key '" << fkName << "' Not Exists" << endl;
        return;
    }

    bool checkForeignKey(string tableName, char* pData) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) {
            // cout << "Table '" << tableName << "' not Exists" << endl;
            return false;
        }
        Table &table = sm->dbConfig.tableVec[tableID];
        for(int i = 0; i < table.foreignKeyVec.size(); ++i) {
            string refTableName = table.refTableVec[i];
            // cout << refTableName << endl;
            Table &ref = sm->dbConfig.tableVec[sm->findTable(refTableName)];
            // cout << "fffff" << endl;
            if(!checkSingleForeignKey(table, ref, pData, table.foreignKeyVec[i], table.refColVec[i])) {
                return false;
            }
        }
        return true;
    }

    bool checkSingleForeignKey(Table& table, Table& ref, char* pData, multiCol& attr, multiCol& refAttr) {
        // cout << ref.tableName << endl;
        // cout << ref.recordSize << endl;
        char* refData = new char [ref.recordSize];
        memset(refData, 0, ref.recordSize);
        for(int i = 0; i < attr.idVec.size(); ++i) {
            int off = table.attrVec[attr.idVec[i]].offset;
            int refOff = ref.attrVec[refAttr.idVec[i]].offset;

            int len = table.attrVec[attr.idVec[i]].attrLen;
            int refLen = ref.attrVec[refAttr.idVec[i]].attrLen;

            if(len != refLen) {
                cout << "error!!!" << endl;
                return false;
            }

            memcpy(refData + refOff, pData + off, len);

        }
        return !sm->checkPrimaryKeyNotExist(ref.tableName, refData);
    }
    

    char* buildData(string tableName, vector<ValueInfo> values) {
        int tableID = sm->findTable(tableName);
        if(tableID == -1) return nullptr;
        Table &temp = sm->dbConfig.tableVec[tableID];
        
        char *ret = new char[temp.recordSize];
        memset(ret, 0, temp.recordSize);
        

        for(int i = 0; i < values.size(); ++i) {
            if(values[i].value_null) {
                ret[temp.attrVec[i].offset] = 1;
                continue;
            }

            if(values[i].valueType != temp.attrVec[i].attrType) {
                if(values[i].valueType == INTEGER_TYPE && temp.attrVec[i].attrType == FLOAT_TYPE) {
                    values[i].valueType = FLOAT_TYPE;
                    values[i].value_float = (float)values[i].value_int;
                    
                } else {
                cout << "ERROR: Type Not Match" << endl;
                delete [] ret;
                return nullptr;
                }
            }

            if(values[i].valueType == STRING_TYPE) {
                if(values[i].value_string.length() > temp.attrVec[i].attrLen - 1) {
                    cout << "ERROR: Input String Too Long" << endl;
                    delete [] ret;
                    return nullptr;
                }
                else 
                    memcpy(ret + temp.attrVec[i].offset + 1, values[i].value_string.c_str(), values[i].value_string.length());
            }

            if(values[i].valueType == INTEGER_TYPE) {
                memcpy(ret + temp.attrVec[i].offset + 1, &(values[i].value_int), 4);
            }

            if(values[i].valueType == FLOAT_TYPE) {
                memcpy(ret + temp.attrVec[i].offset + 1, &(values[i].value_float), 4);
            
            }

            
            
        }
        

        return ret;
    }

    bool modifyCol(ColInfo& col, vector<TableInfo> &tableList) {
        if(col.hasTableName) return true;

        for(int i = 0; i < tableList.size(); ++i) {
            int tableID = sm->findTable(tableList[i].tableName);
            Table &temp = sm->dbConfig.tableVec[tableID];
            int attrID = temp.findAttr(col.colName);
            if(attrID != -1) {
                col.tableName = tableList[i].tableName;
                return true;
            }
        }
        return false;
    }

    bool isInnerWhere(WhereClauseInfo& where) {
        if(where.expr.isValue) return true;
        return where.col.tableName == where.expr.col.tableName;
    }

    bool buildCondition(Condition &cond, WhereClauseInfo& where) {
        
        int tableID = sm->findTable(where.col.tableName);
        Table &temp = sm->dbConfig.tableVec[tableID];
        int attrID = temp.findAttr(where.col.colName);
        AttrInfo &attr = temp.attrVec[attrID];

        int off = attr.offset;
        AttrType type = attr.attrType;
        int rhsOff = -1;
        char *ret = new char [attr.attrLen];
        memset(ret, 0, attr.attrLen);

        if(where.expr.isValue) {
            
            if(where.expr.value.value_null) {
                ret[0] = 1;
            }
            else if(where.expr.value.valueType == STRING_TYPE) {
                if(where.expr.value.value_string.length() > attr.attrLen - 1) {
                    cout << "ERROR: Input Condition String Too Long" << endl;
                    return false;
                }
                else {
                    memcpy(ret + 1, where.expr.value.value_string.c_str(), where.expr.value.value_string.length());
                }
            }
            else if(where.expr.value.valueType == INTEGER_TYPE) {
                memcpy(ret + 1, &(where.expr.value.value_int), 4);
            }
            else if(where.expr.value.valueType == FLOAT_TYPE) {
                memcpy(ret + 1, &(where.expr.value.value_float), 4);
            
            }
            cond.set(off, type, attr.attrLen, where.op, ret, true);
            
        } else {
            rhsOff = findTableColOffset(where.expr.col);
            // cout << rhsOff << endl;
            cond.set(off, type, attr.attrLen, where.op, nullptr, false, rhsOff);
        }
        delete [] ret;
        return true;

        

    }

    bool buildSetClause(string tableName, Condition &cond, SetClauseInfo &setClause) {
        int tableID = sm->findTable(tableName);
        Table &temp = sm->dbConfig.tableVec[tableID];
        int attrID = temp.findAttr(setClause.colName);
        AttrInfo &attr = temp.attrVec[attrID];

        int off = attr.offset;
        AttrType type = attr.attrType;
        int rhsOff = -1;

        char *ret = new char [attr.attrLen];
        memset(ret, 0, attr.attrLen);

        if(setClause.value.value_null) {
            ret[0] = 1;
        }
        else if(setClause.value.valueType == STRING_TYPE) {
            if(setClause.value.value_string.length() > attr.attrLen - 1) {
                cout << "ERROR: Input Condition String Too Long" << endl;
                return false;
            }
            else {
                memcpy(ret + 1, setClause.value.value_string.c_str(), setClause.value.value_string.length());
            }
        }
        else if(setClause.value.valueType == INTEGER_TYPE) {
            memcpy(ret + 1, &(setClause.value.value_int), 4);
        }
        else if(setClause.value.valueType == FLOAT_TYPE) {
            memcpy(ret + 1, &(setClause.value.value_float), 4);
        
        }
        cond.set(off, type, attr.attrLen, EQ_OP, ret, true);

        delete [] ret;
        return true;

    }

    int findTableColOffset(ColInfo &col) {
        
        int tableID = sm->findTable(col.tableName);
        Table &temp = sm->dbConfig.tableVec[tableID];
        int attrID = temp.findAttr(col.colName);
        return temp.attrVec[attrID].offset;
    }
};