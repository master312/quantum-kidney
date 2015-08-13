#include "cGuiWidgetButton.h"

cGuiWidgetButton::cGuiWidgetButton(std::string _name, std::string _text, int x, int y, bool _isEnabled){
	type = GUI_WIDGET_BUTTON;
	name = _name;
	text = _text;
	loc.x = x;
	loc.y = y;
	state = 0;
	isEnabled = _isEnabled;
}
cGuiWidgetButton::cGuiWidgetButton(std::string _name, std::string _text, int x, int y, bool _isEnabled, 
		cStormCallbacker _callback){
	type = GUI_WIDGET_BUTTON;
	name = _name;
	text = _text;
	loc.x = x;
	loc.y = y;
	state = 0;
	isEnabled = _isEnabled;
	callback = _callback;
}
cGuiWidgetButton::~cGuiWidgetButton(){

}
void cGuiWidgetButton::SetCallBack(cStormCallbacker _callback){
	callback = _callback;
}
void cGuiWidgetButton::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
	Render();
}
void cGuiWidgetButton::HandleWidgetEvent(bool isMouseOver){
	if(!isEnabled)
		return;
	if(isMouseOver){
		if(S_IsMouseLeft()){
			state = 2;
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}else{
			if(state == 2){
				callback();
				state = 1;
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}else{
				state = 1;
			}
		}
	}else{
		state = 0;
	}
}
void cGuiWidgetButton::Render(){
	if(textLoc.w == 0 && textLoc.y == 0)
		textLoc = S_GetTextSize(text, skin->GetFont());
	textLoc.x = loc.x + 5;
	textLoc.y = loc.y + 5;
	loc.w = textLoc.w + 10;
	loc.h = textLoc.h + 10;
	
	uint *tmp = skin->GetSkin(GUI_WIDGET_BUTTON);
	bLeft = loc;
	bLeft.w = S_GetSection(tmp[1])->width;
	bRight = bLeft;
	bRight.x += loc.w + 1;
	bRight.x -= S_GetSection(tmp[5])->width;
	loc.w -= (S_GetSection(tmp[5])->width / 2);
	// destRight.x = loc.x + loc.w - S_GetSection(tmp[0])->width;
	// destRight.y = loc.y;
}
void cGuiWidgetButton::Draw(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_BUTTON);
	if(!isEnabled){
		S_DrawSectionScaled(tmp[0], &loc);
	}else{
		switch(state){
			case 0:
				S_DrawSectionScaled(tmp[3], &loc);
				S_DrawSectionScaled(tmp[4], &bLeft);
				S_DrawSectionScaled(tmp[5], &bRight);
				break;
			case 1:
				S_DrawSectionScaled(tmp[6], &loc);
				S_DrawSectionScaled(tmp[7], &bLeft);
				S_DrawSectionScaled(tmp[8], &bRight);
				break;
			case 2:
				S_DrawSectionScaled(tmp[9], &loc);
				S_DrawSectionScaled(tmp[10], &bLeft);
				S_DrawSectionScaled(tmp[11], &bRight);
				break;
		}
	}
	if(state == 2){
		S_RenderText(text, textLoc.x + 1, textLoc.y + 1, skin->GetFont(),
			(float)tmp[12] / 255, (float)tmp[13] / 255, (float)tmp[14] / 255);
	}else{
		S_RenderText(text, textLoc.x, textLoc.y, skin->GetFont(),
			(float)tmp[12] / 255, (float)tmp[13] / 255, (float)tmp[14] / 255);
	}
}