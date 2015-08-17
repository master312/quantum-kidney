#include "cGuiWidgetInput.h"

cGuiWidgetInput::cGuiWidgetInput(std::string _name, int x, int y, int w, int h, 
	std::string _text, bool _isEnabled){
	type = GUI_WIDGET_INPUT;
	name = _name;
	loc.x = x;
	loc.y = y;
	loc.w = w;
	loc.h = h;
	text = _text;
	isEnabled = _isEnabled;
	textRect = loc;
	visibleString = "";
	pointerLoc = -1;
	isOver = false;
	timer.SetInterval(50);
        if(text.size() > 0){
            visibleString = text;
        }
}
cGuiWidgetInput::~cGuiWidgetInput(){

}

void cGuiWidgetInput::UpdatePosition(int newX, int newY){
	loc.x = newX;
	loc.y = newY;
	Render();
}
void cGuiWidgetInput::HandleText(bool isMouseOver){
	if(!isEnabled)
		return;
	if(pointerLoc != -1){
		if(S_GetTextInput() == text)
			return;
		if(text.size() < S_GetTextInput().size()){
			//New letter typed
			//pointerLoc++;
			text = S_GetTextInput();
			CalculateText();
		}else if(text.size() > S_GetTextInput().size()){
			//Letter removed
			if(pointerLoc > 0)
				pointerLoc--;
			text = S_GetTextInput();
			CalculateText();
		}
	}
}
void cGuiWidgetInput::HandleWidgetEvent(bool isMouseOver){
	if(!isEnabled)
		return;
	if(isMouseOver){
		isOver = true;
		if(S_IsMouseLeft() && pointerLoc == -1){
			S_StartTextInput();
			S_GetInputManager()->strText = text;
			pointerLoc = 0;
			toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
		}
	}else{
		isOver = false;
		if(S_IsMouseLeft() && pointerLoc > -1){
			pointerLoc = -1;
			S_StopTextInput();
			return;
		}
	}
	if(!timer.IsTimeUp())
		return;
	if(S_IsKeyDown(KEY_LEFT)){
		Move(false);
		CalculateText();
		timer.Reset();
		toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
	}else if(S_IsKeyDown(KEY_RIGHT)){
		Move(true);
		CalculateText();		
		timer.Reset();
		toReturnEvent = GUI_WIDGET_EVENT_HANDLED;
 	}
	timer.Reset();
}
void cGuiWidgetInput::Render(){
	if(text != "")
		CalculateText();

	uint *tmp = skin->GetSkin(GUI_WIDGET_INPUT);
	
	secLeft = loc;
	secLeft.w = S_GetSection(tmp[1])->width;

	secRight = loc;
	secRight.w = S_GetSection(tmp[2])->width;
	secRight.x += loc.w - secRight.w;
	
	secMid = loc;
	secMid.x += secLeft.w;
	secMid.w -= secLeft.w + secRight.w;
}
void cGuiWidgetInput::Draw(){
	//S_DrawFillRect(loc.x, loc.y, loc.w, loc.h);
	DrawSkin();
	uint *tmp = skin->GetSkin(GUI_WIDGET_INPUT);
	S_RenderText(visibleString, loc.x + 5, loc.y + 2, skin->GetFont(), tmp[15], tmp[16], tmp[17]);
}
//Private functions
void cGuiWidgetInput::DrawSkin(){
	uint *tmp = skin->GetSkin(GUI_WIDGET_INPUT);
	if(isEnabled){
		if(isOver){
			if(pointerLoc > -1){
				//Over, selected
				S_DrawSectionScaled(tmp[9], &secMid);
				S_DrawSectionScaled(tmp[10], &secLeft);
				S_DrawSectionScaled(tmp[11], &secRight);
				//*//*//
				return;
			}
			//Over
			S_DrawSectionScaled(tmp[6], &secMid);
			S_DrawSectionScaled(tmp[7], &secLeft);
			S_DrawSectionScaled(tmp[8], &secRight);
			//*//*//
		}else{
			if(pointerLoc > -1){
				//Normal, selected
				S_DrawSectionScaled(tmp[12], &secMid);
				S_DrawSectionScaled(tmp[13], &secLeft);
				S_DrawSectionScaled(tmp[14], &secRight);
				//*//*//
				return;
			}
			//Normal
			S_DrawSectionScaled(tmp[3], &secMid);
			S_DrawSectionScaled(tmp[4], &secLeft);
			S_DrawSectionScaled(tmp[5], &secRight);
			//*//*//
		}
	}else{
		//Disabled
		S_DrawSectionScaled(tmp[0], &secMid);
		S_DrawSectionScaled(tmp[1], &secLeft);
		S_DrawSectionScaled(tmp[2], &secRight);
	}
}
void cGuiWidgetInput::CalculateText(){
	if(pointerLoc < 0)
		return;
	// char tmp[100];
	// int plus = 0;
	
	// if(pointerLoc < text.size()){
	// 	if(pointerLoc > text.size() - 3){
	// 		plus = text.size() - pointerLoc;
	// 	}else{
	// 		plus = 3;
	// 	}
	// 	plus= 0;
	// 	text.copy(tmp, pointerLoc + plus, 0);
	// 	textRect = S_GetTextSize(tmp, skin->GetFont());
	// }else{
	// 	textRect = S_GetTextSize(text, skin->GetFont());
	// }

	// if(textRect.w > loc.w - 10){
	// 	sFont *tmpF = S_GetFont(skin->GetFont());
	// 	int tmpP = pointerLoc + plus;
	// 	for(int i = 0; i < tmpP; i++){
	// 		if(text[i] == ' '){
	// 			textRect.w -= tmpF->spacing * 4;
	// 		}else{
	// 			char c[2];
	// 			c[0] = text[i];
	// 			c[1] = '\0';
	// 			std::string tmpC = c;
	// 			if(tmpF->glyphs.count(tmpC) == 0)
	// 				continue;				
	// 			textRect.w -= S_GetSection(tmpF->glyphs[tmpC])->width;
	// 			textRect.w -= tmpF->spacing;
	// 		}			
	// 		if(textRect.w < loc.w - 10){
	// 			text.copy(tmp, tmpP - i, i);
	// 			tmp[tmpP - i] = '\0';
	// 			visibleString = tmp;
	// 			break;
	// 		}
	// 	}
	// }else{
	// 	visibleString = text;
	// }
	// std::cout << pointerLoc << " " << visibleString << "=" << text.size() << std::endl;

	char tmp[100];
	text.copy(tmp, text.size(), 0);
	tmp[text.size()] = '\0';
//	visibleString = tmp;

	textRect = S_GetTextSize(tmp, skin->GetFont());

	//std::cout << pointerLoc << " " << tmp << "=" << text.size() << std::endl;
	if(textRect.w > loc.w){
		for(int i = 0; i < pointerLoc - 3; i++){
			text.copy(tmp, pointerLoc - i, i);
			tmp[pointerLoc - i] = '\0';
			textRect = S_GetTextSize(tmp, skin->GetFont());
			if(textRect.w <= loc.w - 5){
				visibleString = tmp;
				break;
			}
		}
	}else if(textRect.w < loc.w - 5 && (int)text.size() > pointerLoc){
		text.copy(tmp, pointerLoc, 0);
		visibleString = tmp;
		pointerLoc ++;
	}else{
		visibleString = tmp;
	}
	//skip:
	textRect.x = loc.x + 5;
	textRect.y = loc.y + 2;
}
void cGuiWidgetInput::Move(bool dir){
	if(dir){
		if(pointerLoc < (int)text.size())
			pointerLoc ++;
	}else{
		if(pointerLoc >0)
			pointerLoc --;
	}
}