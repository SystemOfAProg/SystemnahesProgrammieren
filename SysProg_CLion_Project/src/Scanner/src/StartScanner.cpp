using namespace std;
#include "../includes/Scanner.h"
#include <iostream>
#include <fstream>

// This is a test, if I can get this line committed from my iPad

int main(int argc, char **argv) {
	Symboltable* symtab = new Symboltable;
	Scanner* scanner = new Scanner(argv[1], symtab);
	cout << "Start scanning program " << argv[1] << " and writing output to " << argv[2] << "." << endl;
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
			case Token::Int:
				output << "Token " << t->typeToString() << "\t\t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn() << endl;
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
				output  << "Token Comment  " << "\t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn()  << endl;
				break;
			case Token::Error:
				cerr << "Number out of integer range, line " << t->getLine()<< " column " << t->getColumn() << endl;
				break;
		}
	}
	output  << "End of File \t\tLine:\t" << t->getLine() << "\t\tColumn: " << t->getColumn()  << endl;
	delete symtab;
	delete scanner;
	output.close();
	return 0;
}

