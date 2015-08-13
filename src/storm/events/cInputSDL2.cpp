#include "cInputSDL2.h"

cInputSDL2::cInputSDL2(){

}
cInputSDL2::~cInputSDL2(){

}
bool cInputSDL2::Update(){
	if(SDL_PollEvent(&EVENT)){
        isNew = true;
		switch(EVENT.type){
            case SDL_WINDOWEVENT:
                switch(EVENT.window.event){
                    case SDL_WINDOWEVENT_RESIZED:
                        graphics->ResizeWindow(EVENT.window.data1, EVENT.window.data2);
                        break;
                }
                break;
			case SDL_QUIT:
				toQuit = true;
				break;
            case SDL_TEXTINPUT:
                if(textScan){
                    strText += EVENT.text.text;
                }
                break;
            case SDL_KEYDOWN:{
                SDL_Keycode tmpKey = EVENT.key.keysym.sym;
                if(textScan){
                    if(tmpKey == SDLK_LEFT || tmpKey == SDLK_RIGHT || tmpKey == SDLK_UP ||
                        tmpKey == SDLK_DOWN || (tmpKey >= SDLK_F1 && tmpKey <= SDLK_F15) || 
                        tmpKey == SDLK_ESCAPE || tmpKey == SDLK_BACKSPACE || 
                        tmpKey == SDLK_RSHIFT || tmpKey == SDLK_LSHIFT || tmpKey == SDLK_RCTRL ||
                        tmpKey == SDLK_LCTRL || tmpKey == SDLK_RALT || tmpKey == SDLK_LALT ||
                        tmpKey == KEY_RETURN || tmpKey == SDLK_KP_ENTER || tmpKey == SDLK_TAB){
                        
                        keys[tmpKey] = 'd';

                        if(tmpKey == SDLK_BACKSPACE){
                            if(strText.size() > 0){
                                strText.erase(strText.size() - 1);
                            }
                        }
                    }
                    break;
                }
				keys[tmpKey] = 'd';
				break;}
			case SDL_KEYUP:
                if(keys.count(EVENT.key.keysym.sym) != 0)
				    keys.erase(keys.find(EVENT.key.keysym.sym));
				break;
            case SDL_MOUSEMOTION:
                mouseX = EVENT.motion.x;
                mouseY = EVENT.motion.y;
                break;
            case SDL_MOUSEBUTTONUP:
            	if(EVENT.button.button == SDL_BUTTON_LEFT){
            		mouseButton[MOUSE_BUTTON_LEFT] = false;
            	}else if(EVENT.button.button == SDL_BUTTON_RIGHT){
            		mouseButton[MOUSE_BUTTON_RIGHT] = false;
            	}else if(EVENT.button.button == SDL_BUTTON_MIDDLE){
            		mouseButton[MOUSE_BUTTON_MIDDLE] = false;
            	}
                break;
            case SDL_MOUSEBUTTONDOWN:
            	if(EVENT.button.button == SDL_BUTTON_LEFT){
            		mouseButton[MOUSE_BUTTON_LEFT] = true;
            	}else if(EVENT.button.button == SDL_BUTTON_RIGHT){
            		mouseButton[MOUSE_BUTTON_RIGHT] = true;
            	}else if(EVENT.button.button == SDL_BUTTON_MIDDLE){
            		mouseButton[MOUSE_BUTTON_MIDDLE] = true;
            	}
                break;
            case SDL_MOUSEWHEEL:
                mouseScroll = EVENT.wheel.y;
                break;
			default:
				break;
		}
        return true;
	}
    return false;
}