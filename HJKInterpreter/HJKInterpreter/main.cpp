#include "FileLoad.h"
#include "Lexical.h"
#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
using namespace std;

int main(int argc, char *argv[]) {
	//char directory[256];
	FileLoad fl;
	string fileDirectory;
	string fileName;
	string totalDirectory;
	int i = 0;
	int length = fl.GetLineLength();
	char number[100];
	//gets_s(directory, 200);

	totalDirectory = fl.SetDirectory("D:\\study\\�����Ϸ� ������Ʈ\\�����ڷ�\\IsPrimeNumber.hjk");
	fileDirectory = fl.GetDirectory();
	fileName = fl.GetFileName();

	cout << totalDirectory << endl << "���� ��� : " << fileDirectory << endl << "���� �̸� : " << fileName << endl;

	fl.Load(totalDirectory);
	i = 0;
	length = fl.GetLineLength();
	while (i < length) {
		sprintf(number, "%2d", i + 1);
		cout << number << " : " << fl.GetLine(i) << endl;
		i++;
	}
	Lexical lexical;
	TokenLine tl;
	lexical.InitKindType();
	i = 0;
	int j;
	FILE *saveFile;
	string dir;
	dir = fl.GetDirectory();
	dir += "\\���ֺм�����.txt";
	saveFile = fopen(dir.c_str(), "wt+");
	while (i < fl.GetLineLength()) {
		tl = lexical.MakeTokenLine(fl.GetLine(i));
		lexical.AddTokenLine(tl);
		j = 0;
		sprintf(number, "%2d", i + 1);
		cout << number << " : ";
		fprintf(saveFile, number);
		fprintf(saveFile, " : ");
		while (j < tl.GetLength()) {
			cout << tl.GetToken(j).GetName() << " ";

			fprintf(saveFile, tl.GetToken(j).GetName().c_str());
			fprintf(saveFile, " ");

			j++;
		}
		cout << endl;
		fprintf(saveFile, "\n");
		i++;
	}

	getchar();
	return 0;
}