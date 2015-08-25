//Created by Petar Ostojic;
//Mon August 24 03:04:12 2015
//Console is available only in debug mode
#ifndef CSTORMCONSOLE_H
#define	CSTORMCONSOLE_H
#include "cStormCallbacker.h"
#include "engine.h"
#include <map>
#include <algorithm>
#include <string>

struct to_lower {
    int operator() (int ch){
        return std::tolower(ch);
    }
};

class cStormConsole {
public:
    cStormConsole();
    ~cStormConsole();
    
    void Init();
    void HandleEvents(void *data);
    void Draw();
    
    void Show();
    void Hide();
    void PrintLine(std::string text, ...);
    void PushLogLine(std::string text);
    void AddCommand(std::string name, cStormCallbacker cb) {
        if(commands.count(name) > 0){
            StormPrintLog(STORM_LOG_WARNING, "cStormConsole",
                        "Console command '%s' has been overriden", name.c_str());
        }
        commands[name] = cb;
    }
    void RemoveCommand(std::string command) {
        commands.erase(command);
    }
    
    void SetShortkey(eKey _key) { key = _key; }
    bool IsOnScreen() { return onScreen; }
private:
    //This map contains command names and their callback methods
    std::map<std::string, cStormCallbacker> commands;
    //All log lines drawn in console
    std::vector<std::string> logLines;
    //Maximum number of log lines
    int maxLogLines;
    //Log lines scrolling
    int scrollY;
    //Shortkey used to show console
    eKey key;
    //Is console showen on screen
    bool onScreen;
    //Draw location y. Used for console sliding in effect
    int locY;
    //Console height in number of log lines
    int height;
    //Command history
    std::vector<std::string> cmdHistory;
    int curHistory;
};

#endif	/* CCONSOLE_H */

