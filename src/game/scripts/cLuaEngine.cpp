#include "cLuaEngine.h"

cLuaEngine::cLuaEngine() {
    state = nullptr;
}
cLuaEngine::~cLuaEngine() {
    if(state != nullptr){
        lua_close(state);
        state = nullptr;
    }
}
void cLuaEngine::Init() {
    state = luaL_newstate();
    luaL_openlibs(state);
    LoadKeysGetterFunction();
}
int cLuaEngine::LoadScript(const std::string filename) {
    if (!(luaL_loadfile(state, filename.c_str()) || 
            lua_pcall(state, 0, 0, 0))){
        StormPrintLog(STORM_LOG_INFO, "cLuaEngine", 
                        "Script '%s' loaded", filename.c_str());
        return 1;
    } else {
        StormPrintLog(STORM_LOG_ERROR, "cLuaEngine", 
                        "Could not load script '%s'", filename.c_str());
        lua_pop(state, 1);
        return -1;
    }
}
std::vector<std::string> cLuaEngine::GetTableKeys(const std::string &name) {
    lua_getglobal(state, "getKeys"); // get function
    if (lua_isnil(state, -1)) {
        StormPrintLog(STORM_LOG_WARNING, "cLuaEngine", 
                    "getKeys function not initialized. Initializing...");
        LoadKeysGetterFunction();
        lua_getglobal(state, "getKeys");
    }

    GetToStack(name);

    lua_pcall(state, 1, 1, 0); // execute function. Got table on stack

    lua_pushnil(state);

    std::vector<std::string> keys;

    while(lua_next(state, -2)){ // get values one by one
        if(lua_type(state, -1) == LUA_TSTRING){
            keys.push_back(lua_tostring(state, -1));
        }
        lua_pop(state, 1);
    }

    lua_settop(state, 0); // remove s table from stack 
    return keys;
}
LuaRef cLuaEngine::GetTable(const std::string &name) {
    return getGlobal(state, name.c_str());
}
//Private functions
void cLuaEngine::GetToStack(const std::string &varName) {
    int level = 0;
    std::string var = "";
    for(unsigned int i = 0; i < varName.size(); i++){
        if(varName.at(i) == '.'){
            if(level == 0){
                lua_getglobal(state, var.c_str());
            } else {
                lua_getfield(state, -1, var.c_str());
            }

            if(lua_isnil(state, -1)){
                StormPrintLog(STORM_LOG_ERROR, "cLuaEngine", 
                        "Could not find variable '%s'", varName.c_str());
                return;
            } else {
                var = "";
                ++level;
            }
        } else {
            var += varName.at(i);
        }
    }
    if(level == 0){
        lua_getglobal(state, var.c_str());
    } else {
        lua_getfield(state, -1, var.c_str());
    }

    if(level == 0){ 
        return; 
    }

    int tableIndex = lua_gettop(state) - level;
    lua_replace(state, tableIndex);
    lua_settop(state, tableIndex);
}
void cLuaEngine::LoadKeysGetterFunction() {
    std::string code =
        R"(function getKeys(t)
        s = {}
        for k, v in pairs(t) do 
            table.insert(s, k)
            end 
        return s 
        end)";
    
    luaL_dostring(state, code.c_str());
}