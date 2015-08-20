#include "cGuiWidgetContainer.h"

cGuiWidgetContainer::cGuiWidgetContainer(std::string _name, std::string _title, int x, int y, int w, int h){
	name = _name;
	title = _title;
	type = GUI_WIDGET_CONTAINER;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = h;
	showTitleBar = true;
	showCloseButton = true;
	isResizable = true;
	isMovable = true;
	closeButtonState = 0;
	resizeDir = 0;
	isResize = false;
}
cGuiWidgetContainer::cGuiWidgetContainer(std::string _name, std::string _title, int x, int y, 
		int w, int h, bool showTitle, bool showClose, bool _isResizable, bool _isMovable){
	name = _name;
	title = _title;
	type = GUI_WIDGET_CONTAINER;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = h;
	showTitleBar = showTitle;
	showCloseButton = showClose;
	isResizable = _isResizable;
	isMovable = _isMovable;
	closeButtonState = 0;
	resizeDir = 0;
	isResize = false;
}
cGuiWidgetContainer::~cGuiWidgetContainer(){
	for(int i = 0; i < (int)children.size(); i++){
		delete children[i];
	}
}

void cGuiWidgetContainer::AddChild(cGuiWidget *_child){
	if(_child->skin == NULL)
		_child->skin = skin;
        if(showTitleBar) {
		_child->SetLoc(_child->loc.x + loc.x, 
                                _child->loc.y + loc.y + titleBarRect[0].h);
        } else {
		_child->SetLoc(_child->loc.x + loc.x, _child->loc.y + loc.y);
        }
	_child->Render();
	children.push_back(_child);
}
int cGuiWidgetContainer::GetChildCount(){
	return (int)children.size();
}
cGuiWidget *cGuiWidgetContainer::GetChild(int id){
	return children[id];	
}
void cGuiWidgetContainer::UpdatePosition(int newX, int newY){
	for(int i = 0; i < (int)children.size(); i++){
		children[i]->UpdatePosition(children[i]->loc.x + (newX - loc.x), 
			children[i]->loc.y + (newY - loc.y));
	}
	loc.x = newX;
	loc.y = newY;
	titleBarRect[0].x = newX;
	titleBarRect[0].y = newY;
	titleBarRect[1].x = newX + titleBarRect[0].w;
	titleBarRect[1].y = newY;
	closeButton.x = newX + loc.w - closeButton.w - 5;
	closeButton.y = titleBarRect[1].y + closeButton.w / 3;

}
void cGuiWidgetContainer::HandleWidgetEvent(bool isMouseOver){
	if(isMouseOver){
		if(S_IsMouseLeft() || S_IsMouseRight())
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		
		if(closeButton.IsCollision(S_GetMouseX(), S_GetMouseY())){
			if(S_IsMouseLeft()){
				closeButtonState = 2; //Down event
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}else if(closeButtonState == 2){
				closeButtonState = 0;
				isOnScreen = false;
			}else{
				closeButtonState = 1;
			}
			return;
		}else{
			closeButtonState = 0;
		}
		if(titleBarRect[0].IsCollision(S_GetMouseX(), S_GetMouseY())){
			if(!isDragging && !isResize && isMovable){
				resizeDir = -1;
				isDragging = true;
				dragStart.x = S_GetMouseX() - loc.x;
				dragStart.y = S_GetMouseY() - loc.y;
			}
		}else if(!isResize && !S_IsMouseLeft()){
			resizeDir = -1;
			if(S_GetMouseX() >= loc.x + loc.w - BORDER_SIZE){
				resizeDir = 1;
			}else if(S_GetMouseX() - loc.x <= BORDER_SIZE && S_GetMouseX() - loc.x > 0){
				resizeDir = 0;
			}
			if(S_GetMouseY() > loc.y + loc.h - BORDER_SIZE){
				if(resizeDir == 0){	//Resize left
					resizeDir = 3;	//Resize left-down
				}else if(resizeDir == 1){	//Resize right 
					resizeDir = 4;	//Resize right-down
				}else{
					resizeDir = 2;	//Resize down
				}
			}
		}
		if(!isResize && S_IsMouseLeft() && resizeDir != -1){
			dragStart.x = S_GetMouseX();
			dragStart.y = S_GetMouseY();
			isResize = true;
		}
	}
	if(isDragging){
		if(S_IsMouseLeft()){
			UpdatePosition(S_GetMouseX() - dragStart.x, S_GetMouseY() - dragStart.y);
		}else{
			isDragging = false;
		}
	}
	HandleResizeEvent();

	for(int i = 0; i < (int)children.size(); i++){
		if(children[i]->HandleEvents() != GUI_WIDGET_EVENT_NOTHING){
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}
	}
}
void cGuiWidgetContainer::Render(){
	if(loc.w < 45){
		loc.w = 45;
	}
	if(loc.h < 45){
		loc.h = 45;
	}
	uint *tmp = skin->GetSkin(GUI_WIDGET_CONTAINER);
	titleBarRect[0] = loc;
	titleBarRect[0].h = S_GetSection(tmp[1])->height;
	if(showCloseButton){
		titleBarRect[0].w -= S_GetSection(tmp[2])->width / 2;
		titleBarRect[1] = titleBarRect[0];
		titleBarRect[1].x += titleBarRect[0].w;
		titleBarRect[1].w = S_GetSection(tmp[2])->width / 2;
		closeButton = loc;
		closeButton.x += loc.w - S_GetSection(tmp[3])->width - 5;
		closeButton.y += S_GetSection(tmp[3])->height / 3; 
		closeButton.w = S_GetSection(tmp[3])->width;
		closeButton.h = S_GetSection(tmp[3])->height;	
	}
}
void cGuiWidgetContainer::Draw(){
	DrawBackground();
	if(showTitleBar){
		DrawTitle();
	}
	for(int i = 0; i < (int)children.size(); i++){
		children[i]->Draw();
	}
}
void cGuiWidgetContainer::HandleResizeEvent(){
	if(isResize && isResizable){
		if(S_IsMouseLeft()){
			switch(resizeDir){
				case 0:	//Left
					//dragStart.x += loc.w;
					// loc.w -= S_GetMouseX() - dragStart.x;
					// dragStart.x = S_GetMouseX();
					// if(loc.w > 46)
					// 	loc.x = S_GetMouseX();
					break;
				case 1:	//Right
					loc.w += (S_GetMouseX() - dragStart.x);
					dragStart.x = S_GetMouseX();
					break;
				case 2:	//Down
					loc.h += (S_GetMouseY() - dragStart.y);
					dragStart.y = S_GetMouseY();
					break;
				case 3:	//LeftDown
					break;
				case 4:	//RightDown
					loc.w += (S_GetMouseX() - dragStart.x);
					dragStart.x = S_GetMouseX();
					loc.h += (S_GetMouseY() - dragStart.y);
					dragStart.y = S_GetMouseY();
					break;
			}
			Render();		
		}else{
			isResize = false;
		}
	}
}
void cGuiWidgetContainer::DrawBackground(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_CONTAINER);
	S_DrawSectionScaled(tmp[0], &loc);
}
void cGuiWidgetContainer::DrawTitle(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_CONTAINER);
	S_DrawSectionScaled(tmp[1], &titleBarRect[0]);
	S_RenderText(title, titleBarRect[0].x + 50, titleBarRect[0].y, skin->GetFont()
			,(float)tmp[7] / 255, (float)tmp[8] / 255, (float)tmp[9] / 255);
	if(showCloseButton){
		S_DrawSectionScaled(tmp[2], &titleBarRect[1]);
		switch(closeButtonState){
			case 0:
				S_DrawSection(tmp[3], closeButton.x, closeButton.y);
				break;
			case 1:
				S_DrawSection(tmp[4], closeButton.x, closeButton.y);
				break;
			case 2:
				S_DrawSection(tmp[5], closeButton.x, closeButton.y);
				break;
		}
	}
}