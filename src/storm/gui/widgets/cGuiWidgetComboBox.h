//Created by Petar Ostojic
//Tue Mar 31 05:05:51 2015
#include "../cGuiWidget.h"
#include <map>
#ifndef CGUIWIDGETCOMBOBOX_H
#define CGUIWIDGETCOMBOBOX_H

class cGuiWidgetComboBox : public cGuiWidget{
public:
	cGuiWidgetComboBox(std::string _name, int x, int y, int w, int h, bool _isEnabled = true, std::vector<std::string> *vec = NULL);
	cGuiWidgetComboBox(std::string _name, sRect _loc, bool _isEnabled = true, std::vector<std::string> *vec = NULL);
	~cGuiWidgetComboBox();

	void HandleWidgetEvent(bool isMouseOver);
	void UpdatePosition(int newX, int newY);
	//Create item list from vector of strings
	void AddItems(std::vector<std::string> *vec);
	//Adds item to list
	void AddItem(std::string _item);
	//Returns selected item text, or "" if none
	std::string GetSelectedItem();
	//Remove item by name
	void RemoveItem(std::string _name); 

	void Render();
	void Draw();
private:
	bool isEnabled;
	bool isOver;
	bool isExtended;
	bool isDown;
	int itemHeight;

	sRect destMid, destLeft, destRight, arrowRight, destExtend, selectedItem;
	
	int selected;
	int over;

	std::vector<std::string> items;
};


#endif