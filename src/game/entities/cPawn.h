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

class cPawn : public cEntity {
public:
    cPawn();
    virtual ~cPawn();
    
    /* Load sprites (animation) for this pawn
     * animationId or spriteId must be set before calling this method */
    void LoadSprite();
    
    /* Draws this pawn on screen */
    void Draw();

    void SetSpriteId(int _spriteId) { spriteId = _spriteId; }
    int GetSpriteId() { return spriteId; }
    void SetAnimId(int _animId) { animationId = _animId; }
    int GetAnimId() { return animationId; }
    void SetName(std::string _name) { name = _name; }
    std::string GetName() { return name; }
    void SetSubName(std::string _name) { subName = _name; }
    std::string GetSubName() { return subName; }
protected:
    /* This variable is used for debug only */
    int spriteId;
    uint spriteTexture;
    /* Animation ID */
    int animationId;
    /* Animation ID in storm framework animaiton handler*/
    uint animId;
    
    std::string name;
    std::string subName;
    
    /* Pawn stats */
    sStats stats;
    
    void UnloadSprites();
};

#endif	/* CPAWN_H */

