//Lexical.cpp

#include "Lexical.h"

//함수 전방 선언



//기본 생성자
Lexical::Lexical() {

}

//소멸자
Lexical::~Lexical() {

}

/*
함수 이름 : 타입 확인용 배열 생성
기    능 : 읽을 문자의 타입을 보관하는 배열을 만든다
입    력 : 없음
출    력 : 완성된 배열
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
함수 이름 : 토큰라인 제작
기    능 : 문자열 라인을 입력받아 토큰라인으로 변환한다
입    력 : 라인
출    력 : 토큰라인
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
		//식별자/문자 처리
		if (IsLetter(line,i)==true){
			if (this->IsInstruction(line, i) == true) {
				this->GetInstruction(line, &i, &type, &tempID);
			}
			else {
				type = identifier;
				tempID = this->GetIdentfier(line, &i);
				if (tempID == "true" || tempID == "TRUE" || tempID == "false" || tempID == "FALSE") type = token_Constant;
			}

		}//문자상수 처리
		else if (this->letter[line.at(i)] == sign_DoubleQuotes || this->letter[line.at(i)] == sign_Quotes) {
			type = token_Constant;
			tempID = this->GetLetter(line, &i);
		}
		//숫자상수 처리
		else if (this->IsConstant(line,i) == true) {
			tempID = this->GetConstant(line, &i);
		}
		//그외 기호,연산자 처리
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
함수 이름 : (숫자)상수 확인
기    능 : 숫자로 된 상수인지 확인한다
입    력 : 라인, 위치
출    력 : 숫자 상수 여부
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
함수 이름 : 상수 변환
기    능 : 문자에서 상수인부분만 추려낸다
입    력 : 줄, 위치
출    력 : 상수, 위치
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
함수 이름 : 문자 확인
기    능 : 문자인지 확인한다
입    력 : 줄, 위치
출    력 : 문자여부, 위치
*/
bool Lexical::IsLetter(string line, Long index) {
	bool isLetter = false;

	if (this->letter[line.at(index)] == token_Letter || this->letter[line.at(index)] == ins_End) {
		isLetter = true;
	}

	return isLetter;
}

/*
함수 이름 : 명령어 여부 확인
기    능 : H언어의 명령어인지 확인한다
입    력 : 줄, 위치
출    력 : 명령어 여부
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
함수 이름 :명령어 변환
기    능 : 줄에서 명령어인게 확인될때, 명령어부분만추려낸다
입    력 : 줄, 위치
출    력 : 타입, 이름
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
함수 이름 : 식별자 변환
기    능 : 줄에서 식별자인게 확인될때, 식별자만 추려낸다
입    력 : 줄
출    력 : 식별자이름, 위치
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
함수 이름 : 문자상수 변환
기    능 : 문자상수를 추려낸다
입    력 : 줄
출    력 : 문자상수, 위치
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
함수 이름 : 대소비교 변환
기    능 : 대소비교를하는 연산자를 추려낸다
입    력 : 줄
출    력 : 타입,이름,위치
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