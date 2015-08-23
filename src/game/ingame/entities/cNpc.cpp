/* 
 * File:   cNpc.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 7:06 PM
 */

#include "cNpc.h"

cNpc::cNpc() {
    type = npc;
}
cNpc::~cNpc() {
}
void cNpc::OnDestroy() {
    UnloadAnimation();
}

