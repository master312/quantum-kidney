/* 
 * File:   cMapChunk.h
 * Author: master312
 *
 * Created on August 13, 2015, 9:36 PM
 */

#ifndef CMAPCHUNK_H
#define	CMAPCHUNK_H
#include "../sCommon.h"

class cMapChunk {
public:
    cMapChunk();
    ~cMapChunk();
    
    /* Initialise empty chunk, filled with tile 0 */
    void InitEmpty();
    
    
    /* Draw bottom layer on screen, on screen coordinates @x, @y */
    void DrawBot(int x, int y);
    /* Draw top layer on screen, on screen coordinates @x, @y */
    void DrawTop(int x, int y);
private:

};

#endif	/* CMAPCHUNK_H */

