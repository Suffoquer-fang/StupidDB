#pragma once

#include "indexhandle.h"

class IX_IndexScan {
   public:
	IX_IndexHandle *ih;
	CompareOP op;
	void *value;

	IX_BPlusTreeNode *node = new IX_BPlusTreeNode();
	int curID;
	int curIndex;

	IX_IndexScan() {}
	~IX_IndexScan() {}

	bool openScan(IX_IndexHandle *ih, CompareOP op, void *value) {
		this->ih = ih;
		this->op = op;
		this->value = value;

		if (op == EQ_OP || op == GE_OP) {
			ih->searchFirstEntry(value, curID, curIndex);
			ih->convertPageToNode(curID, node);
		} else if (op == GT_OP) {
			ih->searchLastEntry(value, curID, curIndex);
			ih->convertPageToNode(curID, node);
		} else {
			ih->getFirstEntry(node);
			curID = node->selfID;
			curIndex = 0;
		}
	}
	bool hasNextEntry() {
		if (curIndex < node->curNum - 1) {
			return true;
		} else {
			int nextID = node->nextNode;
			if (nextID > 0) {
				return true;
			} else {
				return false;
			}
		}
	}

	void nextEntry() {
		if (curIndex < node->curNum - 1) {
			curIndex += 1;
			return;
		} else {
			int nextID = node->nextNode;
			if (nextID > 0) {
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
		if(curIndex < 0) return false;
		int tmp = compareAttr(
			node->getIthKeyPointer(curIndex, ih->fileConfig.attrLength), value,
			ih->fileConfig.attrType, ih->fileConfig.attrLength);
		if (op == EQ_OP) return tmp == 0;
		if (op == GE_OP) return tmp >= 0;
		if (op == LE_OP) return tmp <= 0;
		if (op == GT_OP) return tmp > 0;
		if (op == LT_OP) return tmp < 0;
		if (op == NE_OP) return tmp != 0;
		if (op == NO_OP) return true;
	}

	bool stop() {
		bool ret = hasNextEntry();
		if (!ret) return true;
		int tmp = compareAttr(
			node->getIthKeyPointer(curIndex, ih->fileConfig.attrLength), value,
			ih->fileConfig.attrType, ih->fileConfig.attrLength);
		
		if (op == EQ_OP && tmp > 0) return true;
		if (op == LT_OP && tmp >= 0) return true;
		if (op == LE_OP && tmp > 0) return true;
		return false;
	}

	bool next(RID &rid) {
		if (!node) return false;

		while (true) {
			if (satisfy()) break;
			if (stop()) break;
			nextEntry();
		}
		if (!satisfy()) return false;
		rid.set(node->getIthPage(curIndex), node->getIthSlot(curIndex));

		if (hasNextEntry())
			nextEntry();
		else {
			delete node;
			node = nullptr;
		}
		return true;
	}
};
