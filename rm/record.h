#pragma once

#include "unistd.h"
#include <cstring>
#include <cstdio>


struct RID {
    int pageID;
    int slotID;
    RID() {
        pageID = -1;
        slotID = -1;
    }

    RID(int p, int s) {
        pageID = p;
        slotID = s;
    }

    void set(int p, int s) {
        pageID = p;
        slotID = s;
    }

    bool equal(const RID &rid) {
        return (pageID == rid.pageID) && (slotID == rid.slotID);
    }

    bool equal(int p, int s) {
        return (pageID == p) && (slotID == s);
    }

};



class Record {
    int size;
    RID rid;
    unsigned int *data;
public:
    Record() {
        this->size = 0;
        this->data = nullptr;
    }

    ~Record() {}

    void setRecord(int size, int pageID, int slotID, unsigned int *pdata) {
        if(this->data) {
            delete [] this->data;
        }

        this->data = new unsigned int [size];
        this->size = size;
        this->rid.set(pageID, slotID);

        memcpy(this->data, pdata, size * sizeof(uint));
    }

    void getData(unsigned int *ret) { ret = this->data; }
    RID getRID() { 
        return this->rid;
    }


    void display() {
        for(int i = 0; i < size; ++i)
            printf("%d ", *(data + i));
        puts(" ");
    }

};
