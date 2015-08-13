//Created by Petar Ostojic
//Wed Mar 18 00:17:04 2015
#include "../engine.h"
#include "../cFileParser.h"
#include "guiDefines.h"
#ifndef CGUISKIN_H
#define CGUISKIN_H
//TODO: Look at .cpp file, and you know it
//Don't forget to fix cout's in parsing functions

class cGuiSkin{
public:
	cGuiSkin();
	~cGuiSkin();
	//Loads gui skin form file
	//Returns false, if there was an error, or warning
	bool Load(std::string _filename);

	//Returns array of texture section ID's for this element 
	uint *GetSkin(int element);
	//Return font name
	std::string GetFont() { return fontName; }
private:
	//Pointer to file parser
	cFileParser *fParser;
	//Filename of config file
	std::string filename;
	//Texture ID of skin
	uint skinTexture;
	//Font name (not filename)
	std::string fontName;

	uint checkBoxSections[11];	//TODO: Set default variables to zero (0)
	uint containerSections[10];
	uint buttonSections[15];
	uint radioSections[11];
	uint inputSections[18];
	uint comboBoxSections[19];
	uint horSliderSections[7];
	uint verSliderSections[7];
	uint listSections[8];

	bool LoadFont();

	//Create section for @tag, form skin configuration file, and returns section ID
	uint ParseSection(std::string tag);
	//Parse color from @tag
	void ParseColor(std::string tag, uint *r, uint *g, uint *b);

	bool LoadCheckBoxSkin();
	bool LoadContainerSkin();
	bool LoadButtonSkin();
	bool LoadRadioSkin();
	bool LoadInputSkin();
	bool LoadComboBoxSkin();
	bool LoadHorSliderSkin();
	bool LoadVerSkiderSkin();
	bool LoadListSkin();
};

#endif