#include "../includes/Parser.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Parser::Parser(char* filename) {
	Symboltable* symtab = new Symboltable;
	this->scanner = new Scanner(filename, symtab);
	this->parseTree = new ParseTree();
	this->currentToken = NULL;
	this->getNextTokenFromScanner();
	return;
}

Parser::~Parser() {
	delete this->scanner;
	delete this->parseTree;
}


void Parser::getNextTokenFromScanner() {
	if (this->currentToken == NULL || currentToken->getType() != Token::Eof) {
		this->currentToken = this->scanner->nextToken();
		if (currentToken->getType() == Token::Comment) {
			this->getNextTokenFromScanner();
		}
	}
	return;
}

void Parser::mandatoryCompareTokenType(Token::TType token) {
	if (this->currentToken->getType() != token) {
		exitExecutionAndThrowError(this->tokenTypeToString(token));
	} else {
		getNextTokenFromScanner();
		return;
	}
}

const char* Parser::tokenTypeToString(Token::TType type) {
	switch (type) {
		case Token::TType::LeftBracket : {
			return "Left Bracket ( [ )";
		};
		case Token::TType::RightBracket : {
			return "Right Bracket ( ] )";
		};
		case Token::TType::LeftParent : {
			return "Left Parent ( ( )";
		};
		case Token::TType::RightParent : {
			return "Right Parent ( ) )";
		};
		case Token::TType::LeftCurved : {
			return "Left Curved ( { )";
		};
		case Token::TType::RightCurved : {
			return "Right Curved ( } )";
		};
		case Token::TType::Semicolon : {
			return "Semicolon ( ; )";
		};
		case Token::TType::Assign : {
			return "Assign ( := )";
		};
		case Token::TType::Else : {
			return "Else ( else )";
		};
		case Token::TType::Integer : {
			return "A number (0|1|2|3|4|5|6|7|8|9)*";
		};
		case Token::TType::Identifier : {
			return "Identifier (variable)";
		};
		default: {
			return "Sign";
		}
	}
}

bool Parser::safeCompareTokenType(Token::TType token) {
	if (this->currentToken->getType() == token) {
		getNextTokenFromScanner();
		return true;
	} else {
		return false;
	}
}

void Parser::exitExecutionAndThrowError(const char* expectedTokenType) {
	cerr << "Unexpected Token Line: " << currentToken->getLine() << " Column: " << currentToken->getColumn() << " " << currentToken->typeToString() << endl;
	if(expectedTokenType != NULL) {
		cerr << "Expected Token was " << expectedTokenType << endl;
	}
	cerr << "Stop parsing ParserTree." << endl;
	exit(EXIT_FAILURE);
}

/**
 *	Start structure-tree with starting-word "PROG"
 */
ParseTree* Parser::parse() {
	this->parseTree->addProg(parseNodePROG());
	return this->parseTree;
}

/**
 * PROG ::= DECLS STATEMENTS
 */
NodeProg* Parser::parseNodePROG() {
	NodeProg* prog = new NodeProg();
	prog->addNode(parseNodeDECLS());
	prog->addNode(parseNodeSTATEMENTS());
	return prog;
}

/**
 * DECLS ::= DECL;DECLS | ε
 */
NodeDecls* Parser::parseNodeDECLS() {
	if (safeCompareTokenType(Token::Int)) {
		NodeDecls* declarations = new NodeDecls();
		declarations->addNode(parseNodeDECL());
		mandatoryCompareTokenType(Token::Semicolon);
		declarations->addNode(parseNodeDECLS());
		return declarations;
	} else {
		return new NodeEpsilon(NodeEpsilon::epsDecls);
	}

}

/**
 * DECL ::= int ARRAY identifier
 */
NodeDecl* Parser::parseNodeDECL() {
	NodeDecl* decl = new NodeDecl();
	decl->addNode(parseNodeARRAY());
	if (currentToken->getType() == Token::Identifier) {
		NodeIdentifier* identifier = new NodeIdentifier(currentToken);
		identifier->addInformation(currentToken->getSymtabEntry()->getInfo());
		decl->addNode(identifier);
		getNextTokenFromScanner();
	} else {
		exitExecutionAndThrowError(this->tokenTypeToString(Token::Identifier));
	}
	return decl;
}

