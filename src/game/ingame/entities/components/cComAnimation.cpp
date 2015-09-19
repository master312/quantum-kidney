#include "cComAnimation.h"
#include "../cEntityManager.h"
#include "../systems/cSysAnimation.h"
#include "../../../sCommon.h"

cComAnimation::cComAnimation(luabridge::LuaRef &table, cEntity *e) {
    animId = 0;
    
    luabridge::LuaRef fName = table["filename"];
    if(fName.isNil() || !fName.isString()){
        StormPrintLog(STORM_LOG_ERROR, "cComAnimation", 
                "Could not create Com_Animation. Filename invalid");
        return;
    }
    std::string filename = fName.cast<std::string> ();
    
    animId = S_LoadAnimation(filename);
    
    if(animId > 0){
        GetCommon()->entityManager->GetSystem<cSysAnimation>()->Register(this);
    }
    
    SetEntity(e);
}
cComAnimation::~cComAnimation() {
    if(animId > 0){
        S_RemoveAnimation(animId);
        GetCommon()->entityManager->GetSystem<cSysAnimation>()->UnRegister(this);
    }
}

