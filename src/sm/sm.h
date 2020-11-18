#pragma once
#include <cstring>
#include <cstdio>


class SM_SystemManager {
    public:
        SM_SystemManager() {}
        ~SM_SystemManager() {}
        bool OpenDb      (const char *dbName);                
        bool CloseDb     ();                                  
        bool CreateTable (const char *relName,                
                        int        attrcount,
                        AttrInfo   *attributes);
        bool DropTable   (const char *relName);               
        bool CreateIndex (const char *relName,                
                        const char *attrName);
        bool DropIndex   (const char *relName,                
                        const char *attrName);
        bool Load        (const char *relName,                
                        const char *fileName);
        bool Help        ();                                  
        bool Help        (const char *relName);               
        bool Print       (const char *relName);               
        bool Set         (const char *paramName,              
                        const char *value);
};