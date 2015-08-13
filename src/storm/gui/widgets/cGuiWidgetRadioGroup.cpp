#include "cGuiWidgetRadioGroup.h"

cGuiWidgetRadioGroup::cGuiWidgetRadioGroup(std::string _name, int x, int y, int w){
	type = GUI_WIDGET_RADIO;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	selected = -1;
	mouseOver = -1;
	mouseDown = -1;
}
cGuiWidgetRadioGroup::cGuiWidgetRadioGroup(std::string _name, 
		std::vector<std::string> _buttons, int x, int y, int w){
	type = GUI_WIDGET_RADIO;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	selected = -1;
	mouseOver = -1;
	mouseDown = -1;
	for(int i = 0; i < (int)_buttons.size(); i++){
		buttons.push_back(radioButton(_buttons[i]));
	}
}
cGuiWidgetRadioGroup::~cGuiWidgetRadioGroup(){

}
void cGuiWidgetRadioGroup::HandleWidgetEvent(bool isMouseOver){
	if(isMouseOver){
		if(mouseDown != -1){
			goto skip;
		}
		tmpRect.x = loc.x;
		for(int i = 0; i < (int)buttons.size(); i++){
			tmpRect.y = btnSize.h * i + OFFSET + loc.y;
			if(tmpRect.IsCollision(S_GetMouseX(), S_GetMouseY())){
				if(S_IsMouseLeft() && mouseOver == i){
					mouseDown = i;
					goto skip;
				}else{	
					mouseOver = i;
					goto skip;	
				}
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}
		}
		mouseOver = -1;
	}
	skip:
	if(!S_IsMouseLeft()){
		if(mouseDown != -1){
			selected = mouseDown;
			mouseDown = -1;
		}
	}
}
void cGuiWidgetRadioGroup::Render(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_RADIO);
	btnSize.w = S_GetSection(tmp[0])->width;
	btnSize.h = S_GetSection(tmp[0])->height;
	loc.h = btnSize.h * buttons.size();
	tmpRect.x = 3;
	tmpRect.w = btnSize.w;
	tmpRect.h = btnSize.h;
}
void cGuiWidgetRadioGroup::Draw(){
	for(int i = 0; i < (int)buttons.size(); i++){
		DrawButton(i);
	}
}
void cGuiWidgetRadioGroup::DrawButton(int i){
	//S_DrawSection
	radioButton *tmpBtn = &buttons[i];
	uint *tmp = skin->GetSkin(GUI_WIDGET_RADIO);
	tmpRect.x = loc.x;
	tmpRect.y = i * btnSize.h + OFFSET + loc.y;

	if(!tmpBtn->isEnabled){
		if(i == selected)
			S_DrawSection(tmp[1], tmpRect.x, tmpRect.y);
		else
			S_DrawSection(tmp[0], tmpRect.x, tmpRect.y);
	}else{
		if(mouseDown == i){
			//Mouse is down
			if(i == selected)
				S_DrawSection(tmp[7], tmpRect.x, tmpRect.y);
			else
				S_DrawSection(tmp[6], tmpRect.x, tmpRect.y);
		}else if(mouseOver == i){
			//Mouse is over
			if(i == selected)
				S_DrawSection(tmp[5], tmpRect.x, tmpRect.y);
			else
				S_DrawSection(tmp[4], tmpRect.x, tmpRect.y);
		}else{
			//Mouse is not over (normal)
			if(i == selected)
				S_DrawSection(tmp[3], tmpRect.x, tmpRect.y);
			else
				S_DrawSection(tmp[2], tmpRect.x, tmpRect.y);
		}
	}
	S_RenderText(tmpBtn->text, tmpRect.x + btnSize.w + 4, tmpRect.y, skin->GetFont(),
			(float)tmp[8] / 255, (float)tmp[9] / 255, (float)tmp[10] / 255);
}