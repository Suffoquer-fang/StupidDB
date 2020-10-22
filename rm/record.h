#include "unistd.h"
#include "memory"

class Record {
    int size;
    int rid;
    char *data;

    Record() {
        this->size = 0;
        this->rid = -1;
        this->data = nullptr;
    }

    ~Record() {}

    void setRecord(int size, int rid, char *pdata) {
        if(this->data) {
            delete [] this->data;
        }

        this->data = new char [size];
        this->size = size;
        this->rid = rid;

        memcpy(this->data, pdata, size);
    }

    char* getData() { return this->data; }
    int getRid() { return this->rid; }


};