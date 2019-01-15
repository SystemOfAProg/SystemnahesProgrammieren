#include "../includes/Scanner.h"
#include <cstring>
#include <cstdlib>
#include <cerrno>

Scanner::Scanner(char* filename, Symboltable* symtab) {
	this->automat = new Automat();
	this->buffer = new Buffer(filename, 1024);
	this->symboltable = symtab;
}

Scanner::~Scanner() {
	delete automat;
	delete buffer;
}

Token* Scanner::nextToken() {
	int line   = this->buffer->getCurrentLine();
	int column = this->buffer->getCurrentPositionInLine();
	while (!this->automat->isStop()) {
		char c = buffer->getNextChar();
		if(this->positionChangingChar(c)) {
			line   = this->buffer->getCurrentLine();
			column = this->buffer->getCurrentPositionInLine();
		}
		this->automat->read(c);
	}
	Token* token = this->createToken(line, column);
	this->buffer->returnLastNCharacters(automat->getBack());
	this->automat->init();
	return token;
}

bool Scanner::positionChangingChar(char c) {
	return ((c == ' ') || (c == '\n'));
}

int Scanner::stringCompare( const char *string1, const char *string2) {
	const unsigned char *copyString1 = (const unsigned char *)string1;
    const unsigned char *copyString2 = (const unsigned char *)string2;
    while (*copyString1 != '\0') {
        if (*copyString2 == '\0') {
			return  1;
        } else if (*copyString2 > *copyString1) {
			return -1;
        } else if (*copyString1 > *copyString2) {
			return  1;
        }
        copyString1++;
        copyString2++;
    }
    if (*copyString2 != '\0') {
    	return -1;
    }
    return 0;
}

Token* Scanner::createToken(int line, int column) {
	switch (automat->getFinalState()) {
		case Automat::Error:
			return new Token(Token::Unknown, line, column, NULL, NULL, *automat->getLexem());
		case Automat::Identifier:
			return this->handleStateIdentifier(line, column);
		case Automat::Integer:
			return this->handleStateInteger(line, column);
		case Automat::LogicAnd:
			return new Token(Token::And, line, column, NULL, 0 , 0);
		case Automat::Equal:
			return new Token(Token::Equal, line, column, NULL, 0 , 0);
		case Automat::Assign:
			return new Token(Token::Assign, line, column, NULL, 0 , 0);
		case Automat::Colon:
			return new Token(Token::Colon, line, column, NULL, 0 , 0);
		case Automat::ColonBetweenEqualFinal:
			return new Token(Token::ColonBetweenEqual, line, column, NULL, 0 , 0);
		case Automat::CommentFinal:
			return new Token(Token::Comment, line, column, NULL, 0, 0);
		case Automat::Sign:
			return this->handleStateSign(line, column);
		case Automat::Eof:
		default:
			return new Token(Token::Eof, line, column, NULL, 0, 0);
	}
}

Token* Scanner::handleStateIdentifier(int line, int column) {
	if (stringCompare(automat->getLexem(), "WHILE") == 0 | stringCompare(automat->getLexem(), "while") == 0) {
		return new Token(Token::While, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	} else 	if (stringCompare(automat->getLexem(), "ELSE") == 0 | stringCompare(automat->getLexem(), "else") == 0) {
		return new Token(Token::Else, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	} else 	if (stringCompare(automat->getLexem(), "IF") == 0 | stringCompare(automat->getLexem(), "if") == 0) {
		return new Token(Token::If, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	} else if (stringCompare(automat->getLexem(), "write") == 0){
		return new Token(Token::Write, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	} else if (stringCompare(automat->getLexem(), "read") == 0){
		return new Token(Token::Read, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	} else if (stringCompare(automat->getLexem(), "int") == 0){
		return new Token(Token::Int, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	} else {
		return new Token(Token::Identifier, line, column, symboltable->insert(automat->getLexem()), 0, 0);
	}
}

Token* Scanner::handleStateInteger(int line, int column) {
	errno = 0;
	long temp = std::strtol(automat->getLexem(), 0, 10);
	if (errno == ERANGE) {
		return new Token(Token::Error, line, column, NULL, 0, 0);
	} else{
		return new Token(Token::Integer, line, column, NULL, temp , 0);
	}
}

Token* Scanner::handleStateSign(int line, int column) {
	if (*automat->getLexem() == ';') {
		return new Token(Token::Semicolon, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '+') {
		return new Token(Token::Plus, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '-') {
		return new Token(Token::Minus, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '*') {
		return new Token(Token::Star, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '<') {
		return new Token(Token::LessThan, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '>') {
		return new Token(Token::GreaterThan, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '!') {
		return new Token(Token::Exclamation, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '(') {
		return new Token(Token::LeftParent, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == ')') {
		return new Token(Token::RightParent, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '{') {
		return new Token(Token::LeftCurved, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '}') {
		return new Token(Token::RightCurved, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == '[') {
		return new Token(Token::LeftBracket, line, column, NULL, 0, 0);
	} else if (*automat->getLexem() == ']') {
		return new Token(Token::RightBracket, line, column, NULL, 0, 0);
	} else {
		return new Token(Token::Eof, line, column, NULL, 0, 0);
	}
}