/**
 * ARRAY ::= [integer] | ε
 */
NodeArray* Parser::parseNodeARRAY() {
	if (safeCompareTokenType(Token::LeftBracket)) {
		NodeArray* array = new NodeArray();
		if (currentToken->getType() == Token::Integer) {
			array->addInteger(new NodeInteger(currentToken->getValue(), currentToken));
			getNextTokenFromScanner();
		} else {
			exitExecutionAndThrowError(this->tokenTypeToString(Token::Integer));
		}
		mandatoryCompareTokenType(Token::RightBracket);
		return array;
	} else {
		return new NodeEpsilon(NodeEpsilon::epsArray);
	}
}

/**
 * STATEMENTS ::= STATEMENT;STATEMENTS | ε
 */
NodeStatements* Parser::parseNodeSTATEMENTS() {
	switch (currentToken->getType()) {
		case Token::Identifier:
		case Token::Write:
		case Token::Read:
		case Token::LeftCurved:
		case Token::If:
		case Token::While: {
			NodeStatements* statements_ = new NodeStatements();
			statements_->addNode(parseNodeSTATEMENT());
			mandatoryCompareTokenType(Token::Semicolon);
			statements_->addNode(parseNodeSTATEMENTS());
			return statements_;
		}
		case Token::Int:
			exitExecutionAndThrowError(NULL);
			break;
		default:
			return new NodeEpsilon(NodeEpsilon::epsStatements);
	}
	return new NodeEpsilon(NodeEpsilon::epsStatements);
}

/**
 *	STATEMENT ::= identifier INDEX := EXP | write(EXP) | read(identifier INDEX) |
 *				  {STATEMENTS} | if (EXP) STATEMENT else STATEMENT | while (EXP) STATEMENT
 *
 */
NodeStatement* Parser::parseNodeSTATEMENT() {
	switch (currentToken->getType()) {
		case Token::Identifier: {
			NodeStatementAssign* statement = new NodeStatementAssign();
			NodeIdentifier* identifier = new NodeIdentifier(currentToken);
			identifier->addInformation(currentToken->getSymtabEntry()->getInfo());
			statement->addNode(identifier);
			getNextTokenFromScanner();
			statement->addNode(parseNodeINDEX());
			mandatoryCompareTokenType(Token::Assign);
			statement->addNode(parseNodeEXP());
			return statement;
		}
		case Token::Write: {
			NodeStatementWrite* statement = new NodeStatementWrite();
			getNextTokenFromScanner();
			mandatoryCompareTokenType(Token::LeftParent);
			statement->addNode(parseNodeEXP());
			mandatoryCompareTokenType(Token::RightParent);
			return statement;
		}
		case Token::Read: {
			NodeStatementRead* statement = new NodeStatementRead();
			getNextTokenFromScanner();
			mandatoryCompareTokenType(Token::LeftParent);
			if (currentToken->getType() == Token::Identifier) {
				NodeIdentifier* identifier = new NodeIdentifier(currentToken);
				identifier->addInformation(currentToken->getSymtabEntry()->getInfo());
				statement->addNode(identifier);
				getNextTokenFromScanner();
			} else {
				exitExecutionAndThrowError(this->tokenTypeToString(Token::Identifier));
			}
			statement->addNode(parseNodeINDEX());
			mandatoryCompareTokenType(Token::RightParent);
			return statement;
		}
		case Token::LeftCurved: {
			NodeStatementBlock* statement = new NodeStatementBlock();
			getNextTokenFromScanner();
			statement->addNode(parseNodeSTATEMENTS());
			mandatoryCompareTokenType(Token::RightCurved);
			return statement;
		}
		case Token::If: {
			NodeStatementIf* statement_ = new NodeStatementIf();
			getNextTokenFromScanner();
			mandatoryCompareTokenType(Token::LeftParent);
			statement_->addNode(parseNodeEXP());
			mandatoryCompareTokenType(Token::RightParent);
			statement_->addNodeIf(parseNodeSTATEMENT());
			mandatoryCompareTokenType(Token::Else);
			statement_->addNodeElse(parseNodeSTATEMENT());
			return statement_;
		}
		case Token::While: {
			NodeStatementWhile* statement_ = new NodeStatementWhile();
			getNextTokenFromScanner();
			mandatoryCompareTokenType(Token::LeftParent);
			statement_->addNode(parseNodeEXP());
			mandatoryCompareTokenType(Token::RightParent);
			statement_->addNode(parseNodeSTATEMENT());
			return statement_;
		}
		default:
			exitExecutionAndThrowError(NULL);
			return new NodeStatement();
	}
}

