/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"
#include <iostream>

Automat::Automat() {
	init();
}

Automat::~Automat() {
}

void Automat::init(){
	this->currentState = Start;
	this->finalState = Start;
	this->stop = false;
	this->lexem = new char[2048];
	for (unsigned int i = 0; i <= 2048; ++i) {
		this->lexem[i] = '\0';
	}
	this->stepsBack = 0;
	this->index = 0;
}

void Automat::reset() {
	delete[] this->lexem;
	this->init();
}

Automat::State Automat::getCurrentState(){
	return this->currentState;
}

Automat::State Automat::getFinalState(){
	return this->finalState;
}

char* Automat::getLexem(){
	return this->lexem;
}

int Automat::getBack(){
	return this->stepsBack;
}

bool Automat::isStop(){
	return this->stop;
}

bool Automat::isAlpha(char c) {
	return (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') ? true : false;
}

bool Automat::isDigit(char c) {
	char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
	bool isDigit = false;
		for (int i=0; i < 9; i++){
			if(c == digits[i])
				isDigit = true;
		}
		return isDigit;
}

bool Automat::isSign(char c) {
	char signs[13] = {'+','-','<','>','!',';','(',')','{','}','[',']','*'};
	bool isSign = false;
	for (int i=0; i < 13; i++){
		if(c == signs[i])
			isSign = true;
	}
	return isSign;
}

bool Automat::isTerminatingOrBreak(char c){
	return (c == '\0'  && c == '\n');
}

bool Automat::addToLexem(char c) {
	this->lexem[index++] = c;
	/*if(c == '\0')
		this->lexem = "eof";*/
	return true;
}

void Automat::checkStartState(char c){
	if(isAlpha(c)){
		this->currentState = Identifier;
		this->finalState = Identifier;
		addToLexem(c);
	}else if(isDigit(c)){
		this->currentState = Integer;
		this->finalState = Integer;
		addToLexem(c);
	}else if(isSign(c)){
		this->finalState = Sign;
		addToLexem(c);
		stop = true;
	}else if(c == ':'){
		this->currentState = Colon;
		this->finalState = Colon;
		addToLexem(c);
	}else if(c == '='){
		this->currentState = Equal;
		this->finalState = Equal;
		addToLexem(c);
	}else if(c == '&'){
		this->currentState = And;
		addToLexem(c);
	}else if(c == ' ' || c == '\n'){
		this->currentState = Start;
	}else if(c == '\0'){
		this->currentState = Eof;
        this->finalState = Eof;
		addToLexem(c);
		stop = true;
	}else {
		this->currentState = Error;
        this->finalState = Error;
		addToLexem(c);
		stop = true;
	}
}

void Automat::read(char c, unsigned int line, unsigned int column) {
	switch (currentState) {
	case Start:
		this->line = line;
		this->column = column;
		checkStartState(c);
		break;
	case Identifier:
		if( isAlpha(c) || isDigit(c) )
			addToLexem(c);
		else{
			if( !isTerminatingOrBreak(c) ){
				stepsBack++;
			}
			stop = true;
		}
		break;
	case Integer:
		if( isDigit(c) )
			addToLexem(c);
		else{
			if( !isTerminatingOrBreak(c) )
				stepsBack++;
			stop = true;
		}
		break;
	case Colon:
		if(c == '='){
			this->currentState = Assign;
			this->finalState = Assign;
			addToLexem(c);
			stop = true;
		}else if(c == '*'){
			this->currentState = CommentStart;
			addToLexem(c);
		}else {
			if( !isTerminatingOrBreak(c) ){
				stepsBack++;
			}
			stop = true;
		}
		break;
	case Equal:
		if(c ==':'){
			this->currentState = ColonBetweenEqual;
			addToLexem(c);
		}else{
			if( !isTerminatingOrBreak(c) )
				stepsBack++;
			stop = true;
		}
		break;
	case And:
		if( !isTerminatingOrBreak(c) )
			stepsBack++;
		c == '&' ? this->finalState = LogicAnd : this->currentState = Error;
		stop = true;
		break;
	case ColonBetweenEqual:
		if(c == '='){
			this->finalState = ColonBetweenEqualFinal;
			addToLexem(c);
		}else{
			this->currentState = Equal;
			stepsBack += 2;
		}
		stop = true;
		break;
	case CommentStart:
		if(c == '\0'){
			this->finalState = CommentFinal;
			stop = true;
		}else if(c == '*'){
			this->currentState = CommentClose;
			addToLexem(c);
		}
		break;
	case CommentClose:
		if(c == ':' || c == '\0'){
			this->finalState = CommentFinal;
			addToLexem(c);
			stop = true;
		}else{
			this->currentState = CommentStart;
		}
		break;
	default:
		stop = true;
	}
}

unsigned int Automat::getLine() {
	return this->line;
}

unsigned int Automat::getColumn() {
	return this->column;
}
