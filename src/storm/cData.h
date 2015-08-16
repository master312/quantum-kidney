//Created by Petar Ostojic
//Thu Mar  5 10:50:50 2015
//This class contains functions for converting various data types to binary (char array)
//And binary data manipulation
#include "defines.h"
#include <cstring>
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
};

#endif