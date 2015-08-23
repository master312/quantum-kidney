/* 
 * File:   cPawn.h
 * Author: master312
 *
 * Created on August 14, 2015, 7:05 PM
 */

#ifndef CPAWN_H
#define	CPAWN_H
#include "cEntity.h"
#include "../sStats.h"
#define PAWN_DIR_NORTH 0x0001
#define PAWN_DIR_EAST 0x0010
#define PAWN_DIR_SOUTH 0x0100
#define PAWN_DIR_WEST 0x1000

class cPawn : public cEntity {
public:
    cPawn();
    virtual ~cPawn();
    
    /* Load animation for this pawn
     * animationId or spriteId must be set before calling this method */
    void LoadAnim();
    
    /* Draws this pawn on screen */
    void Draw();

    void SetAnimId(int _animId) { animationId = _animId; }
    int GetAnimId() { return animationId; }
    cAnimation *GetAnimation() { return S_GetAnimation(animId); }
    void SetName(std::string _name) { name = _name; }
    std::string GetName() { return name; }
    void SetSubName(std::string _name) { subName = _name; }
    std::string GetSubName() { return subName; }
    sStats *GetStats() { return &stats; }
    void SetDirection(short dir) { direction = dir; }
    void PushDirection(short dir) { direction |= dir; }
    short GetDirection() { return direction; }
    bool IsMoving() { return isMoving; }
    void SetIsMoving(bool m) { isMoving = m; }
protected:
    /* Animation ID */
    int animationId;
    /* Animation ID in storm framework animation handler */
    uint animId;
    /* What direction is pawn facing */
    short direction;
    /* Is pawn moving */
    bool isMoving;
    
    std::string name;
    std::string subName;
    
    /* Pawn stats */
    sStats stats;
    
    void UnloadAnimation();
};

#endif	/* CPAWN_H */

