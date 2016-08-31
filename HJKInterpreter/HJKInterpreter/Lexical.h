//Lexical.h
#ifndef _LEXICAL_H
#define _LEXICAL_H
#include <string>
#include "Array.h"
#include "TokenLine.h"
using namespace std;

class Lexical {
private :
	Array<TokenLine> tokenLines;
	Token_Kind letter[256];

public:
	Lexical();
	~Lexical();
	void InitKindType();
	TokenLine MakeTokenLine(string line);
	Long AddTokenLine(TokenLine line);

private ://MakeTokenLine에 관한 처리
	bool IsConstant(string line, Long index);
	string GetConstant(string line, Long *index);
	bool IsLetter(string line, Long index);
	string GetIdentfier(string line, Long *index);
	string GetLetter(string line, Long *index);
	bool IsInstruction(string line, Long index);
	void GetInstruction(string line, Long *index, Token_Kind *type, string *tempID);
	void GetThan(string line, Long *index, Token_Kind *type, string *name);
};

inline Long Lexical::AddTokenLine(TokenLine line) {
	Long index;

	index=this->tokenLines.AppendFromRear(line);

	return index;
}

#endif _LEXICAL_H