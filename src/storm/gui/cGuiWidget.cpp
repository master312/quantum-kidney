#include "cGuiWidget.h"


cGuiWidget::cGuiWidget(){
	type = GUI_WIDGET_NOT_DEFINED;
	name = "";
	skin = NULL;
	isOnScreen = true;
	toReturnEvent = GUI_WIDGET_EVENT_NOTHING;
}
cGuiWidget::~cGuiWidget(){

}
int cGuiWidget::HandleEvents(){
	toReturnEvent = GUI_WIDGET_EVENT_NOTHING;
	if(S_GetMouseX() > loc.x && S_GetMouseX() < loc.x + loc.w 
		&& S_GetMouseY() > loc.y && S_GetMouseY() < loc.y + loc.h){
		HandleWidgetEvent(true);
		if(S_IsTextInput()){
			HandleText(true);
		}
		return toReturnEvent;
	}
	HandleWidgetEvent(false);
	if(S_IsTextInput()){
		HandleText(false);
	}
	return toReturnEvent;
}
void cGuiWidget::SetLoc(int x, int y){
	UpdatePosition(x, y);
}
void cGuiWidget::AddChildren(int count, ...){
	va_list ap;
	va_start(ap, count);
	for(int i = 0; i < count; i++){
		AddChild(va_arg(ap, cGuiWidget*));
	}
	va_end(ap);
}

void cGuiWidget::AddChild(cGuiWidget *_child){
	StormPrintLog(STORM_LOG_WARNING, "cGuiWidget", "Template class called");
}
int cGuiWidget::GetChildCount(){
	return 0;
}
cGuiWidget *cGuiWidget::GetChild(int id){
	return NULL;
}
void cGuiWidget::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
}
void cGuiWidget::HandleText(bool isMouseOver){

}
void cGuiWidget::HandleWidgetEvent(bool isMouseOver){

}
void cGuiWidget::LogicTick(){
	
}
void cGuiWidget::Render(){

}
void cGuiWidget::Draw(){
	StormPrintLog(STORM_LOG_WARNING, "cGuiWidget", "Template class called");
}