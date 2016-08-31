//FileLoad.h
#ifndef _FILELOAD_H
#define _FILELOAD_H
#include "Array.h"
#include <string>
using namespace std;

class FileLoad {
private:
	Array<string> lines;
	string directory;
	string fileName;

public:
	FileLoad();
	FileLoad(const FileLoad& source);
	~FileLoad();
	string SetDirectory(string directory);
	Array<string>* Load(string directory);

private:
	void CleanUpFile();
	void CleanUpFile_DeleteBlockComment();
	void CleanUpFile_DeleteComment();
	void CleanUpFile_DeleteTab();
	void CleanUpFile_DeleteNullLine();
	void CleanUpFile_DeleteNewLine();

public:
	string GetLine(int index);
	string& GetDirectory();
	string& GetFileName();
	string& GetFileDirectory();
	int GetLineLength();
};
inline string FileLoad::GetLine(int index) {
	string line;

	line = this->lines.GetAt(index);
	
	return line;
}

inline string& FileLoad::GetDirectory() {
	return const_cast<string&>(this->directory);
}

inline string& FileLoad::GetFileName() {
	return const_cast<string&>(this->fileName);
}

inline string& FileLoad::GetFileDirectory() {
	string fileDirectory = this->directory + "\\" + this->fileName;

	return const_cast<string&>(fileDirectory);
}

inline int FileLoad::GetLineLength() {
	int length=this->lines.GetLength();
	return length;
}

#endif //_FILELOAD_H