#include "cStormConsole.h"

cStormConsole::cStormConsole() {
}
cStormConsole::~cStormConsole() {
}
void cStormConsole::Init() {
    S_AddEventHandler(
                    new cStormCallbacker(this, &cStormConsole::HandleEvents), 
                    "0001a_cStormConsole"); //Dirty event callback priority hack...
    key = KEY_F4;
    onScreen = false;
    maxLogLines = STORM_CONSOLE_DEFAULT_LOG_HISTORY;
    height = STORM_CONSOLE_DEFAULT_HEIGHT;
    locY = height * S_GetFont("default")->newLine + 32;
    scrollY = 0;
    curHistory = 0;
}
void cStormConsole::HandleEvents(void *data) {
    if(!onScreen) {
        if(S_IsKeyDown(key)){
            Show();
        }
        return;
    }
    if(S_IsKeyDown(key)){
        Hide();
        return;
    }
    
    S_EatEvent("0001a_cStormConsole");
    
    if(S_IsTextInput()){
        if(S_IsKeyDown(KEY_RETURN) && S_GetTextInput().size() > 0){
            if(cmdHistory.size() == 0 ||
                cmdHistory[cmdHistory.size() - 1].compare(S_GetTextInput()) != 0){
                
                cmdHistory.push_back(S_GetTextInput());
                if(cmdHistory.size() > STORM_CONSOLE_DEFAULT_HISTORY_MAX){
                    cmdHistory.erase(cmdHistory.begin());
                }
            }
            
            std::string command;
            std::string arguments;
            
            int commandEnd = S_GetTextInput().find(" ");
            if(commandEnd > 0) {
                command = S_GetTextInput().substr(0, commandEnd);
                commandEnd += 1;
                int argEnd = S_GetTextInput().size() - commandEnd;
                arguments = S_GetTextInput().substr(commandEnd, argEnd);
            }else{
                command = S_GetTextInput();
            }

            std::transform(command.begin(), 
                           command.end(), 
                           command.begin(), 
                           to_lower());     
            
            if(commands.count(command) == 0){
                PrintLine("Command '%s' not found", command.c_str());
            }else{
                const char *tmp[2];
                tmp[0] = command.c_str();
                
                if(arguments.size() > 0)
                    tmp[1] = arguments.c_str();
                else
                    tmp[1] = NULL;
                
                commands[command].Call((void*)tmp);
            }
            S_StopTextInput();
            curHistory = cmdHistory.size();
        }else if(S_IsKeyDown(KEY_RETURN)){
            S_StopTextInput();
            curHistory = cmdHistory.size();
        }else if(S_IsKeyDown(KEY_UP)){
            if(cmdHistory.size() == 0)
                return;
            
            curHistory --;
            if(curHistory < 0)
                curHistory = cmdHistory.size() - 1;
            
            S_GetInputManager()->strText = cmdHistory[curHistory];
        }else if(S_IsKeyDown(KEY_ESCAPE)){
            S_GetInputManager()->strText.clear();
            curHistory = cmdHistory.size();
        }
        return;
    }
    
    if(S_IsKeyDown(KEY_RETURN)){
        S_StartTextInput();
    }
}
void cStormConsole::Draw() {
    if(!onScreen){
        return;
    }
    S_DrawFillRect(0, 0, S_GetWindowSize().w, locY, 0, 0, 0, 0.6f);
    
    for(int i = scrollY; i < logLines.size(); i++){
        S_RenderText(logLines[i], 1, 
                    (i - scrollY) * S_GetFont("default")->newLine, 
                    "default", 1, 1, 1);
    }
    
    if(S_IsTextInput()) {
        S_DrawRect(0, locY - 30, S_GetWindowSize().w, 29, 1, 1, 1, 0.9f);
        if(curHistory != cmdHistory.size()){
            S_RenderText(S_GetTextInput(), 5, locY - 28, "default", 
                0.70f, 0.75f, 0.90f);
        }else{
            S_RenderText(S_GetTextInput(), 5, locY - 28, "default", 
                            0.95f, 0.95f, 0.95f);   
        }
    }else{
        S_DrawRect(0, locY - 30, S_GetWindowSize().w, 29, 1, 1, 1, 0.3f);
    }
}
void cStormConsole::Show() {
    if(onScreen)
        return;
    onScreen = true;
    curHistory = cmdHistory.size();
    S_StartTextInput();
}
void cStormConsole::Hide() {
    if(!onScreen)
        return;
    onScreen = false;
    S_StopTextInput();
}
void cStormConsole::PrintLine(std::string text, ...) {
    int count = 0;
    for(uint i = 0; i < text.size(); i++){
        if(text[i] == '%'){
            count ++;
        }
    }
    
    va_list ap;
    va_start(ap, count);
    logLines.push_back(StormParseArgs(text, count, ap));
    va_end(ap);
    
    if(logLines.size() > maxLogLines){
        //TODO: Delete log lines
        std::cout << "cStormConsole TODO: IN PrintLine(...)" << std::endl;
    }
    
    if(logLines.size() > height){
        scrollY = logLines.size() - height;
    }
}