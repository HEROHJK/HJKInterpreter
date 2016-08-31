//TokenLine.h

#ifndef _TOKENLINE_H
#define _TOKENLINE_H

#include "Array.h"
#include "Token.h"
typedef enum _Line_Kind {
	statementLine,//변수 선언문
	operatorLine,//연산문
	whileLine,//반복문
	ifLine,//판단문
	elseLine,//판단문
	recordLine,//레코드문
	inLine,//입력문
	outLine//출력문
}Line_Kind;

class TokenLine {
public:
	TokenLine();//기본 생성자
	~TokenLine();//소멸자
	Line_Kind GetKind();
	Token GetToken(Long index);
	Long AddToken(Token token);
	Long ModifyToken(Long index, Token token);
	Long DeleteToken(Long index);
	Long GetLength();
private:
	Line_Kind kind;
	Array<Token> tokenLine;

};

inline Line_Kind TokenLine::GetKind() {
	return this->kind;
}

inline Token TokenLine::GetToken(Long index) {
	return this->tokenLine.GetAt(index);
}

inline Long TokenLine::GetLength() {
	Long length = this->tokenLine.GetLength();

	return length;
}

#endif _TOKENLINE_H