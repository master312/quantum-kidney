/* 
 * File:   sKeyBinds.h
 * Author: master312
 *
 * Created on August 15, 2015, 3:20 AM
 */

#ifndef SKEYBINDS_H
#define	SKEYBINDS_H
#define BIND_MOVE_NORTH 0
#define BIND_MOVE_EAST 1
#define BIND_MOVE_SOUTH 2
#define BIND_MOVE_WEST 3
#include "../../storm/engine.h"

struct sKeyBinds {
    eKey movement[4];

    sKeyBinds(){
        movement[BIND_MOVE_NORTH] = KEY_UP;
        movement[BIND_MOVE_EAST] = KEY_RIGHT;
        movement[BIND_MOVE_SOUTH] = KEY_DOWN;
        movement[BIND_MOVE_WEST] = KEY_LEFT;
    }
};

#endif	/* SKEYBINDS_H */

