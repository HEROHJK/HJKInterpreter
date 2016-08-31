//TokenLine.cpp
/*
파일 이름 : TokenLine.cpp
설     명 : 토큰라인의 클래스
작  성 자 : 김호종
작성 일자 : 2016.07.21
*/
#include "TokenLine.h"

//기본 생성자
TokenLine::TokenLine()
{
}

//소멸자
TokenLine::~TokenLine()
{
}

/*
함수 이름 : 토큰 추가
기     능 : 토큰 라인에 토큰을 추가한다
입     력 : 토큰
출     력 : 위치
*/
Long TokenLine::AddToken(Token token)
{
	Long index;
	index=this->tokenLine.AppendFromRear(token);

	return index;
}

/*
함수 이름 : 토큰 수정
기     능 : 토큰라인에 토큰을 수정한다
입     력 : 위치, 토큰
출     력 : 위치
*/
Long TokenLine::ModifyToken(Long index, Token token)
{
	this->tokenLine.Modify(index, token);

	return index;
}

/*
함수 이름 : 토큰 삭제
기     능 : 토큰라인의 토큰을 삭제한다
입     력 : 위치
출     력 : 위치(=삭제된 위치)
*/
Long TokenLine::DeleteToken(Long index)
{
	index = this->tokenLine.Delete(index);

	return index;
}