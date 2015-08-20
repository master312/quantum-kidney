#include "cGuiManager.h"

cGuiManager::cGuiManager(){
	defSkin = NULL;
	logicTimer.SetInterval(STORM_GUI_LOGIC_INTERVAL);
}
cGuiManager::~cGuiManager(){
	std::map<uint, cGuiWidget*>::iterator i;
	for(i = widgets.begin(); i != widgets.end(); ++i){
		delete i->second;
	}
	widgets.clear();
	if(defSkin != NULL)
		delete defSkin;
}
bool cGuiManager::Initialize(){
	defSkin = new cGuiSkin();
	return defSkin->Load("data/gui/ApGUI_BlackOrangeSkin.skin");
}
uint cGuiManager::AddWidget(cGuiWidget *widget, cGuiSkin *skin){
	if(widget->skin == NULL && skin != NULL){
		widget->skin = skin;
	}else{
		widget->skin = defSkin;
	}
	widget->Render();

	uint tmpId = 1;
	if(widgets.size() > 0){
		std::map<uint, cGuiWidget*>::iterator i = widgets.end();
		--i;
		tmpId = i->first + 1;
		widgets[tmpId] = widget;
	}else{
		widgets[1] = widget;
	}

	if(widget->isOnScreen){
		onScreen.push_back(tmpId);
	}
	return tmpId;
}
void cGuiManager::Remove(uint id){
	if(widgets.count(id) == 0)
		return;
	if(widgets[id]->isOnScreen){
		for(int i = 0; i < (int)onScreen.size(); i++){
			if(onScreen[i] == id){
				onScreen.erase(onScreen.begin() + i);
				break;
			}
		}
	}
	delete widgets[id];
	widgets.erase(id);
}
cGuiWidget *cGuiManager::GetWidget(uint id){
	if(widgets.count(id) == 0)
		return NULL;
	return widgets[id];
}
cGuiWidget *cGuiManager::GetWidget(std::string name){
	for (auto& kv : widgets) {
		if(kv.second->name.compare(name) == 0)
		        return kv.second;
        }
}
void cGuiManager::ShowWidget(uint id){
	cGuiWidget *tmpW = GetWidget(id);
	if(tmpW == NULL)
		return;
	if(tmpW->isOnScreen)
		return;
    
	tmpW->isOnScreen = true;
	onScreen.push_back(id);
}
void cGuiManager::ShowWidget(std::string name){
	for (auto& kv : widgets) {
		if(kv.second->name.compare(name) == 0){
		        ShowWidget(kv.first);
		        return;
                }
        }
}
void cGuiManager::HideWidget(uint id){
	cGuiWidget *tmpW = GetWidget(id);
	if(tmpW == NULL)
		return;
	if(!tmpW->isOnScreen)
		return;
    
	tmpW->isOnScreen = false;
}
void cGuiManager::HideWidget(std::string name){
	for (auto& kv : widgets) {
		if(kv.second->name.compare(name) == 0){
		        HideWidget(kv.first);
		        return;
                }
        }
}
void cGuiManager::HandleEvents(){
	bool toEat = false;
	for(int i = 0; i < (int)onScreen.size(); i++){
		if(widgets[onScreen[i]]->HandleEvents() != GUI_WIDGET_EVENT_NOTHING){
			toEat = true;
		} 
	}
	if(toEat)
		S_EatEvent("cGuiManager");
}
void cGuiManager::LogicTick(){
	if(!logicTimer.IsTimeUp()){
		return;
	}
	logicTimer.Reset();
	for(int i = 0; i < (int)onScreen.size(); i++){		
		widgets[onScreen[i]]->LogicTick();
		if(!widgets[onScreen[i]]->isOnScreen){
			onScreen.erase(onScreen.begin() + i);
			i = (i > 0) ? i - 1 : 0;
		}
	}
}
void cGuiManager::GraphicsTick(){
	for(int i = 0; i < (int)onScreen.size(); i++){
		widgets[onScreen[i]]->Draw();
	}
}
