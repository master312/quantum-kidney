#include "cFileParser.h"

cFileParser::cFileParser(){
}
cFileParser::~cFileParser(){
	Clear();
}
void cFileParser::Load(std::string filename){
	Clear();
	std::ifstream in(filename.c_str());
	if(!in.is_open()){
		StormPrintLog(STORM_LOG_ERROR, "cFileParser", 
			"Could not open file %s", filename.c_str());
		return;
	}
	while(!in.eof()){
		char tmpChar[100];
		in.getline(tmpChar, 100);
		if(strlen(tmpChar) < 5)
			continue;
		lines.push_back(tmpChar);
	}
	in.close();
}
void cFileParser::ParseLine(int i){
	char *tmpLine = (char*)lines[i].c_str();
	char tmpTagName[50];
	char tmpTagValue[100];
	if(tmpLine[0] == '/'){
		return;
	}else if(tmpLine[0] != '<'){	//This line is tag
		StormPrintLog(STORM_LOG_ERROR, "cFileParser", "Syntax error on line %d", i);
		return;
	}
	cFileParserTag tmpTag;
	bool tagSaved = false;
	int dataBeginI = 0;
	for(int i = 1; i < (int)strlen(tmpLine); i++){
		if(!tagSaved){
			if(tmpLine[i] == '>'){		//End of tag reached; Tag must end with '>'
				tagSaved = true;
				dataBeginI = i + 1;
				continue;
			}
			tmpTagName[i - 1] = tmpLine[i];
			tmpTagName[i] = '\0';
		}else{
			if(tmpLine[i] == ';'){		//End of the line reached; Line must end with;
				break;
			}
			tmpTagValue[i - dataBeginI] = tmpLine[i];
			tmpTagValue[i - dataBeginI + 1] = '\0';
		}
	}
	tmpTag.tagName = tmpTagName;
	tmpTag.value = tmpTagValue;
	tags.push_back(tmpTag);
}
void cFileParser::Parse(){
	for(int i = 0; i < (int)lines.size(); i++){
		ParseLine(i);
	}
	StormPrintLog(STORM_LOG_INFO, "cFileParser", "Parsed %d tags", (int)tags.size()); 
	lines.clear();
}
cFileParserTag *cFileParser::GetTag(std::string tagName){
	for(int i = 0; i < (int)tags.size(); i++){
		if(tags[i].tagName == tagName){
			return &tags[i];
		}
	}
	return NULL;
}
int cFileParser::Tags(){
	return tags.size();
}
void cFileParser::Clear(){
	tags.clear();
	lines.clear();
}
