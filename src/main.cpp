#include <iostream>
#include "ql/ql.h"


using namespace std;

QL_QueryManager *qm = new QL_QueryManager(); 
int yyparse(void);

unsigned char h[61];

int main(void) 
{ 
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_RecordManager *rm = new RM_RecordManager(fm, bpm);
    IX_IndexManager *ix = new IX_IndexManager(fm, bpm);

    qm->sm = new SM_SystemManager(rm, ix);
    
    while(1)
        yyparse(); 

    cout << "exit" << endl;
    qm->sm->closeDB();
    
    return 0; 
}
