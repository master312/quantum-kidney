#include "cGuiWidgetList.h"

cGuiWidgetList::cGuiWidgetList(std::string _name, int x, int y, int w, int h, std::vector<std::string> *_items){
	type = GUI_WIDGET_LIST;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = h;
	selected = -1;
	selectable = true;
	if(_items != NULL)
		SetItemList(_items);
}
cGuiWidgetList::cGuiWidgetList(std::string _name, sRect _loc, std::vector<std::string> *_items){
	type = GUI_WIDGET_LIST;
	name = _name;
	loc = _loc;
	selected = -1;
	selectable = true;
	if(_items != NULL)
		SetItemList(_items);
}
cGuiWidgetList::~cGuiWidgetList(){

}

void cGuiWidgetList::SetItemList(std::vector<std::string> *_items){
	items.clear();
	for(int i = 0; i < (int)_items->size(); i++){
		items.push_back(_items->at(i));
	}
}
void cGuiWidgetList::RemoveItem(std::string item){
	for(int i = 0; i < (int)items.size(); i++){
		if(items[i] == item){
			if(selected >= i)
				selected --;
			items.erase(items.begin() + i);
			return;
		}
	}
}
std::string cGuiWidgetList::GetSelected(){
	if(selected > -1 && selected < (int)items.size()){
		return items[selected];
	}
	return "";
}
int cGuiWidgetList::GetSelectedOrd(){
	return selected;
}
void cGuiWidgetList::SetSelected(std::string item){
	for(int i = 0; i < (int)items.size(); i++){
		if(items[i] == item){
			selected = i;
		}
	}
}
void cGuiWidgetList::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
}
void cGuiWidgetList::HandleWidgetEvent(bool isMouseOver){
	if(!isMouseOver || !S_IsMouseLeft())
		return;
	int ns = (S_GetMouseY() - loc.y) / itemHeight;
	if(selected != ns){
		selected = ns;
		callback.Call();
		toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
	}else{
		return;
	}

	if(selected >= (int)items.size()){
		selected = items.size() - 1;
	}else if(selected < 0){
		selected = 0;
	}
}
void cGuiWidgetList::Render(){
	itemHeight = S_GetTextSize("TMLP", skin->GetFont()).h;
}
void cGuiWidgetList::Draw(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_LIST);
	S_DrawSectionScaled(tmp[4], &loc);
	for(int i = 0; i < (int)items.size(); i++){
		if(selected == i){
			S_DrawFillRect(loc.x, loc.y + (i * itemHeight) + 1, loc.w, 
							itemHeight, 1.0);
		}
		S_RenderText(items[i], loc.x, loc.y + (i * itemHeight) + 1, skin->GetFont());
	}
}