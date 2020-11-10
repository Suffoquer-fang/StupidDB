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
            if(!curNode->isLeafNode) {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    void* tmp_key = curNode->keys + i * attrLen;
                    if(compareAttr(pData, tmp_key, attrType, attrLen) >= 0) {
                        int new_id = curNode->rids[2 * i];
                        return recurInsertEntry(new_id, pData, rid);
                    }
                }
                int new_id = curNode->rids[0];
                memcpy(curNode->keys, pData, attrLen);
                return recurInsertEntry(new_id, pData, rid);

            } else {
                for(int i = curNode->curNum - 1; i >= 0; --i) {
                    void* tmp_key = curNode->keys + i * attrLen;
                    if(compareAttr(pData, tmp_key, attrType, attrLen) >= 0) {
                        memcpy(curNode)
                    }
                }
            }
        }

        
};