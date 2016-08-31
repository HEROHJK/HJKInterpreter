//Token.h
#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>
using namespace std;
typedef enum _Token_Kind {
	identifier,
	sign_Equal,
	sign_lParen,
	sign_rParen,
	sign_Plus,
	sign_Minus,
	sign_Multiple,
	sign_Division,
	sign_Comma,
	sign_Semicolon,
	sign_Dot,
	sign_Not,
	sign_And,
	sgin_Or,
	sign_IsEqual,
	sign_IsNotEqual,
	sign_IsSmall,
	sign_IsBig,
	sign_IsSmallThan,
	sign_IsBigThan,
	sign_Quotes,
	sign_DoubleQuotes,
	sign_Remainder,
	ins_Macro,
	ins_Int,
	ins_Double,
	ins_Char,
	ins_String,
	ins_Bool,
	ins_Record,
	ins_If,
	ins_Else,
	ins_While,
	ins_Input,
	ins_Output,
	ins_End,
	token_Constant,
	token_Letter,
	token_Etc
}Token_Kind;

class Token {
private:
	Token_Kind kind;
	string name;
public:
	Token();
	Token(Token_Kind kind, string name);
	Token(const Token& source);
	~Token();
	Token& operator=(const Token& other);
	bool IsEqual(const Token& other);
	bool operator==(const Token& other);
	bool IsNotEqual(const Token& other);
	bool operator!=(const Token& other);
	Token_Kind GetKind();
	string GetName();

};

inline Token_Kind Token::GetKind() {
	return this->kind;
}

inline string Token::GetName() {
	return this->name;
}

#endif _TOKEN_H