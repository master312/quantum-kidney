/* 
 * File:   cStormConsoleCommands.cpp
 * Author: master312
 * 
 * Created on August 24, 2015, 5:10 AM
 */

#include "cStormConsoleCommands.h"

cStormConsoleCommands::cStormConsoleCommands(cStormConsole *_console) {
    console = _console;
    console->AddCommand("quit", 
                        cStormCallbacker(this, 
                            &cStormConsoleCommands::HandleSimpleCommands));
    console->AddCommand("print", 
                        cStormCallbacker(this, 
                            &cStormConsoleCommands::HandleSimpleCommands));
    console->AddCommand("debug", 
                        cStormCallbacker(this, 
                            &cStormConsoleCommands::HandleSimpleCommands));
    console->AddCommand("help", 
                        cStormCallbacker(this, 
                            &cStormConsoleCommands::HandleSimpleCommands));
    
}
cStormConsoleCommands::~cStormConsoleCommands() {
}
void cStormConsoleCommands::HandleSimpleCommands(void *data) {
    char **tmp = (char**)data;
    if(strcmp(tmp[0], "quit") == 0){
        S_Stop();
    }else if(strcmp(tmp[0], "print") == 0){
        if(tmp[1] != NULL)
            console->PrintLine(": %s", tmp[1]);
        else
            console->PrintLine("Printing emptiness....");
    }else if(strcmp(tmp[0], "debug") == 0){
        if(tmp[1] == NULL){
            console->PrintLine("Error: Command must have argument 1 or 0");
            return;
        }
        if(tmp[1][0] == '0'){
            S_SetDebugMode(false);
            console->PrintLine("Debug mode disabled");
        }else{
            S_SetDebugMode(true);
            console->PrintLine("Debug mode enabled");
        }
    }else if(strcmp(tmp[0], "help") == 0){
        console->PrintLine("Available commands: (all commands may not be displayed)");
        console->PrintLine("help, quit, print, debug");
    }
}