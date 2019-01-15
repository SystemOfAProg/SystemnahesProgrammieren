#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"
#include "Automat.h"
#include "Buffer.h"
#include "Symboltable.h"

class Scanner {
public:
	Scanner(char* filename, Symboltable* symtab);
	virtual ~Scanner();
	Token* nextToken();
	int main(int argc, char **argv);
private:

	int stringCompare( const char *string1, const char *string2);
	Token* handleStateIdentifier(int line, int column);
	Token* handleStateInteger(int line, int column);
	Token* handleStateSign(int line, int column);
	Automat* automat;
	Buffer* buffer;
	Symboltable* symboltable;
	Token* createToken(int line, int column);
};


#endif /* SCANNER_H_ */
