#pragma once
#include "../filesystem/fs.h"
#include "utils.h"
#include "../rm/record.h"
#include <cstring>
#include <cstdio>
#include <vector>
#include <ctime>

class IX_IndexHandle {
    public:
        int fileID;
        FileManager *fm;
        BufPageManager *bpm;

        IX_FileConfig fileConfig;
        
        IX_BPlusTreeNode nodesPool[10];
        bool nodesUsed[10];

        double time_cnt;
        double down;
        double up;
    
        IX_IndexHandle(FileManager *fm, BufPageManager *bpm, int fileID) {
            this->fileID = fileID;
            this->fm = fm;
            this->bpm = bpm;

            int tmp_index;
            BufType data = bpm->getPage(fileID, 0, tmp_index);
            memcpy(&fileConfig, data, sizeof(IX_FileConfig));
            
            bpm->access(tmp_index);

            time_cnt = 0;
            down = 0;
            up = 0;

            for(int i = 0; i < 10; ++i)
                nodesUsed[i] = false;
        }
        ~IX_IndexHandle() {}

        bool insertEntry(void *pData, RID rid) {
            int curID = fileConfig.rootNode;
            
            // IX_BPlusTreeNode *fake = nullptr;
            // bool ret = recurInsertEntry(curID, pData, rid, fake);
            // if(fake) {
            //     // fake->debug();
            //     forceWrite(fake);
            //     delete fake;
            // }

            bool ret = normalInsertEntry(curID, pData, rid);

            updateFileConfig();
            return ret;
        }

        bool deleteEntry(void *pData, RID rid) {
            int rootID = fileConfig.rootNode;

            IX_BPlusTreeNode *fake = nullptr;
            bool ret = recurDeleteEntry(rootID, pData, rid, fake);
            if(fake) {
                forceWrite(fake);
                delete fake;
            }
            updateFileConfig();
            
            return ret;
        }

        bool searchFirstEntry(void *pData, int &retID, int &index) {
            bool ret = lessThan(pData, retID, index);
            if(!ret) return false;
            IX_BPlusTreeNode *node = new IX_BPlusTreeNode();
            convertPageToNode(retID, node);

            if(index < node->curNum - 1) {
                index += 1;
                return true;
            } else {
                retID = node->nextNode;
                index = 0;
                return (retID > 0);
            }
        }

        bool searchLastEntry(void *pData, int &retID, int &index) {
            return lessEqual(pData, retID, index);
            // return recurSearchEntry(fileConfig.rootNode, pData, retID, index);
        }


        bool searchEntry(void *pData, vector<RID>& vec) {
            int rootID = fileConfig.rootNode;
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            int index = -1;
            int nodeID = -1;
            bool ret = recurSearchEntry(rootID, pData, nodeID, index);
            if(!ret) return false;
            IX_BPlusTreeNode* node = new IX_BPlusTreeNode();
            convertPageToNode(nodeID, node);
            while(true) {
                for(int i = index; i >= 0; --i) {
                    if(compareAttr(pData, node->getIthKeyPointer(i, attrLen), attrType, attrLen) == 0) {
                        vec.push_back(RID(node->getIthPage(i), node->getIthSlot(i)));
                    } else {
                        delete node;
                        return true;
                    }
                }
                int prevID = node->prevNode;
                if(prevID > 0) {
                    convertPageToNode(prevID, node);
                    index = node->curNum - 1;
                } else {
                    delete node;
                    return true;
                }
            }
        }





        void convertPageToNode(int pageID, IX_BPlusTreeNode* &node) {
            if(!node) node = new IX_BPlusTreeNode();
            
            int index;
            BufType buf = bpm->getPage(fileID, pageID, index);
            bpm->access(index);
            
            memcpy(node, buf, fileConfig.treeNodeInfoSize);

            
            node->rids = buf + fileConfig.treeNodeInfoSize;
            node->keys = (char *)(buf + fileConfig.treeNodeInfoSize + fileConfig.maxRidSize);

            node->selfID = pageID;

        }

