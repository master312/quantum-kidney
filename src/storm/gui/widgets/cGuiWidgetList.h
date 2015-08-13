//Created by Petar Ostojic
//Fri Apr  3 09:01:39 2015
#include "../cGuiWidget.h"
#include "../../cStormCallbacker.h"
#include <vector>
#ifndef CGUIWIDGETLIST_H
#define CGUIWIDGETLIST_H

class cGuiWidgetList : public cGuiWidget{
public:
	cGuiWidgetList(std::string _name, int x, int y, int w, int h, std::vector<std::string> *_items = NULL);
	cGuiWidgetList(std::string _name, sRect _loc, std::vector<std::string> *_items = NULL);
	~cGuiWidgetList();

	void SetItemList(std::vector<std::string> *_items);
	//Adds new item to list
	void AddItem(std::string item) { items.push_back(item); }
	//Removes item from list
	void RemoveItem(std::string item);
	//Return name of selected item, or empty string if nothing is selected
	std::string GetSelected();
	//Returns ordinal of selected iten
	int GetSelectedOrd();
	//Select item
	void SetSelected(std::string item);
	//Can items in this list be selected
	void SetSelectable(bool b) { selectable = b; }
	//Callback when selected item is changed
	void SetCallback(cStormCallbacker _cb) { callback = _cb; }

	void UpdatePosition(int newX, int newY);
	void HandleWidgetEvent(bool isMouseOver);
	void Render();
	void Draw();
private:
	int selected;
	bool selectable;
	std::vector<std::string> items;
	int itemHeight;
	cStormCallbacker callback;
};

#endif