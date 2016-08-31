//Lexical.cpp

#include "Lexical.h"

//�Լ� ���� ����



//�⺻ ������
Lexical::Lexical() {

}

//�Ҹ���
Lexical::~Lexical() {

}

/*
�Լ� �̸� : Ÿ�� Ȯ�ο� �迭 ����
��    �� : ���� ������ Ÿ���� �����ϴ� �迭�� �����
��    �� : ����
��    �� : �ϼ��� �迭
*/
void Lexical::InitKindType() {
	int i = 0;
	while (i < 256) {
		this->letter[i] = token_Etc;
		i++;
	}
	this->letter['_'] = token_Letter;
	i = 'a';
	while (i < 'z') {
		this->letter[i] = token_Letter;
		i++;
	}
	i = 'A';
	while (i < 'Z') {
		this->letter[i] = token_Letter;
		i++;
	}
	i = '0';
	while (i < '9') {
		this->letter[i] = token_Constant;
		i++;
	}

	this->letter['('] = sign_lParen;
	this->letter[')'] = sign_rParen;
	this->letter['+'] = sign_Plus;
	this->letter['-'] = sign_Minus;
	this->letter['*'] = sign_Multiple;
	this->letter['/'] = sign_Division;
	this->letter['#'] = ins_End;
	this->letter[','] = sign_Comma;
	this->letter[';'] = sign_Semicolon;
	this->letter['<'] = sign_IsSmall;
	this->letter['>'] = sign_IsBig;
	this->letter['='] = sign_Equal;
	this->letter['%'] = sign_Remainder;
	this->letter['\"'] = sign_DoubleQuotes;
	this->letter['\''] = sign_Quotes;

}

/*
�Լ� �̸� : ��ū���� ����
��    �� : ���ڿ� ������ �Է¹޾� ��ū�������� ��ȯ�Ѵ�
��    �� : ����
��    �� : ��ū����
*/
TokenLine Lexical::MakeTokenLine(string line) {
	TokenLine tokenLine;
	char letter;
	Long i = 0;
	Token_Kind type;
	string tempID;
	while (i<(Long)line.length()) {
		tempID = "";
		type = token_Etc;
		letter = line.at(i);
		//�ĺ���/���� ó��
		if (IsLetter(line,i)==true){
			if (this->IsInstruction(line, i) == true) {
				this->GetInstruction(line, &i, &type, &tempID);
			}
			else {
				type = identifier;
				tempID = this->GetIdentfier(line, &i);
				if (tempID == "true" || tempID == "TRUE" || tempID == "false" || tempID == "FALSE") type = token_Constant;
			}

		}//���ڻ�� ó��
		else if (this->letter[line.at(i)] == sign_DoubleQuotes || this->letter[line.at(i)] == sign_Quotes) {
			type = token_Constant;
			tempID = this->GetLetter(line, &i);
		}
		//���ڻ�� ó��
		else if (this->IsConstant(line,i) == true) {
			tempID = this->GetConstant(line, &i);
		}
		//�׿� ��ȣ,������ ó��
		else {
			switch (this->letter[line.at(i)]) {
			case sign_lParen:type = sign_lParen; tempID = "("; break;
			case sign_rParen:type = sign_rParen; tempID = ")"; break;
			case sign_Plus:type = sign_Plus; tempID = "+"; break;
			case sign_Minus:type = sign_Minus; tempID = "-"; break;
			case sign_Multiple:type = sign_Multiple; tempID = "*"; break;
			case sign_Division:type = sign_Division; tempID = "/"; break;
			case sign_Equal:type = sign_Equal; tempID = "="; break;
			case sign_Dot:type = sign_Dot; tempID = "."; break;
			case sign_Remainder:type = sign_Remainder; tempID = "%"; break;
			case sign_Comma:type = sign_Comma; tempID = ","; break;
			case sign_IsBig: type = sign_IsBigThan; this->GetThan(line, &i,&type,&tempID);
			case sign_IsSmall:type = sign_IsSmallThan; this->GetThan(line, &i,&type,&tempID);
			default:break;

			}
			i++;
		}
		if (tempID != "") {
			tokenLine.AddToken(Token(type, tempID));
		}
	}
	return tokenLine;
}

/*
�Լ� �̸� : (����)��� Ȯ��
��    �� : ���ڷ� �� ������� Ȯ���Ѵ�
��    �� : ����, ��ġ
��    �� : ���� ��� ����
*/
bool Lexical::IsConstant(string line, Long index) {
	bool isConstant = false;
	if (this->letter[line.at(index)] == token_Constant || this->letter[line.at(index)] == sign_Minus) {
		if (this->letter[line.at(index)] == token_Constant) isConstant = true;
		if (this->letter[line.at(index)] == sign_Minus&&this->letter[line.at((index) - 1)] == sign_Equal) isConstant=true;
	}

	return isConstant;
}

/*
�Լ� �̸� : ��� ��ȯ
��    �� : ���ڿ��� ����κκи� �߷�����
��    �� : ��, ��ġ
��    �� : ���, ��ġ
*/
string Lexical::GetConstant(string line, Long *index) {
	string identifier="";
	Long length = line.length();
	if (this->letter[line.at(*index)] == sign_Dot) {
		identifier = "-";
		(*index)++;
	}

	while (*index < length && (this->letter[line.at(*index)] == token_Constant || this->letter[line.at(*index)] == sign_Dot)) {
		identifier += line.at(*index);
		(*index)++;
	}

	return identifier;
}

