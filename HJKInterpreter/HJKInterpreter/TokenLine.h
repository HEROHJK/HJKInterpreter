//TokenLine.h

#ifndef _TOKENLINE_H
#define _TOKENLINE_H

#include "Array.h"
#include "Token.h"
typedef enum _Line_Kind {
	statementLine,//���� ����
	operatorLine,//���깮
	whileLine,//�ݺ���
	ifLine,//�Ǵܹ�
	elseLine,//�Ǵܹ�
	recordLine,//���ڵ幮
	inLine,//�Է¹�
	outLine//��¹�
}Line_Kind;

class TokenLine {
public:
	TokenLine();//�⺻ ������
	~TokenLine();//�Ҹ���
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