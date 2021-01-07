#pragma once
#include "../utils/constants.h"
// #include <cstring>
#include <string>
#include <vector>
#include <ostream>

#include "table.h"
using namespace std;



struct DBConfig {
	string dbName;
	int tableNum;
	vector<Table> tableVec;

	void init(string name) {
		dbName = name;
		tableNum = 0;
	}
};