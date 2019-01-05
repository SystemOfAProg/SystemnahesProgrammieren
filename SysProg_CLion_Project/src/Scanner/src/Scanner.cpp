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
		// unsigned int line = buffer->getCurrentLine();
        // unsigned int column = buffer->getCurrentPositionInLine();
        char symbol = buffer->getNextChar();
        automat->read(symbol);
	}
	Token* token = createToken();
	automat->getBack();
	buffer->returnLastNCharacters(automat->getBack());
	automat->init();
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
	switch (automat->getFinalState()) {
		case Automat::Error:
			return new Token(Token::Unknown, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, NULL, *automat->getLexem());
		case Automat::Identifier:
			if (stringCompare(automat->getLexem(), "WHILE") == 0 | stringCompare(automat->getLexem(), "while") == 0) {
				return new Token(Token::While, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			} else 	if (stringCompare(automat->getLexem(), "ELSE") == 0 | stringCompare(automat->getLexem(), "else") == 0) {
				return new Token(Token::Else, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			} else 	if (stringCompare(automat->getLexem(), "IF") == 0 | stringCompare(automat->getLexem(), "if") == 0) {
				return new Token(Token::If, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			} else if (stringCompare(automat->getLexem(), "write") == 0){
				return new Token(Token::Write, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			} else if (stringCompare(automat->getLexem(), "read") == 0){
				return new Token(Token::Read, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			} else if (stringCompare(automat->getLexem(), "int") == 0){
				return new Token(Token::Int, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			} else {
				return new Token(Token::Identifier, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), symboltable->insert(automat->getLexem()), 0, 0);
			}

		case Automat::Integer: {
			errno = 0;
			long temp = std::strtol(automat->getLexem(), 0, 10);
			if (errno == ERANGE) {
				return new Token(Token::Error, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else{
				return new Token(Token::Integer, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, temp , 0);
			}
		}
		case Automat::LogicAnd:
			return new Token(Token::And, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0 , 0);
		case Automat::Equal:
			return new Token(Token::Equal, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0 , 0);
		case Automat::Assign:
			return new Token(Token::Assign, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0 , 0);
		case Automat::Colon:
			return new Token(Token::Colon, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0 , 0);
		case Automat::ColonBetweenEqualFinal:
			return new Token(Token::ColonBetweenEqual, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0 , 0);
		case Automat::CommentFinal:
			return new Token(Token::Comment, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
		case Automat::Sign:
			if (*automat->getLexem() == ';') {
				return new Token(Token::Semicolon, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '+') {
				return new Token(Token::Plus, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '-') {
				return new Token(Token::Minus, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '*') {
				return new Token(Token::Star, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '<') {
				return new Token(Token::LessThan, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '>') {
				return new Token(Token::GreaterThan, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '!') {
				return new Token(Token::Exclamation, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '(') {
				return new Token(Token::LeftParent, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == ')') {
				return new Token(Token::RightParent, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '{') {
				return new Token(Token::LeftCurved, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '}') {
				return new Token(Token::RightCurved, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == '[') {
				return new Token(Token::LeftBracket, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			} else if (*automat->getLexem() == ']') {
				return new Token(Token::RightBracket, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
			}
		case Automat::Eof:
		default:
			return new Token(Token::Eof, buffer->getCurrentLine(), buffer->getCurrentPositionInLine(), NULL, 0, 0);
	}
}
