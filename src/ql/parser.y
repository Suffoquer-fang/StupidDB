%{
    #include <cstdio>
    #include "ql.h"
    #include "utils.h"
    // extern class QL_QueryManager;
    extern "C"
    {
        void yyerror(const char *s);
        extern int yylex(void);
    };
    extern QL_QueryManager* qm;
%}




%token DATABASE DATABASES TABLE TABLES SHOW CREATE
        DROP USE PRIMARY KEY NOT SQLNULL
        INSERT INTO VALUES DELETE FROM WHERE
        UPDATE SET SELECT IS TOKEN_INT VARCHAR
        DEFAULT CONSTRAINT CHANGE ALTER ADD RENAME
        DESC INDEX AND DATE FLOAT FOREIGN
        REFERENCES ON TO	
%token EQ NE LT GT LE GE	
%token IDENTIFIER
%token VALUE_INT
%token VALUE_FLOAT
%token VALUE_STRING


%type <id> IDENTIFIER dbName fkName pkName tbName colName idxName VALUE_INT VALUE_FLOAT VALUE_STRING
%type <colList> columnList colList
%type <tableList> tableList
%type <selector> selector
%type <_col> col
%type <_field> field
%type <_whereClause> whereClause
%type <whereClauseList> whereClauseList
%type <_expr> expr
%type <_value> value
%type <valueList> valueList
%type <valueLists> valueLists
%type <_op> op
%type <fieldList> fieldList
%type <_type> type
%%

program:
    | 
    program stmt;

stmt:
    sysStmt ';'
    | 
    dbStmt ';'
    | 
    tbStmt ';'
    | 
    idxStmt ';'
    | 
    alterStmt';';

sysStmt: 
    SHOW DATABASES;

dbStmt:   
      CREATE DATABASE dbName {printf("Create\n");}
    | DROP DATABASE dbName
    | USE dbName {
      qm->useDatabase($2);
    }
    | SHOW TABLES {qm->showTables();}
	; 

tbStmt: 
      CREATE TABLE tbName '(' fieldList ')' {
        qm->createTable($3, $5);
      }
    | DROP TABLE tbName {
        qm->dropTable($3);
    }
    | DESC tbName
    | INSERT INTO tbName VALUES valueLists {
        qm->insertIntoTable($3, $5);
    }
    | DELETE FROM tbName WHERE whereClauseList {
        qm->deleteFromTable($3, $5);
    }
    | UPDATE tbName SET setClause WHERE whereClauseList {
        qm->updateTable();
    }
    | SELECT selector FROM tableList WHERE whereClauseList 
      {
        qm->selectFromTables($2, $4, $6);
      }
	  ;

idxStmt:
      CREATE INDEX idxName ON tbName '(' columnList ')' {printf("create index\n"); for(int i = 0; i < $7.size(); ++i) $7[i].debug();}
    | DROP INDEX idxName {
      qm->dropIndex();
    }
    | ALTER TABLE tbName ADD INDEX idxName '(' columnList ')' {
      qm->alterAddIndex();
    }
    | ALTER TABLE tbName DROP INDEX idxName {
      qm->alterDropIndex();
    }
    ;

alterStmt: 
      ALTER TABLE tbName ADD field {
        qm->alterAddfield();
      }
    | ALTER TABLE tbName DROP colName {
      qm->alterAddCol();
    }
    | ALTER TABLE tbName CHANGE colName field {
      qm->alterChange();
    }
    | ALTER TABLE tbName RENAME TO tbName {
      qm->alterRename();
    }
    | ALTER TABLE tbName DROP PRIMARY KEY {
      qm->alterDropPrimaryKey();
    }
    | ALTER TABLE tbName ADD CONSTRAINT pkName PRIMARY KEY '(' columnList ')' {
      qm->alterAddPrimaryKey();
    }
    | ALTER TABLE tbName DROP PRIMARY KEY pkName {
      qm->alterDropPrimaryKey();
    }
    | ALTER TABLE tbName ADD CONSTRAINT fkName FOREIGN KEY '(' columnList ')' REFERENCES tbName '(' columnList ')' {
      qm->alterAddForeignKey();
    }
    | ALTER TABLE tbName DROP FOREIGN KEY fkName {
      qm->alterDropForeignKey();
    }
    ;

fieldList: 
      field {$$.push_back($1);}
    | fieldList ',' field {$$.push_back($3);}
    ;

