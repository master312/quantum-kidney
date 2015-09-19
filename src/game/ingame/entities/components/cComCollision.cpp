#include "cComCollision.h"

cComCollision::cComCollision(luabridge::LuaRef &table, cEntity *e) {
    luabridge::LuaRef x = table["x"];
    luabridge::LuaRef y = table["y"];
    luabridge::LuaRef width = table["width"];
    luabridge::LuaRef height = table["height"];
    luabridge::LuaRef on_intersect = table["on_intersect"];
    
    if(!x.isNil() && x.isNumber()){
        rect.x = x.cast<int>();
    }
    if(!y.isNil() && y.isNumber()){
        rect.y = y.cast<int>();
    }
    if(!width.isNil() && width.isNumber()){
        rect.w = width.cast<int>();
    }
    if(!height.isNil() && height.isNumber()){
        rect.h = height.cast<int>();
    }
    //TODO: on_intersect callback!
    
    SetEntity(e);
}
cComCollision::~cComCollision() {
}