        IX_BPlusTreeNode* assignNode(int pageID) {
            IX_BPlusTreeNode* node = nullptr;
            for(int i = 0; i < 10; ++i) {
                if(!nodesUsed[i]) {
                    node = nodesPool + i;
                    nodesUsed[i] = true;
                    break;
                }
            }
            if(!node) return node;

            int index;
            BufType buf = bpm->getPage(fileID, pageID, index);
            bpm->access(index);
            
            memcpy(node, buf, fileConfig.treeNodeInfoSize);

            
            node->rids = buf + fileConfig.treeNodeInfoSize;
            node->keys = (char *)(buf + fileConfig.treeNodeInfoSize + fileConfig.maxRidSize);

            node->selfID = pageID;

            return node;
        }

        void releaseNode(IX_BPlusTreeNode* node) {
            for(int i = 0; i < 10; ++i) {
                if(node == nodesPool + i) {
                    nodesUsed[i] = false;
                    return;
                }
            }
        }



        void debug(int id) {
            IX_BPlusTreeNode *node = new IX_BPlusTreeNode();
            convertPageToNode(id, node);
            node->debug();
            if(!node->isLeafNode) {
                for(int i = 0; i < node->curNum; ++i) {
                    debug(node->getIthPage(i));
                }
            }

            delete node;
            return;
        }

        void iterLeaves(vector<int>&key, vector<RID>& vec) {
            int rootID = fileConfig.rootNode;
            IX_BPlusTreeNode *node = new IX_BPlusTreeNode();
            convertPageToNode(rootID, node);
            while(!node->isLeafNode) {
                int id = node->getIthPage(0);
                convertPageToNode(id, node);
            }
            while(true) {
                for(int i = 0; i < node->curNum; ++i) {
                    key.push_back(*((uint *)(node->getIthKeyPointer(i, fileConfig.attrLength))));
                    vec.push_back(RID(node->getIthPage(i), node->getIthSlot(i)));
                }
                if(node->nextNode > 0) {
                    int next = node->nextNode;
                    convertPageToNode(next, node);
                } else {
                    return;
                }
            }
        }

        void forceWrite(IX_BPlusTreeNode *node) {
            if(node->selfID <= 0) return;
            // auto start = clock();
            // printf("force %d %d\n", node->selfID, node->curNum);
            int index;
            BufType buf = bpm->getPage(fileID, node->selfID, index);
            // time_cnt += (double)(clock() - start);
            memcpy(buf, node, fileConfig.treeNodeInfoSize);
            bpm->markDirty(index);
            
        }

        void getFirstEntry(IX_BPlusTreeNode* &node) {
            int rootID = fileConfig.rootNode;
            if(!node)
                node = new IX_BPlusTreeNode();
            convertPageToNode(rootID, node);
            while(!node->isLeafNode) {
                int id = node->getIthPage(0);
                convertPageToNode(id, node);
            }
        }


        bool getRecord(int nodeID, int index, void* &pData, RID &rid) {
            IX_BPlusTreeNode *node = new IX_BPlusTreeNode();
            convertPageToNode(nodeID, node);
            pData = node->getIthKeyPointer(index, fileConfig.attrLength);
            rid.set(node->getIthPage(index), node->getIthSlot(index));
            return true;
        }


    private:

        bool recurInsertEntry(int nodeID, void *pData, RID rid, IX_BPlusTreeNode* &parentNode) {
            int m = fileConfig.maxKeyNum;
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            convertPageToNode(nodeID, curNode);

            bool ret = false;

            if(!curNode->isLeafNode) {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    void* tmp_key = curNode->getIthKeyPointer(i, attrLen);
                    if(i == 0 || compareAttr(pData, tmp_key, attrType, attrLen) >= 0) {
                        int new_id = curNode->rids[2 * i];
                        ret = recurInsertEntry(new_id, pData, rid, curNode);
                        break;
                    }
                }
            } else {
                int i;
                for(i = curNode->curNum; i > 0; --i) {
                    void* tmp_key = curNode->getIthKeyPointer(i - 1, attrLen);
                    if(compareAttr(pData, tmp_key, attrType, attrLen) >= 0) 
                        break;
                    memcpy(curNode->getIthKeyPointer(i, attrLen), curNode->getIthKeyPointer(i - 1, attrLen), attrLen);
                    curNode->setRID(i, curNode->getIthPage(i - 1), curNode->getIthSlot(i - 1));
                }

                // printf("insert %d, i = %d\n", *((int*)pData), i);

                memcpy(curNode->getIthKeyPointer(i, attrLen), pData, attrLen);
                curNode->setRID(i, rid);


                curNode->curNum += 1;
                ret = true;
            }



