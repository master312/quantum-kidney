//Created by Petar Ostojic;
//Mon Feb 16 20:47:17 2015
//This class contains callback functions for 
//console commands that are integrated into storm framework
#ifndef CSTORMCONSOLECOMMANDS_H
#define	CSTORMCONSOLECOMMANDS_H
#include "cStormConsole.h"

class cStormConsoleCommands {
public:
    cStormConsoleCommands(cStormConsole *_console);
    ~cStormConsoleCommands();
    
    //This method handles all simple console commands
    //like quit, fullscreen, etc...
    void HandleSimpleCommands(void *data);
private:
    cStormConsole *console;
};

#endif	/* CSTORMCONSOLECOMMANDS_H */

