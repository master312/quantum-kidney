#include "cGuiSkin.h"

cGuiSkin::cGuiSkin(){
	skinTexture = 0;
	fParser= NULL;
}
cGuiSkin::~cGuiSkin(){
	if(fParser != NULL)
		delete fParser;
}
bool cGuiSkin::Load(std::string _filename){
	filename = _filename;
	fParser = new cFileParser();
	fParser->Load(filename);
	fParser->Parse();

	cFileParserTag *tmpTag = fParser->GetTag("FILENAME");
	if(tmpTag == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cGuiSkin", "Invalid config file");
		delete fParser;
		fParser = NULL;
		return false;
	}
	skinTexture = S_LoadTexture(tmpTag->value);

	if(!LoadFont())
		return false;

	bool status = false;
	status |= LoadCheckBoxSkin();
	status |= LoadContainerSkin();
	status |= LoadButtonSkin();
	status |= LoadRadioSkin();
	status |= LoadInputSkin();
	status |= LoadComboBoxSkin();
	status |= LoadHorSliderSkin();
	status |= LoadVerSkiderSkin();
	status |= LoadListSkin();

	if(!status){
		StormPrintLog(STORM_LOG_WARNING, "cGuiSkin", "Config file loaded, with errors");
		return false;
	}
	return true;	
}

uint *cGuiSkin::GetSkin(int element){
	switch(element){
		case GUI_WIDGET_CONTAINER:
			return containerSections;
			break;
		case GUI_WIDGET_BUTTON:
			return buttonSections;
			break;
		case GUI_WIDGET_CHECKBOX:
			return checkBoxSections;
			break;
		case GUI_WIDGET_RADIO:
			return radioSections;
			break;
		case GUI_WIDGET_INPUT:
			return inputSections;
			break;
		case GUI_WIDGET_COMBOBOX:
			return comboBoxSections;
			break;
		case GUI_WIDGET_HOR_SLIDER:
			return horSliderSections;
			break;
		case GUI_WIDGET_VER_SLIDER:
			return verSliderSections;
			break;
		case GUI_WIDGET_LIST:
			return listSections;
			break;
		default:
			StormPrintLog(STORM_LOG_WARNING, "cGuiSkin", "Unknown element required, GetSkin()");
	}
	return NULL;
}
//Private functions
bool cGuiSkin::LoadFont(){
	bool toReturn = true;
	cFileParserTag *tmpTag = fParser->GetTag("FONT_SIZE");
	cFileParserTag *tmpTag2 = fParser->GetTag("FONT_FILE");
	cFileParserTag *tmpTag3 = fParser->GetTag("FONT_NAME");

	if(tmpTag == NULL || tmpTag2 == NULL || tmpTag3 == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cGuiSkin", "Invalid config file");
		toReturn = false;
	}

	int fontSize = atoi(tmpTag->value.c_str());
	fontName = tmpTag3->value;
	if(!S_LoadFont(tmpTag2->value, fontName, fontSize)){
		StormPrintLog(STORM_LOG_ERROR, "cGuiSkin", "Could not load font");
		toReturn = false;
	}
	if(!toReturn){
		S_UnloadTexture(skinTexture);
		delete fParser;
		fParser = NULL;
		return false;
	}
	return true;
}
uint cGuiSkin::ParseSection(std::string tag){
	cFileParserTag *tg = fParser->GetTag(tag);
	uint tmpUint = 0;
	if(tg != NULL){
		sRect tmpRect;
		sscanf(tg->value.c_str(), "%d %d %d %d", &tmpRect.x, &tmpRect.y, &tmpRect.w, &tmpRect.h);
		tmpUint = S_CreateSection(skinTexture, tmpRect.x, tmpRect.y, tmpRect.w, tmpRect.h);
	}else{
		std::cout << "ApGUI skin '" << filename << "' error: Tag "<< tag << " not defined" << std::endl;
	}
	return tmpUint;
}
void cGuiSkin::ParseColor(std::string tag, uint *r, uint *g, uint *b){
	cFileParserTag *tg = fParser->GetTag(tag);
	if(tg != NULL){
		sscanf(tg->value.c_str(), "%d %d %d", r, g, b);	
	}else{
		*r = 0;
		*g = 0;
		*b = 0;
		std::cout << "ApGUI skin '" << filename << "' error: Tag "<< tag << " not defined" << std::endl;
	}
}

