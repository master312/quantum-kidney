#include "fLogs.h"
void StormSetTermColor(char *termColor){
#ifdef OS_LINUX
	std::cout << termColor;
#else
	#ifdef OS_WINDOWS
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (uint)termColor);
	#else
	std::cout << "logs.cpp Unsuported OS; Logs will not be printed right" << std::endl;
	#endif
#endif
}

void StormPrintLog(int type, const char *className, const char *message, ...){
	int size = 0;
	for(uint i = 0; i < strlen(message); i++){
		if(message[i] == '%'){
			size++;
		}
	}

	switch(type){
		case STORM_LOG_NOTSPECIFIED:
			StormSetTermColor((char*)LOGCOLOR_DEFAULT);
			break;
		case STORM_LOG_INFO:
			StormSetTermColor((char*)LOGCOLOR_INFO);
			std::cout << "INFO ";
			break;
		case STORM_LOG_WARNING:
			StormSetTermColor((char*)LOGCOLOR_WARNING);
			std::cout << "WARNING ";
			break;
		case STORM_LOG_ERROR:
			StormSetTermColor((char*)LOGCOLOR_ERROR);
			std::cout << "ERROR ";
			break;
	}

	if(className != NULL){
		StormSetTermColor((char*)LOGCOLOR_CLASS);
		std::cout << className << ": ";
		switch(type){
			case STORM_LOG_NOTSPECIFIED:
				StormSetTermColor((char*)LOGCOLOR_DEFAULT);
				break;
			case STORM_LOG_INFO:
				StormSetTermColor((char*)LOGCOLOR_INFO);
				//std::cout << "INFO ";
				break;
			case STORM_LOG_WARNING:
				StormSetTermColor((char*)LOGCOLOR_WARNING);
				//std::cout << "WARNING ";
				break;
			case STORM_LOG_ERROR:
				StormSetTermColor((char*)LOGCOLOR_ERROR);
				//std::cout << "ERROR ";
				break;
		}
	}
	if(size == 0){
		std::cout << message;
	}else{
		va_list ap;
		va_start(ap, size);
		for(uint i = 0; i < strlen(message); i++){
			if(message[i] == '%'){
				switch(message[i + 1]){
					case 'd':	//Int
						std::cout << va_arg(ap, int);
						break;
					case 's':
						std::cout << va_arg(ap, char*);
						break;
					case 'f':
						std::cout << va_arg(ap, double);
						break;
					default:
						break;
				}
				i++;
			}else{
				std::cout << message[i];
			}
		}
		va_end(ap);
	}
	std::cout << std::endl;
#ifdef OS_LINUX
	std::cout << LOGCOLOR_DEFAULT;
#endif
}