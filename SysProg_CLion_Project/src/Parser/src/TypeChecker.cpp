#include "../includes/TypeChecker.h"
#include "../includes/Node.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

/**
 * Startet die Typüberprüfung am Knoten "PROG" für den übergebenen Baum.
 */
void TypeChecker::typeCheck(ParseTree* tree) {
	tree->getProg()->accept(this);
}

/**
 * Gibt eine Fehlermeldung mit der Zeilen- & Spaltenangabe und dem Fehlertyp aus.
 * Zusätzlich bricht das Programm ab.
 */
void TypeChecker::exitExecutionAndThrowError(char *errorMessage, unsigned int line, unsigned int column) {
	cerr << "error Line: " << line << " Column: " << column << " " << errorMessage << endl;
	cerr << "stop" << endl;
	exit(EXIT_FAILURE);
}

/**
 * PROG ::= DECLS STATEMENTS
 */
void TypeChecker::visitNode(NodeProg* node) {
	node->getDecls()->accept(this);
	node->getStatements()->accept(this);
	node->setType(Node::noType);
}

/**
 * DECLS ::= DECL ; DECLS
 */
void TypeChecker::visitNode(NodeDecls* node) {
	node->getDecl()->accept(this);
	node->getDecls()->accept(this);
	node->setType(Node::noType);
}

/**
 * DECL 		::= e
 * ARRAY 		::= e
 * STATEMENTS 	::= e
 * INDEX 		::= e
 * OP_EXP 		::= e
 */
void TypeChecker::visitNode(NodeEpsilon* node) {
	node->setEpsilonType(Node::noType);
}

/**
 * DECL ::= int ARRAY identifier
 */
