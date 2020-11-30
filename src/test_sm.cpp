#include "sm/sm.h"
#include <iostream>
#include <string>


using namespace std;

int main() {
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_RecordManager *rm = new RM_RecordManager(fm, bpm);
    IX_IndexManager *ix = new IX_IndexManager(fm, bpm);

    SM_SystemManager *sm = new SM_SystemManager(rm, ix);

    sm->openDB("testDB");

    Table table;
    table.init("testTable");
    AttrInfo a{"a", 4, INTEGER, 0, 0};
    AttrInfo b{"b", 4, INTEGER, 0, 1};
    
    table.addAttr(a);
    table.addAttr(b);

    sm->createTable(table);

    

    sm->createIndex("testTable", "a");

    // sm->dropIndex("testTable", "b");
    // sm->dropTable("testTable");
    sm->closeDB();
}