/* 
 * File:   cComPawn.h
 * Author: master312
 *
 * Created on September 18, 2015, 7:01 PM
 */

#ifndef CCOMPAWN_H
#define	CCOMPAWN_H
#include "cComponent.h"
#include "hComDefines.h"

class cComPawn : public cComponent {
public:
    cComPawn(luabridge::LuaRef &table, cEntity *e);
    ~cComPawn();
    
    /* Move pawn in direction @dir */
    void Move();
    
    std::string &GetName() { return name; }
    std::string &GetSubName() { return subName; }
    short &GetDir() { return dir; }
    void SetDir(short _dir) { dir = _dir; }
    bool IsMoving() { return isMoving; }
    void SetIsMoving(bool b) { isMoving = b; }
private:
    std::string name;
    std::string subName;
    /* Direction pawn is currently facing */
    short dir;
    bool isMoving;
};

#endif	/* CCOMPAWN_H */

