#pragma once;
#include <iostream>
#include "constants.h"
#include <vector>
#include <cstdio>
using namespace std;


class FormatPrinter {
    private:
        FormatPrinter() {}
        int curLineWidth;

    public:
        ~FormatPrinter() {}
        FormatPrinter(const FormatPrinter&) = delete;
        FormatPrinter& operator = (const FormatPrinter&) = delete;
        static FormatPrinter& instance() {
            static FormatPrinter instance;
            return instance;
        }

        void setLineWidth(int w) {this->curLineWidth = w;}

        void printWelcome() {
            cout << "   _____ __              _     ______  ____" << endl;
            cout << "  / ___// /___  ______  (_)___/ / __ \\/ __ )" << endl;
            cout << "  \\__ \\/ __/ / / / __ \\/ / __  / / / / __  |" << endl;
            cout << " ___/ / /_/ /_/ / /_/ / / /_/ / /_/ / /_/ / " << endl;
            cout << "/____/\\__/\\__,_/ .___/_/\\__,_/_____/_____/  " << endl;
            cout << "              /_/                           " << endl;

            cout << "Welcome to Stupid DB" << endl;
        }

        void printHeaderLine(char c = '-') {
            for(int i = 0; i < curLineWidth + 2; ++i)
                cout << c;
            cout << endl;
        }
        void printMidLine(char c = '-') {
            cout << "+";
            for(int i = 0; i < curLineWidth; ++i)
                cout << c;
            cout << "+" << endl;
        }
        void printString(const char* s, int num = -1, bool left = true, bool leftCol = false, bool rightCol = false, bool newLine = false) {
            printString(string(s), num, left, leftCol, rightCol, newLine);
        }
        void printString(const string &s, int num = -1, bool left = true, bool leftCol = false, bool rightCol = false, bool newLine = false) {
            if(num == -1) num = curLineWidth;
            int spaceNum = num - s.length();
            string temp = s;
            if(spaceNum < 0) {
                temp = temp.substr(0, num - 4);
                temp += "...";
                spaceNum = 1;
            }
            if(leftCol) cout << "|";
            if(left) {
                for(int i = 0; i < spaceNum; ++i)
                    cout << " ";
                cout << temp;
            } else {
                cout << temp;
                for(int i = 0; i < spaceNum; ++i)
                    cout << " ";
            }
            if(rightCol) cout << "|";
            if(newLine) cout << endl;
        }
        static void quoteString(string &s) {
            cout << "'" << s << "'";
        }
        static void error() {
            cout << "ERROR: ";
        }
        static void printError(RC code, vector<string> args) {
            error();
            if(code == RC::ERROR_DB_NOT_EXIST) {
                cout << "Database ";
                quoteString(args[0]);
                cout << " Not Exists";
            } else if(code == RC::ERROR_TABLE_NOT_EXIST) {
                cout << "Table ";
                quoteString(args[0]);
                cout << " Not Exists";    
            } else if(code == RC::ERROR_COLUMN_NOT_EXIST) {
                cout << "Column ";
                quoteString(args[0]);
                cout << " Not Exists";
            } else {
                cout << "Unknown Error";
            }
            cout << endl;
        }
    
};
