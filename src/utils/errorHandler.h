#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "constants.h"

class ErrorHandler {
    private:
        RC error_code;
        vector<string> args;
        ErrorHandler() {}

    public:
        ~ErrorHandler() {}
        ErrorHandler(const ErrorHandler&) = delete;
        ErrorHandler& operator = (const ErrorHandler&) = delete;
        static ErrorHandler& instance() {
            static ErrorHandler instance;
            return instance;
        }

        void set_error_code(RC error) {
            error_code = error;
        }

        bool has_error() {
            return error_code != RC::NO_ERROR;
        }

        void push_arg(const string &arg) {
            args.push_back(arg);
        }

        string to_string() {
            string error = "ERROR: ";
            string ret;
            if(error_code == RC::ERROR_TABLE_NOT_EXIST) {
                ret = "Table '" + args[0] + "' Not Exists"; 
            } else if(error_code == RC::ERROR_DB_NOT_EXIST) {
                ret = "Database '" + args[0] + "' Not Exists";
            } else if(error_code == RC::ERROR_COLUMN_NOT_EXIST) {
                ret = "Column '" + args[0] + "' Not Exists";
            } else if(error_code == RC::ERROR_TABLE_ALREADY_EXIST) {
                ret = "Table '" + args[0] + "' Already Exists";
            } else if(error_code == RC::ERROR_DB_ALREADY_EXIST) {
                ret = "Database '" + args[0] + "' Already Exists";
            } else if(error_code == RC::ERROR_CLOUMN_ALREARY_EXIST) {
                ret = "Column '" + args[0] + "' Already Exists";
            } else if(error_code == RC::ERROR_COLUMN_HAS_INDEX) {
                ret = "Column '" + args[0] + "' Already Has Index";
            } else if(error_code == RC::ERROR_COLUMN_HAS_NOT_INDEX) {
                ret = "Column '" + args[0] + "' Does Not Have Index";
            } else if(error_code == RC::ERROR_NOT_NULL_CONFLICT) {
                ret = "A NULL Value Conflicts With A NOT NULL Column '" + args[0] + "'";
            } else if(error_code == RC::ERROR_PRIMARYKEY_EXIST) {
                ret = "Primary Key Already Exists In Table '" + args[0] + "'";
            } else if(error_code == RC::ERROR_PRIMARYKEY_NOT_EXIST) {
                ret = "Table '" + args[0] + "' Does Not Have Primary Key";
            } else if(error_code == RC::ERROR_PRIMARYKEY_WRONG_PKNAME) {
                ret = "Primary Key '" + args[0] + "' Not Exists In Table '" + args[1] + "'";
            } else if(error_code == RC::ERROR_PRIMARYKEY_CONFLICT) {
                ret = "Primary Key Values " + args[0] + " Already Exists";
            } else if(error_code == RC::ERROR_TYPE_NOT_MATCH) {
                ret = "Type Not Match For Column '"+ args[0] +"', Expected '" + args[1] + "' Found '" + args[2] + "'";
            } else if(error_code == RC::ERROR_STRING_TOO_LONG) {
                ret = "String Too Long For Column '" + args[0] + "', Max Length: " + args[1];
            } else if(error_code == RC::ERROR_COLUMN_NUM_NOT_MATCH) {
                ret = "Column Num Not Match, Expected " + args[0] + " Found " + args[1];
            } else if(error_code == RC::ERROR_FOREIGNKEY_CONFLICT) {
                ret = "Foreign Key Conflict, Values Not Exist In Reference Table " + args[0];
            } else if(error_code == RC::ERROR_INDEX_ALREADY_EXIST) {
                ret = "Index '" + args[0] + "' Already Exists";
            } else if(error_code == RC::ERROR_DROP_REF_COLUMN) {
                ret = "Drop Column '" + args[0] + "' Which Is Referenced As Forerign Key By Table '" + args[1] + "'";
            } else if(error_code == RC::ERROR_INDEX_NOT_EXIST) {
                ret = "Index '" + args[0] + "' Not Exists";
            } else if(error_code == RC::ERROR_FOREIGNKEY_ALREADY_EXIST) {
                ret = "Foreign Key '" + args[0] + "' Already Exists"; 
            } else if(error_code == RC::ERROR_FOREIGNKEY_NOT_EXIST) {
                ret = "Foreign Key '" + args[0] + "' Not Exists"; 
            }
            else {
                ret = "UNKNOWN ERROR";
            }
            return ret;
        }

        void pop_error() {
            error_code = RC::NO_ERROR;
            args.clear();
        }
};