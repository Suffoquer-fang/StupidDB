#pragma once

#include "indexhandle.h"

class IX_IndexScan {
    public:
        IX_IndexHandle *ih;
        CompareOP op;
        void *value;

        IX_BPlusTreeNode* node = new IX_BPlusTreeNode();
        int curID;
        int curIndex;

        IX_IndexScan() {}
        ~IX_IndexScan() {}

        bool openScan(IX_IndexHandle* ih, CompareOP op, void *value) {
            this->ih = ih;
            this->op = op;
            this->value = value;

            if(op == EQ || op == GE ) {
                ih->searchFirstEntry(value, curID, curIndex);
                ih->convertPageToNode(curID, node);
            } else if(op == GT) {
                ih->searchLastEntry(value, curID, curIndex);
                ih->convertPageToNode(curID, node);
            } else {
                ih->getFirstEntry(node);
                curID = node->selfID;
            }


        }
        bool hasNextEntry() {
            if(curIndex < node->curNum - 1) {
                return true;
            } else {
                int nextID = node->nextNode;
                if(nextID > 0) {
                    return true;
                } else {
                    return false;
                }
            }
        }

        void nextEntry() {
            if(curIndex < node->curNum - 1) {
                curIndex += 1;
                return;
            } else {
                int nextID = node->nextNode;
                if(nextID > 0) {
                    curIndex = 0;
                    curID = nextID;
                    ih->convertPageToNode(nextID, node);
                    return;
                } else {
                    return;
                }
            }
        }

        bool satisfy() {
            int tmp = compareAttr(node->getIthKeyPointer(curIndex, ih->fileConfig.attrLength), value, ih->fileConfig.attrType, ih->fileConfig.attrLength);
            if(op == EQ)
                return tmp == 0;
            if(op == GE)
                return tmp >= 0;
            if(op == LE)
                return tmp <= 0;
            if(op == GT)
                return tmp > 0;
            if(op == LT)
                return tmp < 0;
            if(op == NE)
                return tmp != 0;
        }

        bool stop() {
            int tmp = compareAttr(node->getIthKeyPointer(curIndex, ih->fileConfig.attrLength), value, ih->fileConfig.attrType, ih->fileConfig.attrLength);
            bool ret = hasNextEntry();
            if(!ret) return true;
            if(op == EQ && tmp > 0) return true;
            if(op == LT && tmp >= 0) return true;
            if(op == LE && tmp > 0) return true;
            return false;
        }

        bool next(RID &rid) {
            if(!node) return false;

            while(true) {
                if(satisfy()) break;
                if(stop()) break;
                nextEntry();
            }
            if(!satisfy()) return false;
            rid.set(node->getIthPage(curIndex), node->getIthSlot(curIndex));
            
            if(hasNextEntry())
                nextEntry();
            else {
                delete node;
                node = nullptr;
            }
            return true;
        }

};

