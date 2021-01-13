#pragma once
#include <iostream>
#include "constants.h"
#include <vector>
#include <cstdio>
#include "errorHandler.h"
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

        static void printWelcome() {
            printf("\033[1m\033[32m");
            cout << "   _____ __              _     __   ____  ____ " << endl;
            cout << "  / ___// /___  ______  (_)___/ /  / __ \\/ __ )" << endl;
            cout << "  \\__ \\/ __/ / / / __ \\/ / __  /  / / / / __  |" << endl;
            cout << " ___/ / /_/ /_/ / /_/ / / /_/ /  / /_/ / /_/ / " << endl;
            cout << "/____/\\__/\\__,_/ .___/_/\\__,_/  /_____/_____/  " << endl;
            cout << "              /_/            " << endl;
            
            printf("\033[0m");
            purple("Welcom to Stupid DB\n");
            endline();
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
            if(!left) {
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
            purple("'" + s + "'");
        }
        
        static void set_blue() {
            printf("\033[1m\033[34m");
        }

        static void reset_color() {
            printf("\033[0m");
        }
        static void red(const string& s) {
            printf("\033[1m\033[31m%s\033[0m", s.c_str());
        }
        static void green(const string& s) {
            printf("\033[1m\033[32m%s\033[0m", s.c_str());
        }

        static void blue(const string& s) {
            printf("\033[1m\033[34m%s\033[0m", s.c_str());
        }
        static void purple(const string& s) {
            printf("\033[1m\033[35m%s\033[0m", s.c_str());
        }

        static void yellow(const string& s) {
            printf("\033[1m\033[33m%s\033[0m", s.c_str());
        }
        
        static void success() {
            blue("SUCCESS: ");
        }

        static void printError() {
            if(!ErrorHandler::instance().has_error()) return;
            red("ERROR: ");
            purple(ErrorHandler::instance().to_string());
            endline();
            ErrorHandler::instance().pop_error();
        }

        static void info(const string& s) {
            yellow(s);
        }
        static void endline() {
            cout << endl << endl;
            green("--> ");
            printf("\033[1m\033[32m");
        }
    
};
