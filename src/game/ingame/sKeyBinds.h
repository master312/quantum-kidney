/* 
 * File:   sKeyBinds.h
 * Author: master312
 *
 * Created on August 15, 2015, 3:20 AM
 */

#ifndef SKEYBINDS_H
#define	SKEYBINDS_H
#define BIND_MOVE_UP 0
#define BIND_MOVE_RIGHT 1
#define BIND_MOVE_DOWN 2
#define BIND_MOVE_LEFT 3
#include "../../storm/engine.h"

struct sKeyBinds {
    eKey movement[4];

    sKeyBinds(){
        movement[BIND_MOVE_UP] = KEY_UP;
        movement[BIND_MOVE_RIGHT] = KEY_RIGHT;
        movement[BIND_MOVE_DOWN] = KEY_DOWN;
        movement[BIND_MOVE_LEFT] = KEY_LEFT;
    }
};

#endif	/* SKEYBINDS_H */

