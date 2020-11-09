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

        }
        bool deleteEntry(void *pData, RID rid) {

        }

        IX_BPlusTreeNode* convertPageToNode(int pageID) {
            IX_BPlusTreeNode* node = new IX_BPlusTreeNode();
            
            int index;
            BufType buf = bpm->getPage(fileID, pageID, index);
            
            
            memcpy(node, buf, fileConfig.treeNodeInfoSize);

            node->keys = buf + fileConfig.treeNodeInfoSize;
            node->rids = buf + fileConfig.treeNodeInfoSize + fileConfig.maxKeySize;

            return node;
        }
        
};