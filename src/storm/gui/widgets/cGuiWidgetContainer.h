//Creted by Petar Ostojic
//Wed Mar 18 03:03:59 2015
#include "../cGuiWidget.h"
#include <vector>
#ifndef CGUIWIDGETCONTAINER_H
#define CGUIWIDGETCONTAINER_H

class cGuiWidgetContainer : public cGuiWidget {
public:
	cGuiWidgetContainer(std::string _name, std::string _title, int x, int y, int w, int h);
	cGuiWidgetContainer(std::string _name, std::string _title, int x, int y, int w, int h,
			bool showTitle, bool showClose, bool _isResizable, bool _isMovable);
	~cGuiWidgetContainer();

	void AddChild(cGuiWidget *_child);
	int GetChildCount();
	cGuiWidget *GetChild(int id);
	void UpdatePosition(int newX, int newY);
	void HandleWidgetEvent(bool isMouseOver);
	void Render();
	void Draw();
private:
	static const int BORDER_SIZE = 8;
	bool showTitleBar;
	bool showCloseButton;
	bool isResizable;
	bool isMovable;
	std::string title;
	std::vector<cGuiWidget*> children;
	sRect titleBarRect[2];
	int closeButtonState;	//0=normal;1=over;2=down;3=disabled
	sRect closeButton;	//Location on screen, for close button
	
	bool isUpOnTitle;	//If mouse is pressed down on title bar (used for window movement)

	bool isDragging;
	sRect dragStart;

	bool isResize;
	int resizeDir;	//-1=Nothing;0=Left;1=Right;2=Down;3=LeftDown;4=RightDown

	void HandleResizeEvent();
	void DrawBackground();
	void DrawTitle();
};

#endif