#include "cStormConsoleCommands.h"
#include "engine.h"

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
    console->AddCommand("set_maxfps", 
                        cStormCallbacker(this, 
                            &cStormConsoleCommands::HandleSimpleCommands));
    console->AddCommand("set_maxticks", 
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
    }else if(strcmp(tmp[0], "set_maxfps") == 0){
        if(tmp[1] == NULL){
            console->PrintLine("Error: You must specify max FPS number");
            return;
        }
        int tmpFps = atoi(tmp[1]);
        if (tmpFps <= 0){
            console->PrintLine("Error: Invalid FPS number.");
            return;
        }
        console->PrintLine("Max FPS set to: %d", tmpFps);
        S_SetMaxFps(tmpFps);
    }else if(strcmp(tmp[0], "set_maxticks") == 0){
        if(tmp[1] == NULL){
            console->PrintLine("Error: You must specify max ticks number");
            return;
        }
        int tmpFps = atoi(tmp[1]);
        if (tmpFps <= 0){
            console->PrintLine("Error: Invalid ticks number.");
            return;
        }
        console->PrintLine("Max number of logic ticks/s set to: %d", tmpFps);
        S_SetMaxLogicTicks(tmpFps);
    }else if(strcmp(tmp[0], "help") == 0){
        console->PrintLine("Available commands:");
        int count = 0;
        std::stringstream ss;
        for(auto &c : S_GetConsole()->GetCustomComs()){
            ss << c.first;
            count ++;
            if(count == 8){
                ss << std::endl;
                count = 0;
            }else{
                ss << ", ";
            }
        }
        ss << std::endl;
        console->PrintLine(ss.str());
    }
}