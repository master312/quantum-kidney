#include "cGuiWidgetPictureBox.h"

cGuiWidgetPictureBox::cGuiWidgetPictureBox(std::string _name, int x, int y, int w, int h, uint _picture){
	type = GUI_WIDGET_PICTUREBOX;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = h;
	textureId = _picture;

	drawVerSlider = false;
	drawHorSlider = false;
	canSelect = true;
	griSelect = true;
	drawGrid = true;
	showFrame = true;
	selectedX = selectedY = 0;
	selectRect.w = selectRect.h = 32;

	horSlider = new cGuiWidgetHorizontalSlider(name + "_horSlider", loc.x, loc.y, loc.w);
	verSlider = new cGuiWidgetVerticalSlider(name + "_verSlider", loc.x + loc.w, loc.y, loc.h - 1);
}
cGuiWidgetPictureBox::cGuiWidgetPictureBox(std::string _name, sRect _loc, uint _picture){
	type = GUI_WIDGET_PICTUREBOX;
	name = _name;
	loc = _loc;
	textureId = _picture;

	drawVerSlider = false;
	drawHorSlider = false;
	canSelect = true;
	griSelect = true;
	drawGrid = true;
	showFrame = true;
	selectedX = selectedY = 0;
	selectRect.w = selectRect.h = 32;

	horSlider = new cGuiWidgetHorizontalSlider(name + "_horSlider", loc.x, loc.y, loc.w);
	verSlider = new cGuiWidgetVerticalSlider(name + "_verSlider", loc.x + loc.w, loc.y, loc.h - 1);
}
cGuiWidgetPictureBox::~cGuiWidgetPictureBox(){
	delete horSlider;
	delete verSlider;
}

void cGuiWidgetPictureBox::HandleWidgetEvent(bool isMouseOver){
	if(drawHorSlider){
		if(horSlider->HandleEvents() == GUI_WIDGET_EVENT_HANDLED){
			srcRect.x = horSlider->GetCurValue();
			if(canSelect){
				UpdateSelectRectPos();
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}
			return;
		}

	}
	if(drawVerSlider){
		if(isMouseOver){
			int tmp = S_GetMouseScroll();
			if(tmp != 0){
				verSlider->SetCurValue(verSlider->GetCurValue() - (tmp * 2));
				srcRect.y = verSlider->GetCurValue();
				if(canSelect){
					UpdateSelectRectPos();
					toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
				}
			}
		}
		if(verSlider->HandleEvents() == GUI_WIDGET_EVENT_HANDLED){
			srcRect.y = verSlider->GetCurValue();
			if(canSelect){
				UpdateSelectRectPos();
				toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			}
			return;
		}
	}
	if(isMouseOver){
		if(!canSelect)
			return;
		if(S_IsMouseLeft()){
			if(griSelect){
				selectedX = (((S_GetMouseX() + srcRect.x) - loc.x) / selectRect.w) * selectRect.w;
				selectedY = (((S_GetMouseY() + srcRect.y) - loc.y) / selectRect.h) * selectRect.h;
			}else{
				selectedX = (S_GetMouseX() + srcRect.x) - loc.x;
				selectedY = (S_GetMouseY() + srcRect.y) - loc.y;
			}
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
			UpdateSelectRectPos();
		}
	}
}
void cGuiWidgetPictureBox::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
	Render();
	UpdateSelectRectPos();
}
void cGuiWidgetPictureBox::SetTexture(uint tId){
	textureId = tId;
	Render();
}
void cGuiWidgetPictureBox::Render(){
	//srcRect.w = loc.w - 1;
	srcRect.h = loc.h - 1;
	horSlider->loc.x = loc.x;
	horSlider->loc.y = loc.y;
	horSlider->loc.w = loc.w - verSlider->loc.w - 1;
	verSlider->loc.x = loc.x + loc.w - verSlider->loc.w - 1;
	verSlider->loc.y = loc.y;
	horSlider->skin = skin;
	verSlider->skin = skin;
	horSlider->Render();
	verSlider->Render();

	if(textureId > 0){
		sTexture *tmpTxture = S_GetTexture(textureId);
		if(tmpTxture->width > loc.w){
			drawHorSlider = true;
			horSlider->SetMaxValue(tmpTxture->width - loc.w + 10);
		}
		if(tmpTxture->height > loc.h){
			drawVerSlider = true;
			verSlider->SetMaxValue(tmpTxture->height - loc.h);
		}
		srcRect.w = tmpTxture->width;
	}
}
void cGuiWidgetPictureBox::Draw(){
	if(showFrame){
		S_DrawRect(&loc);
	}
	if(textureId > 0){
		S_DrawTextureCropped(textureId, &srcRect, loc.x, loc.y);
	}
	if(drawHorSlider){
		horSlider->Draw();
	}
	if(drawVerSlider){
		verSlider->Draw();
	}
	if(canSelect){
		S_DrawRect(&selectRect, 255, 0, 0);
	}
}
void cGuiWidgetPictureBox::UpdateSelectRectPos(){
	selectRect.x = selectedX - srcRect.x + loc.x;
	selectRect.y = selectedY - srcRect.y + loc.y;
	if(selectRect.x < loc.x)
		selectRect.x = -666;
	if(selectRect.y < loc.y)
		selectRect.y = -666;
	if(selectRect.x + selectRect.w > loc.x + loc.w)
		selectRect.x = -666;
	if(selectRect.y + selectRect.h > loc.y + loc.h)
		selectRect.y = -666;
	
}