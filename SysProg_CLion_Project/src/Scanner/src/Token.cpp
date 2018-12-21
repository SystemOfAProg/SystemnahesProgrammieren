/*
 * Token.cpp
 *
 *  Created on: Nov 2, 2016
 *      Author: hede1021
 */

#include "../includes/Token.h"

Token::Token(Token::TType type, int line, int column, SymtabEntry* symtabentry, unsigned long value, char symbol) {
	this->type = type;
	this->line = line;
	this->column = column;
	this->symtabentry = symtabentry;
	this->value = value;
	this->symbol = symbol;
}

Token::~Token() {

}

int Token::getColumn() {
	return this->column;
}

int Token::getLine() {
	return this->line;
}

unsigned long Token::getValue() {
	return this->value;
}

SymtabEntry* Token::getSymtabEntry() {
	return this->symtabentry;
}

char Token::getSymbol() {
	return this->symbol;
}

Token::TType Token::getType() {
	return type;
}

char* Token::typeToString() {
	switch (this->type) {
		case Token::Identifier:
			return "Identifier";
		case Token::Integer:
			return "Integer";
		case Token::Unknown:
			return "Unknown";
		case Token::Assign:
			return "Assign";
		case Token::Plus:
			return "Plus";
		case Token::Minus:
			return "Minus";
		case Token::Colon:
			return "Colon";
		case Token::Star:
			return "Star";
		case Token::LessThan:
			return "LessThan";
		case Token::GreaterThan:
			return "GreaterThan";
		case Token::Equal:
			return "Equal";
		case Token::ColonBetweenEqual:
			return "ColonBetweenEqual";
		case Token::Exclamation:
			return "Exclamation";
		case Token::And:
			return "And";
		case Token::Semicolon:
			return "Semicolon";
		case Token::LeftParent:
			return "LeftParent";
		case Token::RightParent:
			return "RightParent";
		case Token::LeftCurved:
			return "LeftCurved";
		case Token::RightCurved:
			return "RightCurved";
		case Token::LeftBracket:
			return "LeftBracket";
		case Token::RightBracket:
			return "RightBracket";
		case Token::Error:
			return "Error";
		case Token::If:
			return "If";
		case Token::Else:
			return "Else";
		case Token::While:
			return "While";
		case Token::Write:
			return "Write";
		case Token::Read:
			return "Read";
		case Token::Int:
			return "Int";
		case Token::Eof:
			return "Eof";
		case Token::Comment:
			return "Comment";
		default:
			return "[Unknown Type]";
	}
}
