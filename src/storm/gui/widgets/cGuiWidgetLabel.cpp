#include "cGuiWidgetLabel.h"

cGuiWidgetLabel::cGuiWidgetLabel(std::string _name, std::string _text, int x, int y){
	type = GUI_WIDGET_LABEL;
	name = _name;
	text = _text;
	loc.x = x;
	loc.y = y;
	r = g = b = 0;
}
cGuiWidgetLabel::cGuiWidgetLabel(std::string _name, std::string _text, int x, int y,
	uint _r, uint _g, uint _b){

	type = GUI_WIDGET_LABEL;
	name = _name;
	text = _text;
	loc.x = x;
	loc.y = y;
	r = _r;
	g = _g;
	b = _b;
}
cGuiWidgetLabel::~cGuiWidgetLabel(){

}
void cGuiWidgetLabel::SetTextArgs(std::string _text, ...){
    char tmp[_text.size() + 50];
    va_list argptr;
    va_start(argptr, _text.c_str());
    vsprintf(tmp, _text.c_str(), argptr);
    va_end(argptr);
    text = tmp;
}
void cGuiWidgetLabel::Render(){
	int tmpX = loc.x;
	int tmpY = loc.y;
	loc = S_GetTextSize(text, skin->GetFont());
	loc.x = tmpX;
	loc.y = tmpY;
}
void cGuiWidgetLabel::Draw(){
	S_RenderText(text, loc.x, loc.y, skin->GetFont(), 
		(float)r / 255, (float)g / 255, (float)b / 255);
}