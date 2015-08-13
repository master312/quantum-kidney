//Created by Petar Ostojic
//OCT 15 03:24:20 2014
//This class is simple file parser
//Can be improved ...a lot
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include "fLogs.h"
#ifndef CFILEPARSER_H
#define CFILEPARSER_H
//TODO: Optimise GetTag search
//Tags in config file can bi maximum 100 characters long

struct cFileParserTag{
	std::string tagName;
	std::string value;
};

class cFileParser{
public:
	cFileParser();
	~cFileParser();
	//Load file to be parsed
	void Load(std::string filename);
	//Parse file by tags
	void Parse();
	//Return tag object maching tagName, or NULL if tag not found 
	cFileParserTag *GetTag(std::string tagName);
	//Return number of tags
	int Tags();
private:
	std::vector<cFileParserTag> tags;
	std::vector<std::string> lines;
	void ParseLine(int i);
	void Clear();
};

#endif