bool cGuiSkin::LoadCheckBoxSkin(){
	checkBoxSections[0] = ParseSection("APGUI_SKIN_CHBOX_DISABLED_NC");
	checkBoxSections[1] = ParseSection("APGUI_SKIN_CHBOX_DISABLED_CH");
	checkBoxSections[2] = ParseSection("APGUI_SKIN_CHBOX_NORMAL_NC");
	checkBoxSections[3] = ParseSection("APGUI_SKIN_CHBOX_NORMAL_CH");
	checkBoxSections[4] = ParseSection("APGUI_SKIN_CHBOX_OVER_NC");
	checkBoxSections[5] = ParseSection("APGUI_SKIN_CHBOX_OVER_CH");
	checkBoxSections[6] = ParseSection("APGUI_SKIN_CHBOX_DOWN_NC");
	checkBoxSections[7] = ParseSection("APGUI_SKIN_CHBOX_DOWN_CH");

	ParseColor("APGUI_SKIN_CHBOX_LABEL_COLOR", 
		&checkBoxSections[8], &checkBoxSections[9], &checkBoxSections[10]);

	return checkBoxSections[0] != 0 && checkBoxSections[1] != 0 && checkBoxSections[2] != 0 && 
			checkBoxSections[3] != 0 && checkBoxSections[4] != 0 && checkBoxSections[5] != 0 && 
			checkBoxSections[6] != 0 && checkBoxSections[7] != 0;
}
bool cGuiSkin::LoadContainerSkin(){
	containerSections[0] = ParseSection("APGUI_SKIN_CONTAINER_BACKGROUND");
	containerSections[1] = ParseSection("APGUI_SKIN_CONTAINER_TITLEBAR");
	containerSections[2] = ParseSection("APGUI_SKIN_CONTAINER_CLTITLEBAR");
	containerSections[3] = ParseSection("APGUI_SKIN_CONTAINER_CLOSE_DIS");
	containerSections[4] = ParseSection("APGUI_SKIN_CONTAINER_CLOSE_NORM");
	containerSections[5] = ParseSection("APGUI_SKIN_CONTAINER_CLOSE_OVER");
	containerSections[6] = ParseSection("APGUI_SKIN_CONTAINER_CLOSE_DOWN");

	ParseColor("APGUI_SKIN_CHBOX_LABEL_COLOR", 
		&containerSections[7], &containerSections[8], &containerSections[9]);

	return containerSections[0] != 0 && containerSections[1] != 0 && containerSections[2] != 0 && 
			containerSections[3] != 0 && containerSections[4] != 0 && containerSections[5] != 0 && 
			containerSections[6] != 0;
}
bool cGuiSkin::LoadButtonSkin(){
	buttonSections[0] = ParseSection("APGUI_SKIN_BUTTON_DISABLED");
	buttonSections[1] = ParseSection("APGUI_SKIN_BUTTON_DISABLED_LEFT");
	buttonSections[2] = ParseSection("APGUI_SKIN_BUTTON_DISABLED_RIGHT");
	buttonSections[3] = ParseSection("APGUI_SKIN_BUTTON_NORMAL");
	buttonSections[4] = ParseSection("APGUI_SKIN_BUTTON_NORMAL_LEFT");
	buttonSections[5] = ParseSection("APGUI_SKIN_BUTTON_NORMAL_RIGHT");
	buttonSections[6] = ParseSection("APGUI_SKIN_BUTTON_OVER");
	buttonSections[7] = ParseSection("APGUI_SKIN_BUTTON_OVER_LEFT");
	buttonSections[8] = ParseSection("APGUI_SKIN_BUTTON_OVER_RIGHT");
	buttonSections[9] = ParseSection("APGUI_SKIN_BUTTON_DOWN");
	buttonSections[10] = ParseSection("APGUI_SKIN_BUTTON_DOWN_LEFT");
	buttonSections[11] = ParseSection("APGUI_SKIN_BUTTON_DOWN_RIGHT");

	ParseColor("APGUI_SKIN_BUTTON_TEXT_COLOR", 
		&buttonSections[12], &buttonSections[13], &buttonSections[14]);

	return containerSections[0] != 0 && containerSections[1] != 0 && containerSections[2] != 0 && 
			containerSections[3] != 0 && containerSections[4] != 0 && containerSections[5] != 0 && 
			containerSections[6] != 0 && containerSections[7] != 0 && containerSections[8] != 0 &&
			containerSections[9] != 0 && containerSections[10] != 0 && containerSections[11] != 0;
}
bool cGuiSkin::LoadRadioSkin(){
	radioSections[0] = ParseSection("APGUI_SKIN_RADIO_DISABLED_NC");
	radioSections[1] = ParseSection("APGUI_SKIN_RADIO_DISABLED_CH");
	radioSections[2] = ParseSection("APGUI_SKIN_RADIO_NORMAL_NC");
	radioSections[3] = ParseSection("APGUI_SKIN_RADIO_NORMAL_CH");
	radioSections[4] = ParseSection("APGUI_SKIN_RADIO_OVER_NC");
	radioSections[5] = ParseSection("APGUI_SKIN_RADIO_OVER_CH");
	radioSections[6] = ParseSection("APGUI_SKIN_RADIO_DOWN_NC");
	radioSections[7] = ParseSection("APGUI_SKIN_RADIO_DOWN_CH");

	ParseColor("APGUI_SKIN_RADIO_TEXT_COLOR", 
		&radioSections[8], &radioSections[9], &radioSections[10]);

	return radioSections[0] != 0 && radioSections[1] != 0 && radioSections[2] != 0 && 
			radioSections[3] != 0 && radioSections[4] != 0 && radioSections[5] != 0 && 
			radioSections[6] != 0 && radioSections[7] != 0;
}
bool cGuiSkin::LoadInputSkin(){
	inputSections[0] = ParseSection("APGUI_SKIN_INPUT_DISABLED");
	inputSections[1] = ParseSection("APGUI_SKIN_INPUT_DISABLED_LEFT");
	inputSections[2] = ParseSection("APGUI_SKIN_INPUT_DISABLED_RIGHT");
	inputSections[3] = ParseSection("APGUI_SKIN_INPUT_NORMAL");
	inputSections[4] = ParseSection("APGUI_SKIN_INPUT_NORMAL_LEFT");
	inputSections[5] = ParseSection("APGUI_SKIN_INPUT_NORMAL_RIGHT");
	inputSections[6] = ParseSection("APGUI_SKIN_INPUT_OVER_NONSELECTE");
	inputSections[7] = ParseSection("APGUI_SKIN_INPUT_OVER_NONSELECTE_LEFT");
	inputSections[8] = ParseSection("APGUI_SKIN_INPUT_OVER_NONSELECTE_RIGHT");
	inputSections[9] = ParseSection("APGUI_SKIN_INPUT_OVER_SELECTED");
	inputSections[10] = ParseSection("APGUI_SKIN_INPUT_OVER_SELECTED_LEFT");
	inputSections[11] = ParseSection("APGUI_SKIN_INPUT_OVER_SELECTED_RIGHT");
	inputSections[12] = ParseSection("APGUI_SKIN_INPUT_SELECTED");
	inputSections[13] = ParseSection("APGUI_SKIN_INPUT_SELECTED_LEFT");
	inputSections[14] = ParseSection("APGUI_SKIN_INPUT_SELECTED_RIGHT");

	ParseColor("APGUI_SKIN_INPUT_TEXT_COLOR", 
		&inputSections[15], &inputSections[16], &inputSections[17]);

	return inputSections[0] != 0 && inputSections[1] != 0 && inputSections[2] != 0 && 
			inputSections[3] != 0 && inputSections[4] != 0 && inputSections[5] != 0 && 
			inputSections[6] != 0 && inputSections[7] != 0 && inputSections[8] != 0 &&
			inputSections[9] != 0 && inputSections[10] != 0 && inputSections[11] != 0 && 
			inputSections[11] != 0 && inputSections[12] != 0 && inputSections[13] != 0 && 
			inputSections[14] != 0;
}
bool cGuiSkin::LoadComboBoxSkin(){
	comboBoxSections[0] = ParseSection("APGUI_SKIN_COMBOBOX_DISABLED");
	comboBoxSections[1] = ParseSection("APGUI_SKIN_COMBOBOX_DISABLED_LEFT");
	comboBoxSections[2] = ParseSection("APGUI_SKIN_COMBOBOX_DISABLED_RIGHT");
	comboBoxSections[3] = ParseSection("APGUI_SKIN_COMBOBOX_ARROW_DISABLED");
	comboBoxSections[4] = ParseSection("APGUI_SKIN_COMBOBOX_NORMAL");
	comboBoxSections[5] = ParseSection("APGUI_SKIN_COMBOBOX_NORMAL_LEFT");
	comboBoxSections[6] = ParseSection("APGUI_SKIN_COMBOBOX_NORMAL_RIGHT");
	comboBoxSections[7] = ParseSection("APGUI_SKIN_COMBOBOX_ARROW_NORMAL");
	comboBoxSections[8] = ParseSection("APGUI_SKIN_COMBOBOX_OVER");
	comboBoxSections[9] = ParseSection("APGUI_SKIN_COMBOBOX_OVER_LEFT");
	comboBoxSections[10] = ParseSection("APGUI_SKIN_COMBOBOX_OVER_RIGHT");
	comboBoxSections[11] = ParseSection("APGUI_SKIN_COMBOBOX_ARROW_OVER");
	comboBoxSections[12] = ParseSection("APGUI_SKIN_COMBOBOX_ARROW_DOWN");
	comboBoxSections[13] = ParseSection("APGUI_SKIN_COMBOBOX_EXTENDED");
	comboBoxSections[14] = ParseSection("APGUI_SKIN_COMBOBOX_EXTENDED_BOTTOM");
	comboBoxSections[15] = ParseSection("APGUI_SKIN_COMBOBOX_ITEM_OVER");

	ParseColor("APGUI_SKIN_COMBOBOX_TEXT_COLOR", 
		&comboBoxSections[16], &comboBoxSections[17], &comboBoxSections[18]);

	return comboBoxSections[0] != 0 && comboBoxSections[1] != 0 && comboBoxSections[2] != 0 && 
			comboBoxSections[3] != 0 && comboBoxSections[4] != 0 && comboBoxSections[5] != 0 && 
			comboBoxSections[6] != 0 && comboBoxSections[7] != 0 && comboBoxSections[8] != 0 &&
			comboBoxSections[9] != 0 && comboBoxSections[10] != 0 && comboBoxSections[11] != 0 && 
			comboBoxSections[11] != 0 && comboBoxSections[12] != 0 && comboBoxSections[13] != 0 && 
			comboBoxSections[14] != 0 && comboBoxSections[15];
}
bool cGuiSkin::LoadHorSliderSkin(){
	horSliderSections[0] = ParseSection("APGUI_SKIN_HORSLIDER_BACKGROUND");
	horSliderSections[1] = ParseSection("APGUI_SKIN_HORSLIDER_BACKGROUND_LEFT");
	horSliderSections[2] = ParseSection("APGUI_SKIN_HORSLIDER_BACKGROUND_RIGHT");
	horSliderSections[3] = ParseSection("APGUI_SKIN_HORSLIDER_BIG_DISABLED");
	horSliderSections[4] = ParseSection("APGUI_SKIN_HORSLIDER_BIG_NORMAL");
	horSliderSections[5] = ParseSection("APGUI_SKIN_HORSLIDER_BIG_OVER");
	horSliderSections[6] = ParseSection("APGUI_SKIN_HORSLIDER_BIG_DOWN");

	return horSliderSections[0] != 0 && horSliderSections[1] != 0 && horSliderSections[2] != 0 && 
			horSliderSections[3] != 0 && horSliderSections[4] != 0 && horSliderSections[5] != 0 && 
			horSliderSections[6] != 0;
}
bool cGuiSkin::LoadVerSkiderSkin(){
	verSliderSections[0] = ParseSection("APGUI_SKIN_VERSLIDER_BACKGROUND");
	verSliderSections[1] = ParseSection("APGUI_SKIN_VERSLIDER_BACKGROUND_TOP");
	verSliderSections[2] = ParseSection("APGUI_SKIN_VERSLIDER_BACKGROUND_BOT");
	verSliderSections[3] = ParseSection("APGUI_SKIN_VERSLIDER_BIG_DISABLED");
	verSliderSections[4] = ParseSection("APGUI_SKIN_VERSLIDER_BIG_NORMAL");
	verSliderSections[5] = ParseSection("APGUI_SKIN_VERSLIDER_BIG_OVER");
	verSliderSections[6] = ParseSection("APGUI_SKIN_VERSLIDER_BIG_DOWN");

	return verSliderSections[0] != 0 && verSliderSections[1] != 0 && verSliderSections[2] != 0 && 
			verSliderSections[3] != 0 && verSliderSections[4] != 0 && verSliderSections[5] != 0 && 
			verSliderSections[6] != 0;
}
bool cGuiSkin::LoadListSkin(){
	listSections[0] = ParseSection("APGUI_SKIN_LIST_TOP");
	listSections[1] = ParseSection("APGUI_SKIN_LIST_LEFT");
	listSections[2] = ParseSection("APGUI_SKIN_LIST_DOWN");
	listSections[3] = ParseSection("APGUI_SKIN_LIST_RIGHT");
	listSections[4] = ParseSection("APGUI_SKIN_LIST_MIDDLE");

	ParseColor("APGUI_SKIN_INPUT_TEXT_COLOR", 
		&listSections[5], &listSections[6], &listSections[7]);

	return listSections[0] != 0 && listSections[1] != 0 && listSections[2] != 0 && 
			listSections[3] != 0 && listSections[4] != 0;
}