#include "cGuiWidgetHorizontalSlider.h"


cGuiWidgetHorizontalSlider::cGuiWidgetHorizontalSlider(std::string _name, int x, int y, 
	int w, int _minValue, int _maxValue, int _curValue, bool _isEnabled){
	type = GUI_WIDGET_HOR_SLIDER;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = 0;
	minValue = _minValue;
	maxValue = _maxValue;
	curValue = _curValue;
	sliderX = sliderY = 0;
	sliderW = 0;
	isSliding = false;
	canStartSlide = false;
	isEnabled = _isEnabled;
}
cGuiWidgetHorizontalSlider::~cGuiWidgetHorizontalSlider(){

}

void cGuiWidgetHorizontalSlider::HandleWidgetEvent(bool isMouseOver){
	if(isSliding){
		float pixelRepresent = (float)loc.w / (maxValue - minValue);
		curValue = (((S_GetMouseX() - sliderW / 2) - loc.x) / pixelRepresent) + minValue - 1;
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
void cGuiWidgetHorizontalSlider::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;

	Render();
}

void cGuiWidgetHorizontalSlider::Render(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_HOR_SLIDER);
	loc.h = S_GetSection(tmp[0])->height;
	
	borderLeft = loc;
	borderLeft.w = S_GetSection(tmp[1])->width;
	borderRight = loc;
	borderRight.w = S_GetSection(tmp[2])->width;
	borderRight.x += loc.w - borderRight.w;
	sliderX = loc.x;
	sliderY = loc.y + 1;
	sliderW = S_GetSection(tmp[3])->width;
	CalculateSlider();
}
void cGuiWidgetHorizontalSlider::Draw(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_HOR_SLIDER);
	S_DrawSectionScaled(tmp[0], &loc);
	S_DrawSectionScaled(tmp[1], &borderLeft);
	S_DrawSectionScaled(tmp[2], &borderRight);

	S_DrawSection(tmp[3], sliderX, sliderY);
}
void cGuiWidgetHorizontalSlider::CalculateSlider(){
	float pixelRepresent = (float) loc.w / (maxValue - minValue);
	sliderX = loc.x + (pixelRepresent * curValue);
	if(sliderX < loc.x){
		sliderX = loc.x;
	}else if(sliderX + sliderW > loc.x + loc.w){
		sliderX = loc.x + loc.w - sliderW;
	}
}