//Token.cpp

/*
*파일 이름 : Token.cpp
*기     능 : 토큰 클래스 멤버함수의 내용을 담고있다
*작  성 자 : 김호종
*작성 일자 : 2016.07.19
*/

#include "Token.h"

/*
*함수 이름 : 기본 생성자
*기     능 : 기본 토큰을 생성한다, 종류는 기타로 설정하며 이름은 비워둔다
*입     력 : 없음
*출     력 : 없음
*/
Token::Token():kind(token_Etc), name("") {

}

/*
*함수 이름 : 매개변수를 가진 생성자
*기     능 : 종류와 이름을 입력받아 토큰을 생성한다
*입     력 : 토큰 종류, 이름
*출     력 : 없음
*/
Token::Token(Token_Kind kind, string name):kind(kind), name(name) {
}

/*
*함수 이름 : 소멸자
*기     능 : 토큰을 없앤다
*입     력 : 없음
*출     력 : 없음
*/
Token::~Token() {

}

/*
*함수 이름 : 복사 생성자
*기     능 : 토큰을 복사한다
*입     력 : 복사할 토큰
*출     력 : 없음
*/
Token::Token(const Token& source):kind(source.kind), name(source.name) {
}

/*
*함수 이름 : 대입 연산자
*기     능 : 토큰을 대입한다(복사한다)
*입     력 : 복사할 토큰
*출     력 : 복사된 토큰
*/
Token& Token::operator=(const Token& other) {
	this->kind = other.kind;
	this->name = other.name;

	return *this;
}

/*
*함수 이름 : 같은지 비교
*기     능 : 두 토큰이 같은지 비교한다
*입     력 : 다른 토큰
*출     력 : 비교 결과
*/
bool Token::IsEqual(const Token& other) {
	bool isEqual=false;

	if (this->kind == other.kind &&
		this->name==other.name) {
		isEqual = true;
	}

	return isEqual;
}

/*
*함수 이름 : 같은지 비교(== 연산자)
*기     능 : 두 토큰이 같은지 비교한다
*입     력 : 다른 토큰
*출     력 : 비교 결과
*/
bool Token::operator==(const Token& other) {
	bool isEqual = false;

	if (this->kind == other.kind &&
		this->name == other.name) {
		isEqual = true;
	}

	return isEqual;
}

/*
*함수 이름 : 다른지 비교
*기     능 : 두 토큰이 다른지 비교한다
*입     력 : 다른 토큰
*출     력 : 비교 결과
*/
bool Token::IsNotEqual(const Token& other) {
	bool isNotEqual = false;

	if (this->kind != other.kind ||
		this->name != other.name) {
		isNotEqual = true;
	}

	return isNotEqual;
}

/*
*함수 이름 : 다른지 비교(!= 연산자)
*기     능 : 두 토큰이 다른지 비교한다
*입     력 : 다른 토큰
*출     력 : 비교 결과
*/
bool Token::operator!=(const Token& other){
	bool isNotEqual = false;

	if (this->kind != other.kind ||
		this->name != other.name) {
		isNotEqual = true;
	}

	return isNotEqual;
}
