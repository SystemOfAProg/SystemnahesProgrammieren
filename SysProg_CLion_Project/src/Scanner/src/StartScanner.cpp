using namespace std;
#include "../includes/Scanner.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
	Symboltable* symtab = new Symboltable;
	Scanner* scanner = new Scanner(argv[1], symtab);
	ofstream output;
    output.open(argv[2]);
	Token* t;
	while ((t = scanner->nextToken())->getType() != Token::Eof) {
		switch (t->getType()) {
			case Token::Identifier:
				output << "Token " << t->typeToString() << "\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn() << "\t\tLexem: " << t->getSymtabEntry()->getInfo()->getName() << endl;
				break;
			case Token::Integer:
				output << "Token " << t->typeToString() << "\t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn() << "\t\tValue: " << t->getValue()<< endl;
				break;
			case Token::And:
			case Token::Assign:
			case Token::Plus:
			case Token::Minus:
			case Token::Colon:
			case Token::Star:
			case Token::LessThan:
			case Token::Equal:
			case Token::Semicolon:
			case Token::While:
			case Token::If:
			case Token::Else:
			case Token::Write:
			case Token::Read:
				output  << "Token " << t->typeToString() << "\t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn() << endl;
				break;
			case Token::ColonBetweenEqual:
			case Token::Exclamation:
			case Token::GreaterThan:
			case Token::LeftParent:
			case Token::RightParent:
			case Token::LeftCurved:
			case Token::RightCurved:
			case Token::LeftBracket:
			case Token::RightBracket:
				output  << "Token " << t->typeToString() << "\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn() << endl;
				break;
			case Token::Unknown:
				output  << "Token Unknown  " << "\t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn()  << "\t\tSymbol: " << t->getSymbol() << endl;
				cerr << "Token Unknown  " << "\t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn()  << "\t\tSymbol: " << t->getSymbol() << endl;
				break;
			case Token::Comment:
				break;
			case Token::Error:
				cerr << "error, overflow in line " << t->getLine()<< " column " << t->getColumn() << endl;
				break;
		}
	}
	delete symtab;
	delete scanner;
	output.close();
	return 0;
}

