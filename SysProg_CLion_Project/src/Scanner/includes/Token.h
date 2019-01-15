#ifndef SCANNER_INCLUDES_TOKEN_H_
#define SCANNER_INCLUDES_TOKEN_H_
#include "../../Symboltable/includes/SymTabEntry.h"

class Token {
public:

	enum TType {
		While,
		Else,
		Int,
		Read,
		Write,
		If,
		Identifier,
		Assign,
		Integer,
		Plus,
		Minus,
		Colon,
		Star,
		LessThan,
		GreaterThan,
		Equal,
		ColonBetweenEqual,
		Exclamation,
		And,
		Semicolon,
		LeftParent,
		RightParent,
		LeftCurved,
		RightCurved,
		LeftBracket,
		RightBracket,
		Unknown,
		Comment,
		Error,
		Eof
	};
	Token(Token::TType type, int line, int column, SymtabEntry* symtabentry, unsigned long value, char symbol);
	virtual ~Token();
	int getLine();
	int getColumn();
	unsigned long getValue();
	SymtabEntry* getSymtabEntry();
	char getSymbol();
	Token::TType getType();
	const char* typeToString();
private:
	Token::TType type;
	int line;
	int column;
	unsigned long value;
	SymtabEntry* symtabentry;
	char symbol;
};



#endif /* SCANNER_INCLUDES_TOKEN_H_ */
