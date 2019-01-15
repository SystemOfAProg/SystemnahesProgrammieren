#ifndef PARSER_H_
#define PARSER_H_

#include "../../Scanner/includes/Token.h"
#include "../../Scanner/includes/Scanner.h"
#include "Nodes/NodeProg.h"
#include "Nodes/NodeDecls.h"
#include "Nodes/NodeDecl.h"
#include "Nodes/NodeArray.h"
#include "Nodes/NodeStatements.h"
#include "Nodes/NodeIdentifier.h"
#include "Nodes/NodeStatement.h"
#include "Nodes/NodeStatementAssign.h"
#include "Nodes/NodeStatementBlock.h"
#include "Nodes/NodeStatementIf.h"
#include "Nodes/NodeStatementRead.h"
#include "Nodes/NodeStatementWhile.h"
#include "Nodes/NodeStatementWrite.h"
#include "Nodes/NodeIndex.h"
#include "Nodes/NodeExp.h"
#include "Nodes/NodeOpExp.h"
#include "Nodes/NodeExp2.h"
#include "Nodes/NodeExp2Bracket.h"
#include "Nodes/NodeExp2Exclamation.h"
#include "Nodes/NodeExp2Identifier.h"
#include "Nodes/NodeExp2Integer.h"
#include "Nodes/NodeExp2Minus.h"
#include "Nodes/NodeInteger.h"
#include "Nodes/NodeOp.h"
#include "Nodes/NodeEpsilon.h"
#include "ParseTree.h"

class Parser {
public:
	Parser(char* filename);
	virtual ~Parser();
	ParseTree* parse();

private:
	Token* currentToken;
	Scanner* scanner;
	ParseTree* parseTree;
	void getNextTokenFromScanner();
	void mandatoryCompareTokenType(Token::TType token);
	bool safeCompareTokenType(Token::TType token);
	void exitExecutionAndThrowError(const char* expectedTokenType);
	const char* tokenTypeToString(Token::TType type);
	NodeProg* parseNodePROG();
	NodeDecls* parseNodeDECLS();
	NodeDecl* parseNodeDECL();
	NodeArray* parseNodeARRAY();
	NodeStatements* parseNodeSTATEMENTS();
	NodeStatement* parseNodeSTATEMENT();
	NodeIndex* parseNodeINDEX();
	NodeExp* parseNodeEXP();
	NodeExp2* parseNodeEXP2();
	NodeOpExp* parseNodeOP_EXP();
	NodeOp* parseNodeOP();
};


#endif /* PARSER_H_ */