/*
�Լ� �̸� : ���� Ȯ��
��    �� : �������� Ȯ���Ѵ�
��    �� : ��, ��ġ
��    �� : ���ڿ���, ��ġ
*/
bool Lexical::IsLetter(string line, Long index) {
	bool isLetter = false;

	if (this->letter[line.at(index)] == token_Letter || this->letter[line.at(index)] == ins_End) {
		isLetter = true;
	}

	return isLetter;
}

/*
�Լ� �̸� : ��ɾ� ���� Ȯ��
��    �� : H����� ��ɾ����� Ȯ���Ѵ�
��    �� : ��, ��ġ
��    �� : ��ɾ� ����
*/
bool Lexical::IsInstruction(string line, Long index) {
	bool isInstruction = false;
	string temp;
	temp = line.substr(index,index+7);
	if (temp.substr(0, 3) == "int") isInstruction = true;
	else if (temp.substr(0, 6) == "double") isInstruction = true;
	else if (temp.substr(0, 4) == "char") isInstruction = true;
	else if (temp.substr(0, 6) == "string") isInstruction = true;
	else if (temp.substr(0, 4) == "bool") isInstruction = true;
	else if (this->letter[line.at(index)] == ins_End) isInstruction = true;

	return isInstruction;
}

/*
�Լ� �̸� :��ɾ� ��ȯ
��    �� : �ٿ��� ��ɾ��ΰ� Ȯ�εɶ�, ��ɾ�κи��߷�����
��    �� : ��, ��ġ
��    �� : Ÿ��, �̸�
*/
void Lexical::GetInstruction(string line, Long *index, Token_Kind *type, string *tempID) {
	string temp;

	temp = line.substr(*index, (*index) + 7);
	if (temp.substr(0, 3) == "int") {
		*type = ins_Int; 
		*tempID = "int";
		*index += 3;
	}
	else if (temp.substr(0, 6) == "double") {
		*type = ins_Double;
		*tempID = "double";
		*index += 6;
	}
	else if (temp.substr(0, 4) == "char") {
		*type = ins_Char;
		*tempID = "char";
		*index += 4;
	}
	else if (temp.substr(0, 6) == "string") {
		*type = ins_String;
		*tempID = "string";
		*index += 6;
	}
	else if (temp.substr(0, 4) == "bool") {
		*type = ins_Bool;
		*tempID = "bool";
		*index += 4;
	}
	else if (temp == "#record") {
		*type = ins_Record;
		*tempID = "record";
		*index += 7;
	}
	else if (temp == "#define") {
		*type = ins_Macro;
		*tempID = "macro";
		*index += 7;
	}
	else if (temp.substr(0, 6) == "#while") {
		*type = ins_While;
		*tempID = "loop";
		*index += 6;
	}
	else if (temp.substr(0, 3) == "#if") {
		*type = ins_If;
		*tempID = "if";
		*index += 3;
	}
	else if (temp.substr(0, 5) == "#else") {
		*type = ins_Else;
		*tempID = "else";
		*index += 5;
	}
	else if (temp.substr(0, 3) == "#in") {
		*type = ins_Input;
		*tempID = "input";
		*index += 3;
	}
	else if (temp.substr(0, 4) == "#out") {
		*type = ins_Output;
		*tempID = "output";
		*index += 4;
	}
	else if (this->letter[temp.at(*index)] == ins_End) {
		*type = ins_End;
		*tempID = "end";
		*index += 1;
	}
}

/*
�Լ� �̸� : �ĺ��� ��ȯ
��    �� : �ٿ��� �ĺ����ΰ� Ȯ�εɶ�, �ĺ��ڸ� �߷�����
��    �� : ��
��    �� : �ĺ����̸�, ��ġ
*/
string Lexical::GetIdentfier(string line, Long *index) {
	string idString="";
	while (*index < (Long)line.length() &&
		(this->letter[line.at(*index)] == token_Letter || this->letter[line.at(*index)] == token_Constant)) {
		idString = idString + (line.at(*index));
		(*index)++;
	}
	return idString;
}

/*
�Լ� �̸� : ���ڻ�� ��ȯ
��    �� : ���ڻ���� �߷�����
��    �� : ��
��    �� : ���ڻ��, ��ġ
*/
string Lexical::GetLetter(string line, Long *index) {
	string letterString;
	if (this->letter[line.at(*index)] == sign_DoubleQuotes) letterString = "\"";
	else letterString = "'";
	(*index)++;
	while (*index < (Long)line.length() && this->letter[line.at(*index)] != sign_DoubleQuotes &&
		this->letter[line.at(*index)] != sign_Quotes) {
		letterString += line.at(*index);
		(*index)++;
	}
	letterString += line.at(*index);
	(*index)++;

	return letterString;
}

/*
�Լ� �̸� : ��Һ� ��ȯ
��    �� : ��Һ񱳸��ϴ� �����ڸ� �߷�����
��    �� : ��
��    �� : Ÿ��,�̸�,��ġ
*/
void Lexical::GetThan(string line, Long *index, Token_Kind *type, string *name) {

	if (this->letter[line.at(*index)] == sign_IsBig) {
		if (*index < line.length()&&this->letter[line.at((*index)+1)]==sign_Equal) {
			*type = sign_IsBigThan;
			*name = ">=";
			(*index)++;
		}
		else {
			*type = sign_IsBig;
			*name = ">";
		}
	}
	else {
		if (*index < line.length() && this->letter[line.at((*index) + 1)] == sign_Equal) {
			*type = sign_IsSmallThan;
			*name = "<=";
			(*index)++;
		}
		else {
			*type = sign_IsSmall;
			*name = "<";
		}
	}

}