#pragma once
#include "../utils/constants.h"
// #include <cstring>
#include <string>
#include <vector>

using namespace std;

struct AttrInfo {
	string attrName;
	int attrLen;
	AttrType attrType;
	int offset;

	bool hasIndex;
};

struct Table {
	string tableName;
	int attrNum;
	int recordSize;

	vector<AttrInfo> attrVec;

	void init(string name) {
		tableName = name;
		recordSize = 0;
		attrNum = 0;
	}

	void addAttr(AttrInfo attr) {
		attrVec.push_back(attr);
		attrNum += 1;
		attrVec[attrNum - 1].offset = recordSize / 4;

		recordSize += attr.attrLen;
	}
};

struct DBConfig {
	string dbName;
	int tableNum;
	vector<Table> tableVec;

	void init(string name) {
		dbName = name;
		tableNum = 0;
	}
};