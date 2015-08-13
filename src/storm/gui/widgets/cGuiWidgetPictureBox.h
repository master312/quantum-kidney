//Created by Petar Ostojic
//Tue Mar 31 08:28:48 2015
#include "../cGuiWidget.h"
#include "cGuiWidgetVerticalSlider.h"
#include "cGuiWidgetHorizontalSlider.h"
#ifndef CGUIWIDGETPICTUREBOX_H
#define CGUIWIDGETPICTUREBOX_H
//TODO: Draw grid

class cGuiWidgetPictureBox : public cGuiWidget{
public:
	cGuiWidgetPictureBox(std::string _name, int x, int y, int w, int h, uint _picture = 0);
	cGuiWidgetPictureBox(std::string _name, sRect _loc, uint _picture = 0);
	~cGuiWidgetPictureBox();
	
	//Set size of selection box
	void SetSelectRectSize(int w, int h) { selectRect.w = w; selectRect.h = h; }
	//Set selected part of picture in pixels 
	void SetSelectRectLoc(int x, int y) { selectRect.x = x; selectRect.y = y; }
	//If true, selection will be sticked to grid
	void SetGridSelect(bool b) { griSelect = b; }
	//If true, grid will be drawn over image; Grid size is based of selection rect
	void SetShowGrid(bool b) { drawGrid = b; }
	//If true, frame around image will be drawn
	void SetShowFrame(bool b) { showFrame = b; }
	int GetSelectedX() { return selectedX; }
	int GetSelectedY() { return selectedY; }
	//Set picture(texture) to be drawn in picture box
	void SetTexture(uint tId);
	//If true, this image can be selected
	void SetIsSelectable(bool b) { canSelect = b; }

	void HandleWidgetEvent(bool isMouseOver);
	void UpdatePosition(int newX, int newY);
	
	void Render();
	void Draw();
private:
	bool drawVerSlider;			//Should vertical slider be drawn
	bool drawHorSlider;			//Should horizontal slider be drawn

	sRect srcRect;				//Source texture rect, used for texture scrolling

	sRect selectRect;			//Selection rectangle position on screen
	int selectedX, selectedY; 	//Selected position in picture
	bool canSelect;				//Can parts of this picture be selected
	bool griSelect;				//Should selection be sticked to grid
	bool drawGrid;				//Should grid be drawn over image
	bool showFrame;				//Should draw frame around image

	uint textureId;

	cGuiWidgetHorizontalSlider *horSlider;
	cGuiWidgetVerticalSlider *verSlider;

	void UpdateSelectRectPos();
};

#endif