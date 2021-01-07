#pragma once

#include <iostream>

#include "utils.h"
#include "../sm/sm.h"

// extern class SM_SystemManager;

using namespace std;

class QL_QueryManager {
   public:
   SM_SystemManager* sm;
	QL_QueryManager() {
        // sm = new SM_SystemManager();
    }
	~QL_QueryManager() {}

    void showDatabases() {}
    void createDatabase() {}
    void dropDatabase() {}
    void useDatabase(string dbName) {
        sm->openDB(dbName.c_str());
    }
    void showTables() {
        sm->showTables();
    }

    void createTable(string tableName, vector<FieldInfo> fieldList) {
        Table table;
        table.init(tableName, nullptr, nullptr);
        
        for(int i = 0; i < fieldList.size(); ++i) {
            AttrInfo attr;
            FieldInfo field = fieldList[i];
            attr.attrName = field.colName;
            attr.attrType = field.type.type;
            attr.attrLen = field.type.attrLen;
            attr.hasIndex = false;
            
            table.addAttr(attr);
        }

        sm->createTable(table);

    }
    void dropTable(string tableName) {
        sm->dropTable(tableName);
    }
    void descTable() {}
    void insertIntoTable(string tableName, vector<vector<ValueInfo>> valueLists) {
        cout << "insert into " << tableName  << endl;

        for(int i = 0; i < valueLists.size(); ++i) {
            char *pData = buildData(tableName, valueLists[i]);

            if(!pData) return;
            sm->insertIntoTable(tableName, pData);
            delete [] pData;
        }
        

    }
    void deleteFromTable(string tableName, vector<WhereClauseInfo> whereClauseList) {
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
    void updateTable() {}
    void selectFromTables(SelectorInfo selector, vector<TableInfo> tableList, vector<WhereClauseInfo> whereClauseList) {
        cout << "Select Stmt";
        selector.debug();
        
        // assert(tableList.size() == 1);

        string tableName = tableList[0].tableName;

        for(int i = 0; i < whereClauseList.size(); ++i) {
            modifyCol(whereClauseList[i].col, tableList);
            if(!whereClauseList[i].expr.isValue)
                modifyCol(whereClauseList[i].expr.col, tableList);
        }





        Conditions conds;


        for(int i = 0; i < whereClauseList.size(); ++i) {
            Condition cond;
            buildCondition(cond, whereClauseList[i]);
            conds.addCond(cond);
        }
        sm->selectFromTable(tableName, conds);


    }

    void createIndex() {}
    void dropIndex() {}
    void alterAddIndex() {}
    void alterDropIndex() {}

    void alterAddfield() {}
    void alterAddCol() {}
    void alterChange() {}
    void alterRename() {}

    void alterDropPrimaryKey() {}
    void alterAddPrimaryKey() {}
    void alterAddForeignKey() {}
    void alterDropForeignKey() {}

    

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


            if(values[i].valueType == STRING_TYPE) {
                if(values[i].value_string.length() > temp.attrVec[i].attrLen - 1) {
                    cout << "string too long" << endl;
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

    bool buildCondition(Condition &cond, WhereClauseInfo& where) {
        
        int tableID = sm->findTable(where.col.tableName);
        Table &temp = sm->dbConfig.tableVec[tableID];
        int attrID = temp.findAttr(where.col.colName);
        AttrInfo &attr = temp.attrVec[attrID];

        int off = attr.offset;
        AttrType type = attr.attrType;
        int rhsOff = -1;
        char ret[attr.attrLen] = {0};
        if(where.expr.isValue) {
            
            if(where.expr.value.value_null) {
                ret[0] = 1;
            }
            else if(where.expr.value.valueType == STRING_TYPE) {
                if(where.expr.value.value_string.length() > attr.attrLen - 1) {
                    cout << "condition string too long" << endl;
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
        return true;

        

    }

    int findTableColOffset(ColInfo &col) {
        
        int tableID = sm->findTable(col.tableName);
        Table &temp = sm->dbConfig.tableVec[tableID];
        int attrID = temp.findAttr(col.colName);
        return temp.attrVec[attrID].offset;
    }
};