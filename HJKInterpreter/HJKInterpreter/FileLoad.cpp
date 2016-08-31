//FileLoad.cpp
/*
*파일 이름 : FileLoad.cpp
*기     능 : 파일 적재에 관한 기능을 담당한다(파일적재, 주석 제거)
*작 성  자 : 김호종
*작성 일자 : 2016.07.12
*/

#include "FileLoad.h"
#pragma warning(disable:4996)

/*
* 연산 이름 : 생성자
* 연산 기능 : 파일적재 클래스를 생성한다
* 입     력 : 없음
* 출     력 : 없음
*/
FileLoad::FileLoad() {

}

/*
* 연산 이름 : 소멸자
* 연산 기능 : 파일적재 클래스를 지운다
* 입     력 : 없음
* 출     력 : 없음
*/
FileLoad::~FileLoad() {

}

/*
* 연산 이름 : 복사 생성자
* 연산 기능 : 파일적재 클래스를 복사한다
* 입     력 : 기존의 파일적재 클래스
* 출     력 : 복사된 파일적재 클래스
*/
FileLoad::FileLoad(const FileLoad& source) {
	this->lines = source.lines;
	this->directory = source.directory;
	this->fileName = source.fileName;
}

/*
* 연산 이름 : 경로 설정
* 연산 기능 : 파일의 파일명과 경로를 입력받아 파일적재 클래스에 나눠 저장한다
* 입     력 : 파일경로
* 출     력 : 파일명과 경로
*/
string FileLoad::SetDirectory(string directory) {
	char temp;
	int index;
	string totalDirectory;
	index = directory.length()-1;
	temp = directory.at(index);
	while (temp != '\\'){
		index--;
		temp = directory.at(index);
	}

	this->directory = directory.substr(0, index);
	index++;
	this->fileName = directory.substr(index);
	totalDirectory = this->directory + "\\" + this->fileName;
	return totalDirectory;
}

/*
* 연산 이름 : 적재
* 연산 기능 : 파일경로에있는 파일을 불러와 적재후 정리한다
* 입     력 : 파일경로
* 출     력 : 줄들
*/
Array<string>* FileLoad::Load(string directory) {
	FILE *file;
	char line[256];
	file = fopen(directory.c_str(), "rt");
	if (file != NULL) {
		while (!feof(file)) {
			fgets(line, 256, file);
			this->lines.AppendFromRear(line);
		}
	}
	this->CleanUpFile();
	return &this->lines;
}

/*
* 연산 이름 : 파일 정리
* 연산 기능 : 줄들의 필요 없는 부분을 정리한다
* 입     력 : 없음
* 출     력 : 없음
*/
void FileLoad::CleanUpFile() {
	this->CleanUpFile_DeleteNewLine();
	this->CleanUpFile_DeleteBlockComment();
	this->CleanUpFile_DeleteComment();
	this->CleanUpFile_DeleteTab();
	this->CleanUpFile_DeleteNullLine();
}

/*
* 연산 이름 : (파일정리)블록 주석 제거
* 연산 기능 : 블록단위의 주석을 없앤다
* 입     력 : 없음
* 출     력 : 없음
*/
void FileLoad::CleanUpFile_DeleteBlockComment() {
	int length;
	int index=0;
	string line;

	length = this->lines.GetLength();
	while (index < length) {
		line = this->lines.GetAt(index).substr(0,3);
		if (line == "###") {
			this->lines.Delete(index);			
			length = this->lines.GetLength();
			line = this->lines.GetAt(index).substr(0, 3);
			while (line != "###"&&length>index) {
				this->lines.Delete(index);
				length = this->lines.GetLength();
				line = this->lines.GetAt(index).substr(0, 3);
			}
			this->lines.Delete(index);
			length = this->lines.GetLength();
		}
		index++;
	}
}

/*
* 연산 이름 : (파일정리)주석 제거
* 연산 기능 : 주석을 없앤다
* 입     력 : 없음
* 출     력 : 없음
*/
void FileLoad::CleanUpFile_DeleteComment() {
	int length;
	int index = 0;
	string line;
	int endIndex;
	int tempIndex;

	length = this->lines.GetLength();
	while (index < length) {
		line = this->lines.GetAt(index).substr(0, 2);
		if (line == "##") {
			this->lines.Delete(index);
			length = this->lines.GetLength();
		}
		else {
			line = this->lines.GetAt(index);
			endIndex = line.length();
			endIndex--;
			tempIndex = endIndex;
			while (tempIndex>0&&line.at(tempIndex) != ';') tempIndex--;
			if (tempIndex>0&&tempIndex < endIndex) {
				while (tempIndex < endIndex&&line.at(tempIndex) != '#') tempIndex++;
				if (line.at(tempIndex) == '#'&&line.at(tempIndex+1) == '#') {
					line = line.substr(0, tempIndex);
					this->lines.Modify(index, line);
				}
			}
		}
		index++;
	}
}

/*
* 연산 이름 : (파일정리)탭문자 제거
* 연산 기능 : 줄들의 탭문자를 없앤다
* 입     력 : 없음
* 출     력 : 없음
*/
void FileLoad::CleanUpFile_DeleteTab() {
	int length;
	int index = 0;
	int lineIndex;
	int endIndex;
	string line;

	length = this->lines.GetLength();
	while (index < length) {
		line = this->lines.GetAt(index);
		lineIndex = 0;
		endIndex = line.length();
		while (lineIndex<endIndex&&line.at(lineIndex)=='\t')lineIndex++;
		line = line.substr(lineIndex, endIndex);
		this->lines.Modify(index, line);
		index++;
	}
}

/*
* 연산 이름 : (파일정리)공란제거
* 연산 기능 : 비어있는 줄을 없앤다
* 입     력 : 없음
* 출     력 : 없음
*/
void FileLoad::CleanUpFile_DeleteNullLine() {
	int index=0;
	int length;
	string line;
	length = this->lines.GetLength();
	while (index < length) {
		line = this->lines.GetAt(index);
		if (line == "") {
			this->lines.Delete(index);
			length = this->lines.GetLength();
		}
		else {
			index++;
		}
	}
}

/*
* 연산 이름 : (파일정리)개행 제거
* 연산 기능 : 개행문자(\n)를 제거한다
* 입     력 : 없음
* 출     력 : 없음
*/
void FileLoad::CleanUpFile_DeleteNewLine() {
	int index = 0;
	int length;
	string line;

	length = this->lines.GetLength();
	while (index < length) {
		line = this->lines.GetAt(index);
		if (line.at(line.length() - 1) == '\n') {
			line = line.substr(0, line.length() - 1);
			this->lines.Modify(index, line);
		}
		index++;
	}
}