//Token.cpp

/*
*���� �̸� : Token.cpp
*��     �� : ��ū Ŭ���� ����Լ��� ������ ����ִ�
*��  �� �� : ��ȣ��
*�ۼ� ���� : 2016.07.19
*/

#include "Token.h"

/*
*�Լ� �̸� : �⺻ ������
*��     �� : �⺻ ��ū�� �����Ѵ�, ������ ��Ÿ�� �����ϸ� �̸��� ����д�
*��     �� : ����
*��     �� : ����
*/
Token::Token():kind(token_Etc), name("") {

}

/*
*�Լ� �̸� : �Ű������� ���� ������
*��     �� : ������ �̸��� �Է¹޾� ��ū�� �����Ѵ�
*��     �� : ��ū ����, �̸�
*��     �� : ����
*/
Token::Token(Token_Kind kind, string name):kind(kind), name(name) {
}

/*
*�Լ� �̸� : �Ҹ���
*��     �� : ��ū�� ���ش�
*��     �� : ����
*��     �� : ����
*/
Token::~Token() {

}

/*
*�Լ� �̸� : ���� ������
*��     �� : ��ū�� �����Ѵ�
*��     �� : ������ ��ū
*��     �� : ����
*/
Token::Token(const Token& source):kind(source.kind), name(source.name) {
}

/*
*�Լ� �̸� : ���� ������
*��     �� : ��ū�� �����Ѵ�(�����Ѵ�)
*��     �� : ������ ��ū
*��     �� : ����� ��ū
*/
Token& Token::operator=(const Token& other) {
	this->kind = other.kind;
	this->name = other.name;

	return *this;
}

/*
*�Լ� �̸� : ������ ��
*��     �� : �� ��ū�� ������ ���Ѵ�
*��     �� : �ٸ� ��ū
*��     �� : �� ���
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
*�Լ� �̸� : ������ ��(== ������)
*��     �� : �� ��ū�� ������ ���Ѵ�
*��     �� : �ٸ� ��ū
*��     �� : �� ���
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
*�Լ� �̸� : �ٸ��� ��
*��     �� : �� ��ū�� �ٸ��� ���Ѵ�
*��     �� : �ٸ� ��ū
*��     �� : �� ���
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
*�Լ� �̸� : �ٸ��� ��(!= ������)
*��     �� : �� ��ū�� �ٸ��� ���Ѵ�
*��     �� : �ٸ� ��ū
*��     �� : �� ���
*/
bool Token::operator!=(const Token& other){
	bool isNotEqual = false;

	if (this->kind != other.kind ||
		this->name != other.name) {
		isNotEqual = true;
	}

	return isNotEqual;
}
