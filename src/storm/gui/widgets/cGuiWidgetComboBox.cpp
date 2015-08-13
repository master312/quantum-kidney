#include "cGuiWidgetComboBox.h"

cGuiWidgetComboBox::cGuiWidgetComboBox(std::string _name, int x, int y, int w, int h, 
		bool _isEnabled, std::vector<std::string> *vec){
	type = GUI_WIDGET_COMBOBOX;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = h;
	isEnabled = _isEnabled;
	selected = -1;
	isOver = false;
	isExtended = false;
	itemHeight = 1;
	AddItems(vec);
}
cGuiWidgetComboBox::cGuiWidgetComboBox(std::string _name, sRect _loc, bool _isEnabled, std::vector<std::string> *vec){
	type = GUI_WIDGET_COMBOBOX;
	name = _name;
	loc = _loc;
	isEnabled = _isEnabled;
	selected = -1;
	isOver = false;
	isExtended = false;
	itemHeight = 1;
	AddItems(vec);
}
cGuiWidgetComboBox::~cGuiWidgetComboBox(){

}
void cGuiWidgetComboBox::HandleWidgetEvent(bool isMouseOver){
	if(isMouseOver){
		isOver = true;
		if(S_IsMouseLeft()){
			isDown = true;
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}else if(isDown){
			isDown = false;
			isExtended = !isExtended;
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}
	}else{
		isOver = false;
		if(S_IsMouseLeft() && isExtended){
			isDown = false;
			if(destExtend.IsCollision(S_GetMouseX(), S_GetMouseY())){
				if(items.size() == 0)
					return;
				selected = (int)((S_GetMouseY() - destExtend.y) / itemHeight);
				if(selected >= (int)items.size())
					selected = items.size() - 1;
				isExtended = false;
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}else{
				isExtended = false;
			}
		}else if(isDown){
			isDown = false;
		}else if(isExtended){
			over = (int)((S_GetMouseY() - destExtend.y) / itemHeight);
		}
	}
}
void cGuiWidgetComboBox::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
	Render();
}
void cGuiWidgetComboBox::AddItems(std::vector<std::string> *vec){
	for(int i = 0; i < (int)vec->size(); i++){
		items.push_back(vec->at(i));
	}
}
void cGuiWidgetComboBox::AddItem(std::string _item){
	items.push_back(_item);
	destExtend.h = itemHeight * items.size() + 2;
}
std::string cGuiWidgetComboBox::GetSelectedItem(){
	if(selected > -1)
		return items[selected];
	return "";
}
void cGuiWidgetComboBox::RemoveItem(std::string _name){
	for(int i = 0; i < (int)items.size(); i++){
		if(items[i] == _name){
			items.erase(items.begin() + i);
			destExtend.h = itemHeight * items.size() + 2;
			return;
		}
	}
}
void cGuiWidgetComboBox::Render(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_COMBOBOX);
	//sRect destMid, destLeft, destRight;
	destLeft = loc;
	destLeft.w = S_GetSection(tmp[1])->width;

	destRight = loc;
	destRight.w = S_GetSection(tmp[2])->width;
	destRight.x += loc.w - destRight.w;

	destMid = loc;
	destMid.x += destLeft.w;
	destMid.w -= destLeft.w + destRight.w;

	arrowRight = loc;
	arrowRight.w =  S_GetSection(tmp[3])->width;
	arrowRight.h =  S_GetSection(tmp[3])->height;
	arrowRight.x += loc.w - arrowRight.w - arrowRight.w / 2;
	arrowRight.y += (destLeft.h / 2) - (arrowRight.h / 2);

	destExtend = loc;
	destExtend.y += destMid.h;
	destExtend.h = 80;

	itemHeight = S_GetFont(skin->GetFont())->newLine;
	
	destExtend.h = itemHeight * items.size() + 2;

	selectedItem = destExtend;
	selectedItem.h = itemHeight;
}
void cGuiWidgetComboBox::Draw(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_COMBOBOX);
	if(isEnabled){
		if(isOver){
			//Over
			S_DrawSectionScaled(tmp[8], &destMid);
			S_DrawSectionScaled(tmp[9], &destLeft);
			S_DrawSectionScaled(tmp[10], &destRight);
			if(!isDown)
				S_DrawSectionScaled(tmp[11], &arrowRight);
			else
				S_DrawSectionScaled(tmp[12], &arrowRight);
		}else{
			//Enabled, not over
			S_DrawSectionScaled(tmp[4], &destMid);
			S_DrawSectionScaled(tmp[5], &destLeft);
			S_DrawSectionScaled(tmp[6], &destRight);
			S_DrawSectionScaled(tmp[7], &arrowRight);
		}
		//Selected item ID in skin is 15...
		if(isExtended){
			S_DrawSectionScaled(tmp[12], &arrowRight); //'Down' arrow
			S_DrawSectionScaled(tmp[13], &destExtend);
			std::map<uint, std::string>::iterator i;
			for(int i = 0; i < (int)items.size(); i++){
				if(i == over){
					selectedItem.y = destExtend.y + (i * itemHeight);
					S_DrawSectionScaled(tmp[15], &selectedItem);
				}
				S_RenderText(items[i], destExtend.x + 1, destExtend.y + (i * itemHeight), 
					skin->GetFont(), (float)tmp[16] / 255, (float)tmp[17] / 255, (float)tmp[18] / 255);
				
			}
		}
	}else{
		//Disabled
		S_DrawSectionScaled(tmp[0], &destMid);
		S_DrawSectionScaled(tmp[1], &destLeft);
		S_DrawSectionScaled(tmp[2], &destRight);
		S_DrawSectionScaled(tmp[3], &arrowRight);
	}
	if(selected > -1){
		S_RenderText(items[selected], destLeft.x + destLeft.w, destLeft.y + 2, 
			skin->GetFont(), (float)tmp[16] / 255, (float)tmp[17] / 255, (float)tmp[18] / 255);
	}
}