void TypeChecker::visitNode(NodeDecl* node) {
	node->getArray()->accept(this);
	if (node->getIdentifier()->getType() != Node::noType) {
		exitExecutionAndThrowError("Identifier has already been declared", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	} else if (node->getArray()->getType() == Node::errorType) {
		node->setType(Node::errorType);
	} else {
		node->setType(Node::noType);
		if (node->getArray()->getType() == Node::arrayType) {
			node->getIdentifier()->setType(Node::intArrayType);
		} else {
			node->getIdentifier()->setType(Node::intType);
		}
	}
}

/**
 * ARRAY ::= [integer]
 */
void TypeChecker::visitNode(NodeArray* node) {
	if (node->getInteger()->getValue() > 0) {
		node->setType(Node::arrayType);
	} else {
		exitExecutionAndThrowError("no valid dimension", node->getInteger()->getLine(), node->getInteger()->getColumn());
		node->setType(Node::errorType);
	}
}

/**
 * STATEMENTS ::= STATEMENT ; STATEMENTS
 */
void TypeChecker::visitNode(NodeStatements* node) {
	node->getStatement()->accept(this);
	node->getStatements()->accept(this);
	node->setType(Node::noType);
}

/**
 * STATEMENT ::= identifier INDEX := EXP
 */
void TypeChecker::visitNode(NodeStatementAssign* node) {
	node->getExp()->accept(this);
	node->getIndex()->accept(this);
	if (node->getIdentifier()->getType() == Node::noType) {
		exitExecutionAndThrowError("identifier not defined", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	} else if (node->getExp()->getType() == Node::intType && (
			(node->getIdentifier()->getType() == Node::intType && node->getIndex()->getType() == Node::noType) ||
			(node->getIdentifier()->getType() == Node::intArrayType && node->getIndex()->getType() == Node::arrayType))) {
		node->setType(Node::noType);
	} else {
		exitExecutionAndThrowError("incompatible types", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	}
}

/**
 * STATEMENT ::= write(EXP)
 */
void TypeChecker::visitNode(NodeStatementWrite* node) {
	node->getExp()->accept(this);
	node->setType(Node::noType);
}

/**
 * STATEMENT ::= read(identifier INDEX)
 */
void TypeChecker::visitNode(NodeStatementRead* node) {
	node->getIndex()->accept(this);
	if (node->getIdentifier()->getType() == Node::noType) {
		exitExecutionAndThrowError("identifier not defined", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	} else if (((node->getIdentifier()->getType() == Node::intType) && node->getIndex()->getType() == Node::noType) ||
			((node->getIdentifier()->getType() == Node::intArrayType) && node->getIndex()->getType() == Node::arrayType)) {
		node->setType(Node::noType);
	} else {
		exitExecutionAndThrowError("incompatible types", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	}
}

/**
 * STATEMENT ::= {STATEMENTS}
 */
void TypeChecker::visitNode(NodeStatementBlock* node) {
	node->getStatements()->accept(this);
	node->setType(Node::noType);
}

/**
 * STATEMENT ::= if (EXP) STATEMENT else STATEMENT
 */
void TypeChecker::visitNode(NodeStatementIf* node) {
	node->getExp()->accept(this);
	node->getStatementIf()->accept(this);
	node->getStatementElse()->accept(this);
	if (node->getExp()->getType() == Node::errorType) {
		node->setType(Node::errorType);
	} else {
		node->setType(Node::noType);
	}
}

/**
 * STATEMENT ::= while (EXP) STATEMENT
 */
void TypeChecker::visitNode(NodeStatementWhile* node) {
	node->getExp()->accept(this);
	node->getStatement()->accept(this);
	if (node->getExp()->getType() == Node::errorType) {
		node->setType(Node::errorType);
	} else {
		node->setType(Node::noType);
	}
}

/**
 * INDEX ::= [EXP]
 */
void TypeChecker::visitNode(NodeIndex* node) {
	node->getExp()->accept(this);
	if (node->getExp()->getType() == Node::errorType) {
		node->setType(Node::errorType);
	} else {
		node->setType(Node::arrayType);
	}
}

/**
 * EXP ::= EXP2 OP_EXP
 */
void TypeChecker::visitNode(NodeExp* node) {
	node->getExp2()->accept(this);
	node->getOpExp()->accept(this);
	if (node->getOpExp()->getType() == Node::noType) {
		node->setType(node->getExp2()->getType());
	} else if (node->getExp2()->getType() != node->getOpExp()->getType()) {
		node->setType(Node::errorType);
	} else {
		node->setType(node->getExp2()->getType());
	}
}

/**
 * EXP2 ::= (EXP)
 */
void TypeChecker::visitNode(NodeExp2Bracket* node) {
	node->getExp()->accept(this);
	node->setType(node->getExp()->getType());
}

/**
 * EXP2 ::= identifier INDEX
 */
void TypeChecker::visitNode(NodeExp2Identifier* node) {
	node->getIndex()->accept(this);
	if (node->getIdentifier()->getType() == Node::noType) {
		exitExecutionAndThrowError("identifier not defined", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	} else if (node->getIdentifier()->getType() == Node::intType && node->getIndex()->getType() == Node::noType) {
		node->setType(node->getIdentifier()->getType());
	} else if (node->getIdentifier()->getType() == Node::intArrayType && node->getIndex()->getType() == Node::arrayType) {
		node->setType(Node::intType);
	} else {
		exitExecutionAndThrowError("no primitive Type", node->getIdentifier()->getLine(),
								   node->getIdentifier()->getColumn());
		node->setType(Node::errorType);
	}
}

/**
 * EXP2 ::= integer
 */
void TypeChecker::visitNode(NodeExp2Integer* node) {
	node->setType(Node::intType);
}

/**
 * EXP2 ::= -EXP2
 */
void TypeChecker::visitNode(NodeExp2Minus* node) {
	node->getExp2()->accept(this);
	node->setType(node->getExp2()->getType());
}

/**
 * EXP2 ::= !EXP2
 */
void TypeChecker::visitNode(NodeExp2Exclamation* node) {
	node->getExp2()->accept(this);
	if (node->getExp2()->getType() != Node::intType) {
		node->setType(Node::errorType);
	} else {
		node->setType(Node::intType);
	}
}

/**
 * OP_EXP ::= OP EXP
 */
void TypeChecker::visitNode(NodeOpExp* node) {
	node->getOp()->accept(this);
	node->getExp()->accept(this);
	node->setType(node->getExp()->getType());
}

/**
 * OP ::= + | - | * | : | < | > | = | =:= | &&
 */
void TypeChecker::visitNode(NodeOp* node) {
	switch (node->getToken()->getType()) {
		case Token::Plus:
			node->setType(Node::opPlus);
			break;
		case Token::Minus:
			node->setType(Node::opMinus);
			break;
		case Token::Star:
			node->setType(Node::opMult);
			break;
		case Token::Colon:
			node->setType(Node::opDiv);
			break;
		case Token::LessThan:
			node->setType(Node::opLess);
			break;
		case Token::GreaterThan:
			node->setType(Node::opGreater);
			break;
		case Token::Equal:
			node->setType(Node::opEqual);
			break;
		case Token::ColonBetweenEqual:
			node->setType(Node::opUnEqual);
			break;
		case Token::And:
			node->setType(Node::opAnd);
			break;
	}
}

void TypeChecker::visitNode(NodeExp2* node) {
}

void TypeChecker::visitNode(NodeIdentifier* node) {
}

void TypeChecker::visitNode(NodeInteger* node) {
}

void TypeChecker::visitNode(NodeStatement* node) {
}

void TypeChecker::visitNode(Node* node) {
}