            if(curNode->curNum >= fileConfig.maxKeyNum) {

                // IX_BPlusTreeNode* parentNode = NULL;

                if(curNode->parentNode <= 0) {
                    int parent = ++fileConfig.curNodeNum;
                    convertPageToNode(parent, parentNode);
                    fileConfig.rootNode = parent;

                    parentNode->init(false, -1, -1, -1);
                    memcpy(parentNode->keys, curNode->keys, attrLen);
                    parentNode->rids[0] = nodeID;
                    parentNode->curNum = 1;
                    
                    curNode->parentNode = parent;

                    // printf("\nmake new parent %d %d\n", curNode->selfID, curNode->curNum);
                    
                }



                IX_BPlusTreeNode* newNode = splitNode(curNode, attrLen);
                
                // printf("\ndone split\n");

                // if(!parentNode) parentNode = convertPageToNode(curNode->parentNode);
                int curWhichChild = whichChild(nodeID, parentNode);

                if(curWhichChild == -1) {
                    printf("error\n");
                }


                for(int i = parentNode->curNum; i > curWhichChild + 1; --i) {
                    memcpy(parentNode->getIthKeyPointer(i, attrLen), parentNode->getIthKeyPointer(i - 1, attrLen), attrLen);
                    parentNode->setRID(i, parentNode->getIthPage(i - 1), parentNode->getIthSlot(i - 1));
                }

                parentNode->curNum += 1;
                // printf("add %d %d\n\n", parentNode->selfID, parentNode->curNum);

                memcpy(parentNode->getIthKeyPointer(curWhichChild, attrLen), curNode->keys, attrLen);
                memcpy(parentNode->getIthKeyPointer(curWhichChild + 1, attrLen), newNode->keys, attrLen);

                parentNode->setRID(curWhichChild + 1, newNode->selfID, -1);

                
                forceWrite(newNode);

               

                delete newNode;
                // delete parentNode;

            }

            forceWrite(curNode);
            
            delete curNode;



