//Created by Petar Ostojic
//Thu Feb 19 04:00:46 2015
#include "defines.h"
#include <iostream>
#ifndef FLOGS_H
#define FLOGS_H
#ifdef OS_LINUX
	#define LOGCOLOR_DEFAULT	"\033[0m"
	#define LOGCOLOR_INFO		"\033[32m"
	#define LOGCOLOR_WARNING	"\033[33m"
	#define LOGCOLOR_ERROR		"\033[31m"
	#define LOGCOLOR_CLASS		"\033[36m"
#elif OS_WINDOWS 
	#include <windows.h>
	#define LOGCOLOR_DEFAULT	(uint)(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
	#define LOGCOLOR_INFO		(uint)(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
	#define LOGCOLOR_WARNING	(uint)(FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
	#define LOGCOLOR_ERROR		(uint)(FOREGROUND_RED|FOREGROUND_INTENSITY)
	#define LOGCOLOR_CLASS		(uint)(FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#endif

//Change terminal text color
void StormSetTermColor(char *termColor);
//Print log on console
//Warning: This function CAN NOT print '%' character in string for now
void StormPrintLog(int type, const char *className, const char *message, ...);

#endif