field: 
      colName type {
        $$.colName = $1;
        $$.type = $2;
      }
    | colName type NOT SQLNULL {
        $$.colName = $1;
        $$.type = $2;
    }
    | colName type DEFAULT value {
        $$.colName = $1;
        $$.type = $2;
    }
    | colName type NOT SQLNULL DEFAULT value {
        $$.colName = $1;
        $$.type = $2;
    }
    | PRIMARY KEY '(' columnList ')' {
        $$.isPrimaryKey = true;
        $$.colList = $4;
    }
    | FOREIGN KEY '(' colName ')' REFERENCES tbName '(' colName ')' {
        $$.isForeignKey = true;
        $$.colName = $4;
        $$.refTableName = $7;
        $$.refColName = $9; 
    }
    ;

type: 
      TOKEN_INT '(' VALUE_INT ')' {
        $$.type = INTEGER_TYPE;
        $$.attrLen = 4;
      }
    | VARCHAR '(' VALUE_INT ')' {
        $$.type = STRING_TYPE;
        $$.attrLen = 10;
    }
    | DATE {
        $$.type = STRING_TYPE;
        $$.attrLen = 10;
    }
    | FLOAT {
        $$.type = FLOAT_TYPE;
        $$.attrLen = 4;
    }
    ;

valueLists: 
      '(' valueList ')' {$$.push_back($2);}
    | valueLists ',' '(' valueList ')' {$$.push_back($4);}
    ;

valueList: 
      value {$$.push_back($1);}
    | valueList ',' value {$$.push_back($3);}
    ;

value: 
      VALUE_INT {
        $$.valueType = INTEGER_TYPE; 
        $$.value_int = atoi($1.c_str());
        // printf("in %d\n", $$.value_int);
      }
    | VALUE_FLOAT {
        $$.valueType = FLOAT_TYPE; 
        $$.value_float = (float)(atof($1.c_str()));
      }
    | VALUE_STRING {
        $$.valueType = STRING_TYPE; 
        $$.value_string = $1;
      }
    | SQLNULL {$$.value_null = true;}
    ;   

whereClause: 
      col op expr {
        $$.col = $1;
        $$.op = $2;
        $$.expr = $3;
      }
    | col IS SQLNULL {
        $$.col = $1;
        $$.op = EQ_OP;
        $$.expr.isValue = true;
        $$.expr.value.value_null = true;
    }
    | col IS NOT SQLNULL {
        $$.col = $1;
        $$.op = NE_OP;
        $$.expr.isValue = true;
        $$.expr.value.value_null = true;
    }
    ;

whereClauseList:
      whereClause {
        $$.push_back($1);
      }
    | whereClauseList AND whereClause {
      $$.push_back($3);
    }
    ;

col: 
      colName {
        $$.colName = $1;
        $$.hasTableName = false;
      }
    | tbName '.' colName {
        $$.tableName = $1;
        $$.colName = $3;
        $$.hasTableName = true;
    }
    ;

colList:
	  col {
		  $$.push_back($1);
    }
	| colList ',' col {
      $$.push_back($3);
  }
	;

op: EQ {$$ = EQ_OP;}| NE {$$ = NE_OP;}| LE {$$ = LE_OP;}| GE {$$ = GE_OP;}| LT {$$ = LT_OP;}| GT {$$ = GT_OP;};

expr: 
      value {$$.isValue = true; $$.value = $1;}
    | col {$$.isValue = false; $$.col = $1;}
    ;

setClause: 
      colName EQ value
    | setClause ',' colName EQ value
    ;

selector: 
      '*' {$$.isSelectAll = true;}
    | colList {$$.isSelectAll = false; $$.colList = $1;}
	;



tableList: 
	  tbName {
		  TableInfo temp;
		  temp.tableName = $1;
		  $$.push_back(temp);
	  }
	| tableList ',' tbName {
		  TableInfo temp;
		  temp.tableName = $3;
		  $$.push_back(temp);
	}
	;

columnList: 
	  colName {
		  ColInfo temp;
		  temp.colName = $1;
      temp.hasTableName = false;
		  $$.push_back(temp);
		  // printf("push back %s\n", $1.c_str());
		}
	| columnList ',' colName {
		ColInfo temp;
		temp.colName = $3;
    temp.hasTableName = false;
		$$.push_back(temp);
		// printf("push back %s\n", $3.c_str());
	}
	;

dbName: IDENTIFIER {$$ = $1;};

tbName: IDENTIFIER { $$ = $1;};

colName: IDENTIFIER { $$ = $1;};

pkName: IDENTIFIER { $$ = $1;};

fkName: IDENTIFIER { $$ = $1;};

idxName: IDENTIFIER { $$ = $1; };


%%

void yyerror(const char *s)
{
    printf("err\n");
}