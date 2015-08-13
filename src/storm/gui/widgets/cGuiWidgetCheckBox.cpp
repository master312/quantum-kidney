#include "cGuiWidgetCheckBox.h"

cGuiWidgetCheckBox::cGuiWidgetCheckBox(std::string _name, int x, int y, 
							bool value, bool _isEnabled){
	name = _name;
	type = GUI_WIDGET_CHECKBOX;
	loc.x = x;
	loc.y = y;
	isEnabled = _isEnabled;
	isChecked = value;
	label = "";
	state = 0;
	side = false;
}
cGuiWidgetCheckBox::cGuiWidgetCheckBox(std::string _name, std::string _label, 
		int x, int y, bool value, bool _isEnabled){
	name = _name;
	type = GUI_WIDGET_CHECKBOX;
	loc.x = x;
	loc.y = y;
	isEnabled = _isEnabled;
	isChecked = value;
	label = _label;
	state = 0;
	side = false;
}
cGuiWidgetCheckBox::~cGuiWidgetCheckBox(){

}
void cGuiWidgetCheckBox::HandleWidgetEvent(bool isMouseOver){
	if(!isEnabled)
		return;
	if(isMouseOver){
		if(S_IsMouseLeft() && state == 1){
			state = 2;
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}else if(!S_IsMouseLeft() && state == 2){
			isChecked = !isChecked;
			state = 1;
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}else if(!S_IsMouseLeft()){
			state = 1;
		}
	}else{
		if(!S_IsMouseLeft()){
			state = 0;
		}else if(state != 2){
			state = 0;
		}
	}
}
void cGuiWidgetCheckBox::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
	Render();
}
void cGuiWidgetCheckBox::Render(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_CHECKBOX);
	loc.w = S_GetSection(tmp[0])->width;
	loc.h = S_GetSection(tmp[0])->height;
	//loc.x -= labelLoc.w + 1;
	if(label != ""){
		labelLoc = S_GetTextSize(label, skin->GetFont());
		if(side){
			labelLoc.x = loc.x - (labelLoc.w + 1);
			labelLoc.y = loc.y;
			loc.x = labelLoc.x + labelLoc.w + 1;
		}else{
			labelLoc.x = loc.x + loc.w + 1;
			labelLoc.y = loc.y;
		}
	}
}
void cGuiWidgetCheckBox::Draw(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_CHECKBOX);
	if(label != ""){
		S_RenderText(label, labelLoc.x, labelLoc.y, skin->GetFont(), 
			(float)tmp[8] / 255, (float)tmp[9] / 255, (float)tmp[10] / 255);
	}
	if(!isEnabled){
		if(isChecked){
			S_DrawSection(tmp[1], loc.x, loc.y);
		}else{
			S_DrawSection(tmp[0], loc.x, loc.y);
		}
	}else{
		switch(state){
			case 0:	//Normal
				if(isChecked)
					S_DrawSection(tmp[3], loc.x, loc.y);
				else
					S_DrawSection(tmp[2], loc.x, loc.y);
				break;
			case 1:	//Over
				if(isChecked)
					S_DrawSection(tmp[5], loc.x, loc.y);
				else
					S_DrawSection(tmp[4], loc.x, loc.y);
				break;
			case 2:	//Down
				if(isChecked)
					S_DrawSection(tmp[7], loc.x, loc.y);
				else
					S_DrawSection(tmp[6], loc.x, loc.y);
				break;
		}
	}
}