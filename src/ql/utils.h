#pragma once

#include "../utils/constants.h"
#include <string>
#include <vector>
#include <iostream>

// using namespace std;

// struct AttrType {
// 	string name;
// };

// struct CompareOP {};

struct ColInfo {
	string tableName;     
	string colName;
	bool hasTableName;
	void debug() {
		cout << "ColInfo: ";
		if(hasTableName) {
			cout << tableName << ".";
		}
		cout << colName << endl;
	}
};

struct TypeInfo {
	AttrType type;
	int attrLen;
};

struct ValueInfo {
	AttrType valueType;
	int value_int;
	float value_float;
	string value_string;
	bool value_null = false;

	void debug() {
		if(value_null)
			cout << "NULL" << " ";
		else {
			// debugAttrType(valueType);
			cout << ": " << value_string << " ";
		}
	}
};

struct FieldInfo {
	string colName;
	TypeInfo type;
	bool is_not_null;
	bool has_default;
	ValueInfo defaultValue;
	bool isPrimaryKey;
	vector<ColInfo> colList;
	bool isForeignKey;
	string refTableName;
	string refColName;
	
};

struct Expr {
	bool isValue;
	ValueInfo value;
	ColInfo col;
	void debug() {
		if(isValue)
			value.debug();
		else 
			col.debug();
	}
};

struct WhereClauseInfo {
	ColInfo col;
	CompareOP op;
	Expr expr;
	void debug() {
		cout << "WhereClauseInfo:" << endl;
		col.debug();
		// cout << op << endl;
		debugCompareOP(op);
		expr.debug();
		cout << endl;
	}
};



struct SetClauseInfo {
	string colName;
	ValueInfo value;
};

struct SelectorInfo {
	bool isSelectAll = false;
	vector<ColInfo> colList;
	void debug() {
		cout << "SelectorInfo: ";
		if(isSelectAll) {
			cout << "*" << endl;
		} else {
			cout << endl;
			for(auto i: colList)
				i.debug();
		}
	}
};

struct TableInfo {
	string tableName;
	void debug() {
		cout << "TableInfo: " << tableName << endl;
	}
};

// struct ConditionInfo {

// };


struct YYType {
	string id;
	ColInfo _col;
	FieldInfo _field;
	ValueInfo _value;
	SetClauseInfo _setClause;
	WhereClauseInfo _whereClause;
	Expr _expr;
	TypeInfo _type;
    CompareOP _op;

	vector<ColInfo> colList;
	vector<FieldInfo> fieldList;
	vector<ValueInfo> valueList;
	vector<SetClauseInfo> setClauseList;
	vector<WhereClauseInfo> whereClauseList;
	vector<TableInfo> tableList;
	SelectorInfo selector;

	vector<vector<ValueInfo>> valueLists;
};




#define YYSTYPE YYType
