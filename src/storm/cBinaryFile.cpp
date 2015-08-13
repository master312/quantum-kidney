#include "cBinaryFile.h"

cBinaryFile::cBinaryFile(){
	filename = "";
	isOpen = false;
	pointer = 0;
}
cBinaryFile::cBinaryFile(std::string _filename){
	isOpen = false;
	pointer = 0;
	Open(_filename);
}
cBinaryFile::~cBinaryFile(){
	file.close();
}
void cBinaryFile::Open(std::string _filename){
	file.open(_filename.c_str(), std::ios::binary | std::fstream::in | std::fstream::out);
	isOpen = file.is_open();
	if(!isOpen){
		StormPrintLog(STORM_LOG_ERROR, "cBinaryFile",
			"Could not open binary file '%s'", _filename.c_str());
		file.close();
		return;
	}
	filename = _filename;
}
void cBinaryFile::Close(){
	file.close();
}
void cBinaryFile::Seek(uint num){
	std::cout << "TODO: cBinaryFile Seek() function" << std::endl;
}
int cBinaryFile::ReadInt(){
	file.read(buffer, 4);
	pointer += 4;
	return cData::ByteToInt((char*)buffer, 0);
}
short cBinaryFile::ReadShort(){
	file.read(buffer, 2);
	pointer += 2;
	return cData::ByteToShort((char*)buffer, 0);
}
float cBinaryFile::ReadFloat(){
	file.read(buffer, 4);
	pointer += 4;
	return cData::ByteToFloat((char*)buffer, 0);
}
char cBinaryFile::ReadByte(){
	file.read(buffer, 1);
	pointer += 1;
	return buffer[0];
}
std::string cBinaryFile::ReadString(){
	uint strLen = 0;
	file.read(buffer, 4);
	strLen = (uint)cData::ByteToInt(buffer, 0);
	char* tmpString = new char[strLen + 1];
	file.read(tmpString, strLen);
	std::string tmpS(tmpString);
	delete [] tmpString;
	pointer += strLen;
	return tmpS;
}
std::string cBinaryFile::ReadString(uint len){
	char* tmpString = new char[len + 1];
	file.read(tmpString, len);
	std::string tmpS(tmpString);
	delete [] tmpString;
	pointer += len;
	return tmpS;
}
void cBinaryFile::WriteInt(int val){
	cData::IntToByte(val, (char*)buffer);
	file.write(buffer, 4);
	pointer += 4;
}
void cBinaryFile::WriteShort(short val){
	cData::ShortToByte(val, (char*)buffer);
	file.write(buffer, 2);
	pointer += 2;
}
void cBinaryFile::WriteFloat(float val){
	cData::FloatToByte(val, (char*)buffer);
	file.write(buffer, 4);
	pointer += 4;
}
void cBinaryFile::WriteByte(char b){
	file.write(buffer, 1);
	pointer += 1;
}
void cBinaryFile::WriteString(std::string str){
	WriteInt(str.size());
	file.write(str.c_str(), str.size());
	pointer += str.size();
}
bool cBinaryFile::IsEof(){
	return file.eof();
}