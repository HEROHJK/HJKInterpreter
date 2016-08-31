//TokenLine.cpp
/*
���� �̸� : TokenLine.cpp
��     �� : ��ū������ Ŭ����
��  �� �� : ��ȣ��
�ۼ� ���� : 2016.07.21
*/
#include "TokenLine.h"

//�⺻ ������
TokenLine::TokenLine()
{
}

//�Ҹ���
TokenLine::~TokenLine()
{
}

/*
�Լ� �̸� : ��ū �߰�
��     �� : ��ū ���ο� ��ū�� �߰��Ѵ�
��     �� : ��ū
��     �� : ��ġ
*/
Long TokenLine::AddToken(Token token)
{
	Long index;
	index=this->tokenLine.AppendFromRear(token);

	return index;
}

/*
�Լ� �̸� : ��ū ����
��     �� : ��ū���ο� ��ū�� �����Ѵ�
��     �� : ��ġ, ��ū
��     �� : ��ġ
*/
Long TokenLine::ModifyToken(Long index, Token token)
{
	this->tokenLine.Modify(index, token);

	return index;
}

/*
�Լ� �̸� : ��ū ����
��     �� : ��ū������ ��ū�� �����Ѵ�
��     �� : ��ġ
��     �� : ��ġ(=������ ��ġ)
*/
Long TokenLine::DeleteToken(Long index)
{
	index = this->tokenLine.Delete(index);

	return index;
}