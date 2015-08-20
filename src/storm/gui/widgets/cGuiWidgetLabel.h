//Created by Petar Ostojic
//Thu Mar 19 16:28:36 2015
#include "../cGuiWidget.h"
#ifndef CGUIWIDGETLABEL_H
#define CGUIWIDGETLABEL_H

class cGuiWidgetLabel : public cGuiWidget{
public:
	cGuiWidgetLabel(std::string _name, std::string _text, int x, int y);
	cGuiWidgetLabel(std::string _name, std::string _text, int x, int y,
		uint _r, uint _g, uint _b);
	~cGuiWidgetLabel();

	std::string GetText() { return text; }
	void SetText(std::string _text) { text = _text; }
        void SetText(std::string _text, ...);
	void SetColor(uint _r, uint _g, uint _b) {r = _r; g = _g; b = _b; }

	void Render();
	void Draw();
private:
	std::string text;
	uint r, g, b;

};

#endif