/**
 * INDEX ::= [EXP]
 */
NodeIndex* Parser::parseNodeINDEX() {
	if (safeCompareTokenType(Token::LeftBracket)) {
		NodeIndex* index = new NodeIndex();
		index->addNode(parseNodeEXP());
		mandatoryCompareTokenType(Token::RightBracket);
		return index;
	} else {
		return new NodeEpsilon(NodeEpsilon::epsIndex);
	}

}

/**
 * EXP ::= EXP2 OP_EXP
 */
NodeExp* Parser::parseNodeEXP() {
	NodeExp* exp = new NodeExp();
	exp->addNode(parseNodeEXP2());
	exp->addNode(parseNodeOP_EXP());
	return exp;
}

/**
 * EXP2 ::= (EXP) | identifier INDEX | integer | -EXP2 | !EXP2
 */
NodeExp2* Parser::parseNodeEXP2() {
	switch (currentToken->getType()) {
		case Token::LeftParent: {
			getNextTokenFromScanner();
			NodeExp2Bracket* exp2 = new NodeExp2Bracket();
			exp2->addNode(parseNodeEXP());
			mandatoryCompareTokenType(Token::RightParent);
			return exp2;
		}
		case Token::Identifier: {
			NodeExp2Identifier* exp2 = new NodeExp2Identifier();
			NodeIdentifier* identifier = new NodeIdentifier(currentToken);
			identifier->addInformation(currentToken->getSymtabEntry()->getInfo());
			exp2->addNode(identifier);
			getNextTokenFromScanner();
			exp2->addNode(parseNodeINDEX());
			return exp2;
		}
		case Token::Integer: {
			NodeInteger* integer = new NodeInteger(currentToken->getValue(), currentToken);
			NodeExp2Integer* exp2 = new NodeExp2Integer();
			exp2->addNode(integer);
			getNextTokenFromScanner();
			return exp2;
		}
		case Token::Minus: {
			NodeExp2Minus* exp2_ = new NodeExp2Minus();
			getNextTokenFromScanner();
			exp2_->addNode(parseNodeEXP2());
			return exp2_;
		}
		case Token::Exclamation: {
			NodeExp2Exclamation* exp2_ = new NodeExp2Exclamation();
			getNextTokenFromScanner();
			exp2_->addNode(parseNodeEXP2());
			return exp2_;
		}
		default:
			exitExecutionAndThrowError(NULL);
			return new NodeExp2();
	}
}

/**
 * OP_EXP ::= OP EXP
 */
NodeOpExp* Parser::parseNodeOP_EXP() {
	switch (currentToken->getType()) {
		case Token::Plus:
		case Token::Minus:
		case Token::Star:
		case Token::Colon:
		case Token::LessThan:
		case Token::GreaterThan:
		case Token::Equal:
		case Token::ColonBetweenEqual:
		case Token::And: {
			NodeOpExp* opExp = new NodeOpExp();
			opExp->addNode(parseNodeOP());
			opExp->addNode(parseNodeEXP());
			return opExp;
		}
		default:
			return new NodeEpsilon(NodeEpsilon::epsOpExp);
	}
}

/**
 * OP ::= + | - | * | : | < | > | = | =:= | &&
 */
NodeOp* Parser::parseNodeOP() {
	NodeOp* op = new NodeOp(currentToken);
	getNextTokenFromScanner();
	return op;
}
