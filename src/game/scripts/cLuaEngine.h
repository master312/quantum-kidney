/* 
 * File:   cLuaEngine.h
 * Author: master312
 *
 * Created on August 30, 2015, 12:33 AM
 * TODO: Replace copyrighted code here
 */

#ifndef CLUAENGINE_H
#define	CLUAENGINE_H
#include <map>
#include <iostream>
#include <vector>
#include <LuaBridge/LuaBridge.h>
#include "../../storm/engine.h"

extern "C" {
    #include "lua5.2/lua.h"
    #include "lua5.2/lauxlib.h"
    #include "lua5.2/lualib.h"
}

using namespace luabridge;

class cLuaEngine {
public:
    cLuaEngine();
    ~cLuaEngine();
    
    void Init();
    /* Return < 0 if there was an error */
    int LoadScript(const std::string filename);
    /* Return vector of strings with key names of the table @name */
    std::vector<std::string> GetTableKeys(const std::string &name);
    /* Return LuaRef object to the table named @name */
    LuaRef GetTable(const std::string &name);
private:
    lua_State *state;
    
    void GetToStack(const std::string &varName);
    void LoadKeysGetterFunction();
};

#endif	/* CLUAENGINE_H */

