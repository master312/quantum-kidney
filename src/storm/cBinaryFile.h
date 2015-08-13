//Created by Petar Ostojic;
//Mon June 28 02:55:53 2015
#include "cData.h"
#include <fstream>
#include "fLogs.h"
#ifndef CBINARYFILE_H
#define CBINARYFILE_H
//WARNING: Files are always readed/writen in big endian format
//		-If you use this class to read and write at the same time
//		-make sure that you use Seek() function between read/write calls
//TODO: Seek function
//TODO: Read/write long type

class cBinaryFile{
public:
	cBinaryFile();
	cBinaryFile(std::string _filename);
	~cBinaryFile();

	//Open binary file
	void Open(std::string _filename);
	//Close binary file
	void Close();

	//Jump to position in file. @num is location on bytes
	void Seek(uint num);
	
	//Reading functions
	int ReadInt();
	short ReadShort();
	float ReadFloat();
	char ReadByte();
	std::string ReadString();
	std::string ReadString(uint len);
	//Writing functions
	void WriteInt(int val);
	void WriteShort(short val);
	void WriteFloat(float val);
	void WriteByte(char b);
	void WriteString(std::string str);

	//Is file opened
	bool IsOpen() { return isOpen; }
	//Is EOF ?
	bool IsEof();
	//Returns filename of opened file
	std::string GetFilename() { return filename; }
	//Returns current pointer position
	uint GetPointer() { return pointer; }
private:
	std::string filename;
	bool isOpen;
	uint pointer;
	std::fstream file;
	char buffer[4];
};

#endif