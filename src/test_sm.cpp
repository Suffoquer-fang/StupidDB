#include "sm/sm.h"
#include <iostream>
#include <string>


using namespace std;


unsigned char h[61];
int main() {
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_RecordManager *rm = new RM_RecordManager(fm, bpm);
    IX_IndexManager *ix = new IX_IndexManager(fm, bpm);

    SM_SystemManager *sm = new SM_SystemManager(rm, ix);

    sm->openDB("testDB");

    Table table;
    table.init("testTable", rm, ix);


    AttrInfo a{"a", 4, INTEGER_TYPE, 0, 0};
    AttrInfo b{"b", 4, STRING_TYPE, 4, 0};
    
    table.addAttr(a);
    table.addAttr(b);

    sm->createTable(table);


    char data[20];

    for(int i = 0; i < 100000; ++i) {
        uint data_a = i % 900000;
        // cout << i << endl;
        char data_b[5] = "1234";
        memcpy(data + a.offset, &data_a , a.attrLen);
        memcpy(data + b.offset, data_b , b.attrLen);
        // cout << data[4] << endl;
        sm->insertIntoTable(table.tableName, data);
    }

    // sm->addPrimaryKey(table.tableName, "a");

    Conditions conds;

    Condition cond;
    int value_a = 99985;
    cond.set(0, INTEGER_TYPE, 4, LE_OP, &value_a);

    conds.addCond(cond);

    

    // char value_b[5] = "1234";
    int value_b = 10;
    cond.set(0, INTEGER_TYPE, 4, GT_OP, &value_b);

    conds.addCond(cond);
    sm->selectFromTable(table.tableName, conds);
    sm->deleteFromTable(table.tableName, conds);

    conds.conds.clear();

    sm->selectFromTable(table.tableName, conds);

    sm->dropTable("testTable");
    sm->closeDB();

    // sm->openDB("testDB");
}