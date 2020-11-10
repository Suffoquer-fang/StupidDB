#include "../filesystem/fs.h"
#include "utils.h"
#include "../rm/record.h"
#include <cstring>
#include <cstdio>


class IX_IndexHandle {
    int fileID;
    FileManager *fm;
    BufPageManager *bpm;

    IX_FileConfig fileConfig;

    public:
        IX_IndexHandle() {}
        ~IX_IndexHandle() {}

        bool insertEntry(void *pData, RID rid) {
            int curID = fileConfig.rootNode;
            
            
        }




        bool deleteEntry(void *pData, RID rid) {

        }

        IX_BPlusTreeNode* convertPageToNode(int pageID) {
            IX_BPlusTreeNode* node = new IX_BPlusTreeNode();
            
            int index;
            BufType buf = bpm->getPage(fileID, pageID, index);
            
            
            memcpy(node, buf, fileConfig.treeNodeInfoSize);

            
            node->rids = buf + fileConfig.treeNodeInfoSize;
            node->keys = buf + fileConfig.treeNodeInfoSize + fileConfig.maxRidSize;

            return node;
        }


    private:

        bool recurInsertEntry(int nodeID, void *pData, RID rid) {
            int m = fileConfig.maxKeyNum;
            int attrLen = fileConfig.attrLength;
            AttrType attrType = fileConfig.attrType;

            IX_BPlusTreeNode* curNode = convertPageToNode(nodeID);

            bool ret = false;

            if(!curNode->isLeafNode) {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    void* tmp_key = curNode->getIthKeyPointer(i, attrLen);
                    if(i == 0 || compareAttr(pData, tmp_key, attrType, attrLen) >= 0) {
                        int new_id = curNode->rids[2 * i];
                        ret = recurInsertEntry(new_id, pData, rid);
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

                memcpy(curNode->getIthKeyPointer(i, attrLen), pData, attrLen);
                curNode->setRID(i, rid);

                ret = true;
            }








            return true;
        }

        
};