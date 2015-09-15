/* 
 * File:   main.cpp
 * Author: master312
 *
 * Created on August 13, 2015, 7:58 PM
 * TEst
 */
#include "game/cGame.h"

#ifdef OS_WINDOWS
#undef main
#endif

int main(int argc, char** argv) {
//    lua_State* L = luaL_newstate();
//    luaL_openlibs(L);
//    getGlobalNamespace(L).addFunction("printMessage", printMessage);
//    
//    
//    if (luaL_loadfile(L, "script.lua") || lua_pcall(L, 0, 0, 0)) {
//        std::cout << "Script not loaded!" << std::endl;
//        return -1;
//    }
//    std::cout << "Loaded lua"  << std::endl;
//
//    
//    
//    LuaRef s = getGlobal(L, "testString");
//    LuaRef n = getGlobal(L, "number");
//    
//    if(s.isNil() || n.isNil()){
//        std::cout << "Variable not found!|" << std::endl;
//        return -1;
//    }
//    
//    std::string luaString = s.cast<std::string>();
//    int answer = n.cast<int>();
//    std::cout << luaString << std::endl;
//    std::cout << "And here's our number:" << answer << std::endl;
//
//    
//    
//    LuaRef t = getGlobal(L, "window");
//    LuaRef title = t["title"];
//    LuaRef w = t["width"];
//    LuaRef h = t["height"];
//    std::string titleString = title.cast<std::string>();
//    int width = w.cast<int>();
//    int height = h.cast<int>();
//    std::cout << titleString << std::endl;
//    std::cout << "width = " << width << std::endl;
//    std::cout << "height = " << height << std::endl;
//    
//    
//    
//    LuaRef sumNumbers = t["sumNumbers"];
//    //sumNumbers.isFunction()
//    if(sumNumbers.isTable()){
//        std::cout << "IsTable..." << std::endl;
//    }
//    
//    if(!sumNumbers.isNil()) {
//        int result = sumNumbers(5, 4, 4, 434, "milenium");
//        std::cout << "ResultENd :" << result << std::endl;
//    }else {
//        std::cout << "SumNubers function not found in lua script" << std::endl;
//    }
    
    cGame *g = new cGame();
    g->Start();
    delete g;

    return 0;
}

