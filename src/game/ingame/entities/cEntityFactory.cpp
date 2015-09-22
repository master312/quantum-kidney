#include "cEntityFactory.h"
#include "components/cComCollision.h"
#include "components/cComImage.h"
#include "components/cComAnimation.h"
#include "components/cComPawn.h"
#include "components/cComPlayerDriver.h"
#include "components/cComImage.h"
#include "components/cComAnimation.h"

cEntityFactory::cEntityFactory() {
    luaEngine = nullptr;
    entIdCnt = 0;
}
cEntityFactory::~cEntityFactory() {
    if(luaEngine != nullptr){
        delete luaEngine;
    }
}
void cEntityFactory::Init() {
    luaEngine = new cLuaEngine();
    luaEngine->Init();
}
void cEntityFactory::LoadScripts() {
    //Loads framework scripts
    std::vector<std::string> files;
    bool isError = false;
    
    files = cData::GetDir(DIR_FRAMEWORK_SCRIPTS, "lua");
    if(files.size() > 0){
        StormPrintLog(STORM_LOG_INFO, "cEntityFactory", 
                    "Loading %d framework scripts", files.size());
        for(auto &f : files) {
            std::string tmpFullPath;
            tmpFullPath = std::string(DIR_FRAMEWORK_SCRIPTS) + f;
            if(luaEngine->LoadScript(tmpFullPath) < 0){
                isError = true;
            }
        }
    }
    
    files = cData::GetDir(DIR_ENTITY_SCRIPTS, "lua");
    if(files.size() > 0){
        StormPrintLog(STORM_LOG_INFO, "cEntityFactory", 
                    "Loading %d entity scripts", files.size());
        for(auto &f : files) {
            std::string tmpFullPath;
            tmpFullPath = std::string(DIR_ENTITY_SCRIPTS) + f;
            if(luaEngine->LoadScript(tmpFullPath) < 0){
                isError = true;
            }
            //TODO: Check for script errors here
            //..weather script name is same as lua table name
            //..and some similar shit like that
        }
    }
    
    if(!isError){
        StormPrintLog(STORM_LOG_INFO, "cEntityFactory", 
                    "All scripts have been loaded successfully");
    } else {
        StormPrintLog(STORM_LOG_ERROR, "cEntityFactory", 
                    "Some scripts fail to load");
    }
}
cEntity *cEntityFactory::CreateEntity(const std::string& type) {
    std::vector<std::string> keys = luaEngine->GetTableKeys(type);
    if(keys.size() == 0){
        StormPrintLog(STORM_LOG_ERROR, "cEntityFactory",
                      "Could not create entity of type '%s'. \
                       Script was not found.", type.c_str());
        return nullptr;
    }

    cEntity *e = new cEntity(type);
    entIdCnt ++;
    e->SetId(entIdCnt);
    std::vector<std::string> vec = luaEngine->GetTableKeys(type);
    LuaRef table = luaEngine->GetTable(type);
    
    for(auto &comName : vec){
        if(comName == type){
            LuaRef defTable = table[type.c_str()];
            InitDefault(e, defTable);
        }else if(comName == "Com_Image"){
            LuaRef imgTable = table["Com_Image"];
            AddComponent<cComImage>(e, imgTable);
        }else if(comName == "Com_Animation"){
            LuaRef animTable = table["Com_Animation"];
            AddComponent<cComAnimation>(e, animTable);
        }else if(comName == "Com_Collision"){
            LuaRef colTable = table["Com_Collision"];
            AddComponent<cComCollision>(e, colTable);
        }else if(comName == "Com_Pawn"){
            LuaRef pcTable = table["Com_Pawn"];
            AddComponent<cComPawn>(e, pcTable);
        }else{
            StormPrintLog(STORM_LOG_ERROR, "cEntityFactory",
                    "'%s' component not found", comName.c_str());
        }
    }
}