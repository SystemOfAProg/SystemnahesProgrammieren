/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

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
	while (!automat->isStop()) {
		unsigned int line = buffer->getCurrentLine();
        unsigned int column = buffer->getCurrentPositionInLine();
        char symbol = buffer->getNextChar();
        automat->read(symbol, line, column);
	}
	Token* token = createToken();
	automat->getBack();
	buffer->returnLastNCharacters(automat->getBack());
	automat->reset();
	return token;
}

int Scanner::stringCompare( const char *s1, const char *s2) {
	const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0') {
        if (*p2 == '\0') return  1;
        if (*p2 > *p1)   return -1;
        if (*p1 > *p2)   return  1;

        p1++;
        p2++;
    }

    if (*p2 != '\0') return -1;

    return 0;
}

Token* Scanner::createToken() {
	switch (automat->getLastFinalState()) {
		case Automat::Error:
			return new Token(Token::Unknown, automat->getLine(), automat->getColumn(), NULL, NULL, *automat->getLexem());
		case Automat::Identifier:
			if (stringCompare(automat->getLexem(), "WHILE") == 0 | stringCompare(automat->getLexem(), "while") == 0) {
				return new Token(Token::While, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			} else 	if (stringCompare(automat->getLexem(), "ELSE") == 0 | stringCompare(automat->getLexem(), "else") == 0) {
				return new Token(Token::Else, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			} else 	if (stringCompare(automat->getLexem(), "IF") == 0 | stringCompare(automat->getLexem(), "if") == 0) {
				return new Token(Token::If, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			} else if (stringCompare(automat->getLexem(), "write") == 0){
				return new Token(Token::Write, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			} else if (stringCompare(automat->getLexem(), "read") == 0){
				return new Token(Token::Read, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			} else if (stringCompare(automat->getLexem(), "int") == 0){
				return new Token(Token::Int, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			} else {
				return new Token(Token::Identifier, automat->getLine(), automat->getColumn(), symboltable->insert(automat->getLexem()), NULL, NULL);
			}

		case Automat::Integer: {
			errno = 0;
			long temp = std::strtol(automat->getLexem(), NULL, 10);
			if (errno == ERANGE) {
				return new Token(Token::Error, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else{
				return new Token(Token::Integer, automat->getLine(), automat->getColumn(), NULL, temp , NULL);
			}
		}
		case Automat::DoubleAnd:
			return new Token(Token::And,automat->getLine(), automat->getColumn(), NULL, NULL , NULL);
		case Automat::Equal:
			return new Token(Token::Equal, automat->getLine(), automat->getColumn(), NULL, NULL , NULL);
		case Automat::Assign:
			return new Token(Token::Assign, automat->getLine(), automat->getColumn(), NULL, NULL , NULL);
		case Automat::Colon:
			return new Token(Token::Colon, automat->getLine(), automat->getColumn(), NULL, NULL , NULL);
		case Automat::ColonBetweenEqualFinal:
			return new Token(Token::ColonBetweenEqual, automat->getLine(), automat->getColumn(), NULL, NULL , NULL);
		case Automat::CommentFinal:
			return new Token(Token::Comment, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
		case Automat::Sign:
			if (*automat->getLexem() == ';') {
				return new Token(Token::Semicolon, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '+') {
				return new Token(Token::Plus, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '-') {
				return new Token(Token::Minus, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '*') {
				return new Token(Token::Star, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '<') {
				return new Token(Token::LessThan, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '>') {
				return new Token(Token::GreaterThan, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '!') {
				return new Token(Token::Exclamation, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '(') {
				return new Token(Token::LeftParent, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == ')') {
				return new Token(Token::RightParent, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '{') {
				return new Token(Token::LeftCurved, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '}') {
				return new Token(Token::RightCurved, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == '[') {
				return new Token(Token::LeftBracket, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			} else if (*automat->getLexem() == ']') {
				return new Token(Token::RightBracket, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
			}
		case Automat::Eof:
		default:
			return new Token(Token::Eof, automat->getLine(), automat->getColumn(), NULL, NULL, NULL);
	}
}
