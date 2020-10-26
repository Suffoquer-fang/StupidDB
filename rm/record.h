#include "unistd.h"
#include <cstring>
#include <cstdio>

class Record {
    int size;
    int pageID, slotID;
    unsigned int *data;
public:
    Record() {
        this->size = 0;
        this->pageID = -1;
        this->slotID = -1;
        this->data = nullptr;
    }

    ~Record() {}

    void setRecord(int size, int pageID, int slotID, unsigned int *pdata) {
        if(this->data) {
            delete [] this->data;
        }

        this->data = new unsigned int [size];
        this->size = size;
        this->pageID = pageID;
        this->slotID = slotID;

        memcpy(this->data, pdata, size * sizeof(uint));
    }

    unsigned int* getData() { return this->data; }
    void getPageSlotID(int &ret_pageID, int &ret_slotID) { 
        ret_pageID = this->pageID;
        ret_slotID = this->slotID;
    }

    void display() {
        for(int i = 0; i < size; ++i)
            printf("%d ", *(data + i));
        puts(" ");
    }

};