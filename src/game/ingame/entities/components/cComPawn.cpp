#include "cComPawn.h"
#include "cComPlayerDriver.h"
#include "../cEntity.h"

cComPawn::cComPawn(luabridge::LuaRef &table, cEntity *e) {
    dir = 0;
    isMoving = false;
    
    luabridge::LuaRef refTemplate = table["template"];
    luabridge::LuaRef refName = table["name"];
    luabridge::LuaRef refSubname = table["subname"];
    luabridge::LuaRef refStats = table["stats"];
    luabridge::LuaRef refController = table["controller"];
    
    if(!refTemplate.isNil()){
        //TODO: Load shit from template
        //If there is template error, return here
    }
    
    if(!refName.isNil() && refName.isString()){
        name = refName.cast<std::string>();
    }else if(refTemplate.isNil()){
        StormPrintLog(STORM_LOG_WARNING, "cComPawn", ""
                      "Pawn name not set");
        name = "No_name_specified";
    }
    
    if(!refSubname.isNil() && refSubname.isString()){
        subName = refSubname.cast<std::string>();
    }
    
    if(!refStats.isNil() && refStats.isTable()){
        
    }else if(refTemplate.isNil()){
        StormPrintLog(STORM_LOG_ERROR, "cComPawn", ""
                      "Pawn stats not specified. Setting default stats");
    }
    
    if(!refController.isNil()){
        if(refController.isFunction()){
            //TODO: Pawn is controller by this function
            //and its called every tick
        }else if(refController.isString()){
            //TODO: Pawn is controlled by default controller
            //ex: 'ai_controller_stupid', 'user_controller'
        }else if(refController.isTable()){
            //TODO: Pawn is controlled by some controller component
            //create that component here. Use table refController for parameters
            if(refController["component"].isNil() || 
               !refController["component"].isString()){
                StormPrintLog(STORM_LOG_ERROR, "cComPawn",
                              "Component name not specified for pawn controller");
                return;
            }
            
            std::string comName = refController["component"].cast<std::string>();
            if(comName == "PlayerDriver"){
                cComPlayerDriver *pDriver;
                pDriver = new cComPlayerDriver(refController, e);
                //TODO: Check if player driver is initialized correctly
                //and if not, print error, and don't add it to entity
                e->AddComponent(std::type_index(typeid(cComPlayerDriver)), 
                                pDriver);
            }else if(comName == "StupidAi"){
                
            }else if(comName == "SmartAi"){
                
            }
        }
    }
    
    SetEntity(e);
}
cComPawn::~cComPawn() {
}
void cComPawn::Move() {
    double tmpSpeed = 5;
    cVector2d tmpVec;
    switch(dir){
        case COM_DIR_N: tmpVec.Set(0, -tmpSpeed); break;
        case COM_DIR_NE: tmpVec.Set(tmpSpeed, -tmpSpeed); break;
        case COM_DIR_E: tmpVec.Set(tmpSpeed, 0); break;
        case COM_DIR_SE: tmpVec.Set(tmpSpeed, tmpSpeed); break;
        case COM_DIR_S: tmpVec.Set(0, tmpSpeed); break;
        case COM_DIR_SW: tmpVec.Set(-tmpSpeed, tmpSpeed); break;
        case COM_DIR_W: tmpVec.Set(-tmpSpeed, 0); break;
        case COM_DIR_NW: tmpVec.Set(-tmpSpeed, -tmpSpeed); break;
    }
    entity->GetLoc()->Add(tmpVec);
}