            return ret;
        }

        IX_BPlusTreeNode* splitNode(IX_BPlusTreeNode* curNode, int attrLen) {
            int newNodeID = ++fileConfig.curNodeNum;
            int curID = curNode->selfID;
            
            // IX_BPlusTreeNode* newNode = new IX_BPlusTreeNode();
            // convertPageToNode(newNodeID, newNode);
            IX_BPlusTreeNode* newNode = assignNode(newNodeID);

            newNode->init(curNode->isLeafNode, curID, curNode->nextNode, curNode->parentNode);

            int m = curNode->curNum / 2;

            // printf("\nm = %d\n", newNode->parentNode);            
            newNode->curNum = curNode->curNum - m;

            // for(int i = 0; i < newNode->curNum; ++i) {
            //     // printf("move %d\n", *(curNode->getIthKeyPointer(i + m, attrLen)));
            //     memcpy(newNode->getIthKeyPointer(i, attrLen), curNode->getIthKeyPointer(i + m, attrLen), attrLen);
            //     newNode->setRID(i, curNode->getIthPage(i + m), curNode->getIthSlot(i + m));

            //     // printf("move %d\n", *(newNode->getIthKeyPointer(i, attrLen)));
            // }

            memmove(newNode->getIthKeyPointer(0, attrLen), curNode->getIthKeyPointer(m, attrLen), attrLen * newNode->curNum);
            memmove(newNode->rids, curNode->rids + 2 * m, 2 * sizeof(uint) * newNode->curNum);


            curNode->curNum = m;
            curNode->nextNode = newNodeID;

            // printf("\ndone trans\n");

            if(!newNode->isLeafNode) {
                for(int i = 0; i < newNode->curNum; ++i) {
                    int childPage = newNode->getIthPage(i);
                    if(childPage > 0) {
                        modifyParent(childPage, newNode->selfID);
                    }
                }
            } else {
                if(newNode->nextNode > 0) {
                    modifyPrev(newNode->nextNode, newNode->selfID);
                }
            }


            return newNode;


        }

        int binarySearch(IX_BPlusTreeNode* node, void *pData, AttrType attrType, int attrLen) {
            int l = 0;
            int r = node->curNum;
            while(l < r) {
                int mid = l + r >> 1;
                void* tmp_key = node->getIthKeyPointer(mid, attrLen);
                if(compareAttr(pData, tmp_key, attrType, attrLen) < 0) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            return l - 1;

        }
        bool normalInsertEntry(int nodeID, void *pData, RID rid) {
            int m = fileConfig.maxKeyNum;
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            // IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            // convertPageToNode(nodeID, curNode);
            IX_BPlusTreeNode* curNode = assignNode(nodeID);
            // auto start = clock();
            while (!curNode->isLeafNode) {
                
                int tmp = binarySearch(curNode, pData, attrType, attrLen);
                if(tmp < 0) tmp = 0;
                int new_id = curNode->rids[2 * tmp];
                convertPageToNode(new_id, curNode);
            }
            // down += (double)(clock() - start);
            // start = clock();
            // int i;
            // for(i = curNode->curNum; i > 0; --i) {
            //     void* tmp_key = curNode->getIthKeyPointer(i - 1, attrLen);
            //     if(compareAttr(pData, tmp_key, attrType, attrLen) >= 0) 
            //         break;
            //     memcpy(curNode->getIthKeyPointer(i, attrLen), curNode->getIthKeyPointer(i - 1, attrLen), attrLen);
            //     curNode->setRID(i, curNode->getIthPage(i - 1), curNode->getIthSlot(i - 1));
            // }
            int tmp = binarySearch(curNode, pData, attrType, attrLen);
            int i = tmp + 1;
            int num = curNode->curNum - i;
            if(num > 0) {
                memmove(curNode->getIthKeyPointer(i+1 ,attrLen), curNode->getIthKeyPointer(i, attrLen), attrLen * num);
                memmove(curNode->rids + 2 * (i+1), curNode->rids + 2*i, sizeof(uint) * 2 * num);
            }
            memcpy(curNode->getIthKeyPointer(i, attrLen), pData, attrLen);
            curNode->setRID(i, rid);
            curNode->curNum += 1;

            
            // up += (double)(clock() - start);

            IX_BPlusTreeNode* parentNode = nullptr;
            while(curNode->curNum >= fileConfig.maxKeyNum) {
                
                if(curNode->parentNode <= 0) {
                    int parent = ++fileConfig.curNodeNum;
                    // convertPageToNode(parent, parentNode);
                    parentNode = assignNode(parent);

                    fileConfig.rootNode = parent;

                    parentNode->init(false, -1, -1, -1);
                    memcpy(parentNode->keys, curNode->keys, attrLen);
                    parentNode->rids[0] = curNode->selfID;
                    parentNode->curNum = 1;
                    
                    curNode->parentNode = parent;
                } else {
                    // convertPageToNode(curNode->parentNode, parentNode);
                    parentNode = assignNode(curNode->parentNode);
                }
                IX_BPlusTreeNode* newNode = splitNode(curNode, attrLen);
                int curWhichChild = whichChild(curNode->selfID, parentNode);
                for(int i = parentNode->curNum; i > curWhichChild + 1; --i) {
                    memcpy(parentNode->getIthKeyPointer(i, attrLen), parentNode->getIthKeyPointer(i - 1, attrLen), attrLen);
                    parentNode->setRID(i, parentNode->getIthPage(i - 1), parentNode->getIthSlot(i - 1));
                }
                parentNode->curNum += 1;

                memcpy(parentNode->getIthKeyPointer(curWhichChild, attrLen), curNode->keys, attrLen);
                memcpy(parentNode->getIthKeyPointer(curWhichChild + 1, attrLen), newNode->keys, attrLen);

                parentNode->setRID(curWhichChild + 1, newNode->selfID, -1);
                forceWrite(newNode);
                // delete newNode;
                releaseNode(newNode);

                forceWrite(curNode);
                // delete curNode;
                releaseNode(curNode);

                curNode = parentNode;
                // nodeID = parentNode->selfID;
            }

            
            forceWrite(curNode);
            // delete curNode;
            releaseNode(curNode);
            return true;

        }


        

        bool recurDeleteEntry(int nodeID, void *pData, RID rid, IX_BPlusTreeNode* &parentNode) {
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            convertPageToNode(nodeID, curNode);

            bool ret = false;

            if(!curNode->isLeafNode) {
                int start = 0;
                for(int i = 0; i < curNode->curNum; ++i) {
                    start = i;
                    if(i == curNode->curNum-1 || compareAttr(pData, curNode->getIthKeyPointer(i+1, attrLen), attrType, attrLen) <= 0)
                        break;
                }


                for(int i = curNode->curNum - 1; i >= start; --i) {
                    void* tmp_key = curNode->getIthKeyPointer(i, attrLen);
                    if(i == start || compareAttr(pData, tmp_key, attrType, attrLen) >= 0) {
                        int new_id = curNode->rids[2 * i];
                        ret |= recurDeleteEntry(new_id, pData, rid, curNode);
                        if(ret) break;
                    }
                }
            } else {
                int id = -1;
                for(int i = 0; i < curNode->curNum; ++i) {
                    if(compareAttr(pData, curNode->getIthKeyPointer(i, attrLen), attrType, attrLen) == 0 && rid.equal(curNode->getIthPage(i), curNode->getIthSlot(i))) {
                        id = i;
                        break;
                    }
                }

                if(id != -1) {
                    curNode->curNum -= 1;
                    for(int i = id; i < curNode->curNum; ++i) {
                        memcpy(curNode->getIthKeyPointer(i, attrLen), curNode->getIthKeyPointer(i + 1, attrLen), attrLen);
                        curNode->setRID(i, curNode->getIthPage(i + 1), curNode->getIthSlot(i + 1));
                    }
                    ret = true;

                } else {
                    delete curNode;
                    return false;
                }

            }

            if(curNode->curNum == 0) {
                if(curNode->isLeafNode) {
                    if(curNode->prevNode > 0)
                        modifyNext(curNode->prevNode, curNode->nextNode);
                    if(curNode->nextNode > 0)
                        modifyPrev(curNode->nextNode, curNode->prevNode);
                }

                if(nodeID == fileConfig.rootNode) return ret;

                int curWhichChild = whichChild(nodeID, parentNode);
                
                if(curWhichChild == -1) {
                    printf("error");
                }

                parentNode->curNum -= 1;
                for(int i = curWhichChild; i < parentNode->curNum; ++i) {
                    memcpy(curNode->getIthKeyPointer(i, attrLen), curNode->getIthKeyPointer(i + 1, attrLen), attrLen);
                    curNode->setRID(i, curNode->getIthPage(i + 1), curNode->getIthSlot(i + 1));
                }


            }

            forceWrite(curNode);
            delete curNode;
            
            return ret;
        }
        bool lessThan(void *pData, int &retID, int &index) {
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            int id = fileConfig.rootNode;
            convertPageToNode(id, curNode);

            while(!curNode->isLeafNode) {
                for(int i = 0; i < curNode->curNum; ++i) {
                    if(i == curNode->curNum - 1 || compareAttr(pData, curNode->getIthKeyPointer(i+1, attrLen), attrType, attrLen) <= 0) {
                        id = curNode->getIthPage(i);
                        break;
                    }
                }
                convertPageToNode(id, curNode);
            }
            for(int i = curNode->curNum - 1; i >= 0; --i) {
                if(compareAttr(pData, curNode->getIthKeyPointer(i, attrLen), attrType, attrLen) > 0) {
                    index = i;
                    retID = id;
                    delete curNode;
                    return true;
                }
            }
            delete curNode;
            return false;

        }

        bool lessEqual(void *pData, int &retID, int &index) {
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            int id = fileConfig.rootNode;
            convertPageToNode(id, curNode);

            while(!curNode->isLeafNode) {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    if(i == 0 || compareAttr(pData, curNode->getIthKeyPointer(i, attrLen), attrType, attrLen) >= 0) {
                        id = curNode->getIthPage(i);
                        break;
                    }
                }
                convertPageToNode(id, curNode);
            }
            for(int i = curNode->curNum - 1; i >= 0; --i) {
                if(compareAttr(pData, curNode->getIthKeyPointer(i, attrLen), attrType, attrLen) >= 0) {
                    index = i;
                    retID = id;
                    delete curNode;
                    return true;
                }
            }
            delete curNode;
            return false;
        }


        bool recurSearchEntryFirst(int nodeID, void *pData, int &retID, int &index) {
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            convertPageToNode(nodeID, curNode);

            bool ret = false;

            if(!curNode->isLeafNode) {
                int start = -1;
                int end = -1;
                for(int i = 0; i < curNode->curNum; ++i) {
                    if(i == curNode->curNum - 1 || compareAttr(pData, curNode->getIthKeyPointer(i+1, attrLen), attrType, attrLen) <= 0) {
                        start = i;
                        break;
                    }
                }
                if(start == curNode->curNum - 1)
                    end = start;
                else
                    end = (compareAttr(pData, curNode->getIthKeyPointer(start+1, attrLen), attrType, attrLen) == 0) ? start + 1: start;
                

                int new_id = curNode->rids[2 * start];
                ret = recurSearchEntry(new_id, pData, retID, index);
                if(ret || start == end) {
                    delete curNode;
                    return ret;
                } else {
                    new_id = curNode->rids[2 * end];
                    ret = recurSearchEntry(new_id, pData, retID, index);
                    delete curNode;
                    return ret;
                }
                

            } else {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    if(compareAttr(pData, curNode->getIthKeyPointer(i, attrLen), attrType, attrLen) == 0) {
                        index = i;
                        retID = nodeID;
                        delete curNode;
                        return true;
                    }
                }

                
                delete curNode;
                return false;
            }
        }

        bool recurSearchEntry(int nodeID, void *pData, int &retID, int &index) {
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = new IX_BPlusTreeNode();
            convertPageToNode(nodeID, curNode);

            bool ret = false;

            if(!curNode->isLeafNode) {
                
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    void* tmp_key = curNode->getIthKeyPointer(i, attrLen);
                    if(i == 0 || compareAttr(pData, tmp_key, attrType, attrLen) >= 0) {
                        int new_id = curNode->rids[2 * i];
                        ret = recurSearchEntry(new_id, pData, retID, index);
                        delete curNode;
                        return ret;
                    }
                }
            } else {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    if(compareAttr(pData, curNode->getIthKeyPointer(i, attrLen), attrType, attrLen) == 0) {
                        index = i;
                        retID = nodeID;
                        delete curNode;
                        return true;
                    }
                }

                
                delete curNode;
                return false;
            }
        }

        void modifyParent(int id, int parent) {
            auto start = clock();
            IX_BPlusTreeNode *tmp = new IX_BPlusTreeNode();
            convertPageToNode(id, tmp);
            tmp->parentNode = parent;
            forceWrite(tmp);
            delete tmp;
            time_cnt += (double)(clock() - start);
        }

        void modifyPrev(int id, int prev){
            IX_BPlusTreeNode *tmp = new IX_BPlusTreeNode();
            convertPageToNode(id, tmp);
            tmp->prevNode = prev;
            forceWrite(tmp);
            delete tmp;
        }

        void modifyNext(int id, int next) {
            IX_BPlusTreeNode *tmp = new IX_BPlusTreeNode();
            convertPageToNode(id, tmp);
            tmp->nextNode = next;
            forceWrite(tmp);
            delete tmp;
        }

        

        void updateFileConfig() {
            int index;
            BufType buf = bpm->getPage(fileID, 0, index);
            memcpy(buf, &(fileConfig), sizeof(IX_FileConfig));
            bpm->markDirty(index); 
        }

        int whichChild(int curID, IX_BPlusTreeNode *parentNode) {
            if(parentNode->isLeafNode) return -1;
            for(int i = 0; i < parentNode->curNum; ++i) {
                if(parentNode->getIthPage(i) == curID) return i;
            }
            return -1;
        }



        
        
};