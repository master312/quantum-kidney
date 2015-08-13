#include "cGuiWidgetVerticalSlider.h"

cGuiWidgetVerticalSlider::cGuiWidgetVerticalSlider(std::string _name, int x, int y, int h,
	int _minValue, int _maxValue, int _curValue, bool _isEnabled){
	type = GUI_WIDGET_HOR_SLIDER;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = 0;
	loc.h = h;
	minValue = _minValue;
	maxValue = _maxValue;
	curValue = _curValue;
	sliderX = sliderY = 0;
	sliderH = 0;
	isSliding = false;
	canStartSlide = false;
	isEnabled = _isEnabled;
}
cGuiWidgetVerticalSlider::~cGuiWidgetVerticalSlider(){

}

void cGuiWidgetVerticalSlider::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
	Render();
}
void cGuiWidgetVerticalSlider::HandleWidgetEvent(bool isMouseOver){
	if(isSliding){
		float pixelRepresent = (float)loc.h / (maxValue - minValue);
		curValue = (((S_GetMouseY() ) - loc.y) / pixelRepresent) + minValue - 1;
		if(curValue < minValue)
			curValue = minValue;
		else if(curValue > maxValue)
			curValue = maxValue;
		CalculateSlider();
		toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
	}
	if(isMouseOver){
		if(!S_IsMouseLeft()){
			isSliding = false;
			canStartSlide = true;
		}else if(!isSliding){
			if(canStartSlide){
				isSliding = true;
				canStartSlide = false;
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}
		}else{
			canStartSlide = false;
		}
	}else{
		if(!S_IsMouseLeft()){
			isSliding = false;
		}
		canStartSlide = false;
	}
}
void cGuiWidgetVerticalSlider::Render(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_VER_SLIDER);
	loc.w = S_GetSection(tmp[0])->width;
	sliderX = loc.x;
	sliderH = S_GetSection(tmp[3])->height;
	CalculateSlider();
}
void cGuiWidgetVerticalSlider::Draw(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_VER_SLIDER);
	S_DrawSectionScaled(tmp[0], &loc);
	S_DrawSection(tmp[3], sliderX, sliderY);
}
void cGuiWidgetVerticalSlider::CalculateSlider(){
	float pixelRepresent = (float) loc.h / (maxValue - minValue);
	sliderY = loc.y + (pixelRepresent * curValue) - (sliderH / 2);
	if(sliderY < loc.y){
		sliderY = loc.y;
	}else if(sliderY + sliderH > loc.y + loc.h){
		sliderY = loc.y + loc.h - sliderH;
	}
}