#include "cComPlayerDriver.h"
#include "../systems/cSysPlayerDriver.h"
#include "../cEntityManager.h"

cComPlayerDriver::cComPlayerDriver(luabridge::LuaRef &table, cEntity *e) {
    
    SetEntity(e);
    GetCommon()->entityManager->GetSystem<cSysPlayerDriver>()->Register(this);
}
cComPlayerDriver::~cComPlayerDriver() {
}