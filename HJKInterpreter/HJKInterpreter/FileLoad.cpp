//FileLoad.cpp
/*
*���� �̸� : FileLoad.cpp
*��     �� : ���� ���翡 ���� ����� ����Ѵ�(��������, �ּ� ����)
*�� ��  �� : ��ȣ��
*�ۼ� ���� : 2016.07.12
*/

#include "FileLoad.h"
#pragma warning(disable:4996)

/*
* ���� �̸� : ������
* ���� ��� : �������� Ŭ������ �����Ѵ�
* ��     �� : ����
* ��     �� : ����
*/
FileLoad::FileLoad() {

}

/*
* ���� �̸� : �Ҹ���
* ���� ��� : �������� Ŭ������ �����
* ��     �� : ����
* ��     �� : ����
*/
FileLoad::~FileLoad() {

}

/*
* ���� �̸� : ���� ������
* ���� ��� : �������� Ŭ������ �����Ѵ�
* ��     �� : ������ �������� Ŭ����
* ��     �� : ����� �������� Ŭ����
*/
FileLoad::FileLoad(const FileLoad& source) {
	this->lines = source.lines;
	this->directory = source.directory;
	this->fileName = source.fileName;
}

/*
* ���� �̸� : ��� ����
* ���� ��� : ������ ���ϸ�� ��θ� �Է¹޾� �������� Ŭ������ ���� �����Ѵ�
* ��     �� : ���ϰ��
* ��     �� : ���ϸ�� ���
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
* ���� �̸� : ����
* ���� ��� : ���ϰ�ο��ִ� ������ �ҷ��� ������ �����Ѵ�
* ��     �� : ���ϰ��
* ��     �� : �ٵ�
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
* ���� �̸� : ���� ����
* ���� ��� : �ٵ��� �ʿ� ���� �κ��� �����Ѵ�
* ��     �� : ����
* ��     �� : ����
*/
void FileLoad::CleanUpFile() {
	this->CleanUpFile_DeleteNewLine();
	this->CleanUpFile_DeleteBlockComment();
	this->CleanUpFile_DeleteComment();
	this->CleanUpFile_DeleteTab();
	this->CleanUpFile_DeleteNullLine();
}

/*
* ���� �̸� : (��������)��� �ּ� ����
* ���� ��� : ��ϴ����� �ּ��� ���ش�
* ��     �� : ����
* ��     �� : ����
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
* ���� �̸� : (��������)�ּ� ����
* ���� ��� : �ּ��� ���ش�
* ��     �� : ����
* ��     �� : ����
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
* ���� �̸� : (��������)�ǹ��� ����
* ���� ��� : �ٵ��� �ǹ��ڸ� ���ش�
* ��     �� : ����
* ��     �� : ����
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
* ���� �̸� : (��������)��������
* ���� ��� : ����ִ� ���� ���ش�
* ��     �� : ����
* ��     �� : ����
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
* ���� �̸� : (��������)���� ����
* ���� ��� : ���๮��(\n)�� �����Ѵ�
* ��     �� : ����
* ��     �� : ����
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