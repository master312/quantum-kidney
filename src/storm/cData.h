//Created by Petar Ostojic
//Thu Mar  5 10:50:50 2015
//This class contains functions for converting various data types to binary (char array)
//And binary data manipulation
#include "defines.h"
#include <cstring>
#include <vector>
#include <iostream>
#include "defines.h"

#ifdef OS_LINUX
    #include <sys/types.h>
    #include <dirent.h>
    #include <errno.h>
#endif
#ifdef OS_WINDOWS

#endif
#ifndef CDATA_H
#define CDATA_H

class cData{
public:
	static bool IsBigEndian();
	
	static int ByteToInt(char *buffer, int offset);
	static float ByteToFloat(char *buffer, int offset);
	static short ByteToShort(char *buffer, int offset);
	
	static void IntToByte(int &_int, char *dest);
	static void FloatToByte(float &_float, char *dest);
	static void ShortToByte(short &_short, char *dest);
	
	static void ByteCopy(char *src, char *dest, int destOffset, int srcLen);
	//Returns list of files in directory, or empty vector if dir is empty
        static std::vector<std::string> GetDir(const std::string& loc, 
                                               const std::string& ext = "");

};

#endif