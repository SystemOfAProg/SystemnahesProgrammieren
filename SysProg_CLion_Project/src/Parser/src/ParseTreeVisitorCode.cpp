/*
 * ParseTreeVisitorCode.cpp
 *
 *  Created on: 15.01.2017
 *      Author: yannick
 */

#include "../includes/ParseTreeVisitorCode.h"
#include "../includes/Node.h"
#include <iostream>

using namespace std;

/**
 * Zählt die Labelnummer nach oben um eindeutige Sprungmarken zu erhalten.
 */
unsigned long ParseTreeVisitorCode::getLabelNumber() {
	return this->labelNumber++;
}

/**
 * Öffnet die Outputdatei um dort die Ausgabe zu speichern.
 * Startet die Codeerzeugung am ersten Knoten "PROG".
 */
void ParseTreeVisitorCode::makeCode(ParseTree* tree, char* filename) {
	this->labelNumber = 1;
	code.open(filename);
	tree->getProg()->accept(this);
	code.close();
}

/**
 * PROG ::= DECLS STATEMENTS
 */
void ParseTreeVisitorCode::visitNode(NodeProg* node) {
	node->getDecls()->accept(this);
	node->getStatements()->accept(this);
	code << "STP";
}

/**
 * DECLS ::= DECL ; DECLS
 */
void ParseTreeVisitorCode::visitNode(NodeDecls* node) {
	node->getDecl()->accept(this);
	node->getDecls()->accept(this);
}

/**
 * DECL 		::= e
 * ARRAY 		::= e
 * STATEMENTS 	::= e
 * INDEX 		::= e
 * OP_EXP 		::= e
 */
void ParseTreeVisitorCode::visitNode(NodeEpsilon* node) {
	switch (node->getEpsilonNodeType()) {
		case NodeEpsilon::epsDecls:
		case NodeEpsilon::epsIndex:
		case NodeEpsilon::epsOpExp:
			break;
		case NodeEpsilon::epsStatements:
			code << "NOP" << endl;
			break;
		case NodeEpsilon::epsArray:
			code << "1" << endl;
			break;
	}
}

/**
 * DECL ::= int ARRAY identifier
 */
void ParseTreeVisitorCode::visitNode(NodeDecl* node) {
	code << "DS " <<  "$" << node->getIdentifier()->getInformation()->getName() << " ";
	node->getArray()->accept(this);
}

/**
 * ARRAY ::= [integer]
 */
void ParseTreeVisitorCode::visitNode(NodeArray* node) {
	code << node->getInteger()->getValue() << endl;
}

/**
 * STATEMENTS ::= STATEMENT ; STATEMENTS
 */
void ParseTreeVisitorCode::visitNode(NodeStatements* node) {
	node->getStatement()->accept(this);
	node->getStatements()->accept(this);
}

/**
 * STATEMENT ::= identifier INDEX := EXP
 */
void ParseTreeVisitorCode::visitNode(NodeStatementAssign* node) {
	node->getExp()->accept(this);
	code << "LA " << "$" << node->getIdentifier()->getInformation()->getName() << endl;
	node->getIndex()->accept(this);
	code << "STR" << endl;
}

/**
 * STATEMENT ::= write(EXP)
 */
void ParseTreeVisitorCode::visitNode(NodeStatementWrite* node) {
	node->getExp()->accept(this);
	code << "PRI" << endl;
}

/**
 * STATEMENT ::= read(identifier INDEX)
 */
void ParseTreeVisitorCode::visitNode(NodeStatementRead* node) {
	code << "REA" << endl;
	code << "LA " << "$" << node->getIdentifier()->getInformation()->getName() << endl;
	node->getIndex()->accept(this);
	code << "STR" << endl;
}

/**
 * STATEMENT ::= {STATEMENTS}
 */
void ParseTreeVisitorCode::visitNode(NodeStatementBlock* node) {
	node->getStatements()->accept(this);
}

/**
 * STATEMENT ::= if (EXP) STATEMENT else STATEMENT
 */
void ParseTreeVisitorCode::visitNode(NodeStatementIf* node) {
	unsigned long label1 = getLabelNumber();
	unsigned long label2 = getLabelNumber();
	node->getExp()->accept(this);
	code << "JIN " << "#label" << label1 << endl;
	node->getStatementIf()->accept(this);
	code << "JMP " << "#label" << label2 << endl;
	code << "#label" << label1 << " NOP" << endl;
	node->getStatementElse()->accept(this);
	code << "#label" << label2 << " NOP" << endl;
}

/**
 * STATEMENT ::= while (EXP) STATEMENT
 */
void ParseTreeVisitorCode::visitNode(NodeStatementWhile* node) {
	unsigned long label1 = getLabelNumber();
	unsigned long label2 = getLabelNumber();
	code << "#label" << label1 << " NOP" << endl;
	node->getExp()->accept(this);
	code << "JIN " << "#label" << label2 << endl;
	node->getStatement()->accept(this);
	code << "JMP " << "#label" << label1 << endl;
	code << "#label" << label2 << " NOP" << endl;
}

/**
 * INDEX ::= [EXP]
 */
void ParseTreeVisitorCode::visitNode(NodeIndex* node) {
	node->getExp()->accept(this);
	code << "ADD" << endl;
}

/**
 * EXP ::= EXP2 OP_EXP
 */
void ParseTreeVisitorCode::visitNode(NodeExp* node) {
	if (node->getOpExp()->getType() == Node::noType) {
		node->getExp2()->accept(this);
	} else if (node->getOpExp()->getType() == Node::opGreater) {
		node->getOpExp()->accept(this);
		node->getExp2()->accept(this);
		code << "LES" << endl;
	} else if (node->getOpExp()->getType() == Node::opUnEqual) {
		node->getExp2()->accept(this);
		node->getOpExp()->accept(this);
		code << "NOT" << endl;
	} else {
		node->getExp2()->accept(this);
		node->getOpExp()->accept(this);
	}
}

/**
 * EXP2 ::= (EXP)
 */
void ParseTreeVisitorCode::visitNode(NodeExp2Bracket* node) {
	node->getExp()->accept(this);
}

/**
 * EXP2 ::= identifier INDEX
 */
void ParseTreeVisitorCode::visitNode(NodeExp2Identifier* node) {
	code << "LA " << "$" << node->getIdentifier()->getInformation()->getName() << endl;
	node->getIndex()->accept(this);
	code << "LV" << endl;
}

/**
 * EXP2 ::= integer
 */
void ParseTreeVisitorCode::visitNode(NodeExp2Integer* node) {
	code << "LC " << node->getInteger()->getValue() << endl;
}

/**
 * EXP2 ::= -EXP2
 */
void ParseTreeVisitorCode::visitNode(NodeExp2Minus* node) {
	code << "LC " << 0 << endl;
	node->getExp2()->accept(this);
	code << "SUB" << endl;
}

/**
 * EXP2 ::= !EXP2
 */
void ParseTreeVisitorCode::visitNode(NodeExp2Exclamation* node) {
	node->getExp2()->accept(this);
	code << "NOT" << endl;
}

/**
 * OP_EXP ::= OP EXP
 */
void ParseTreeVisitorCode::visitNode(NodeOpExp* node) {
	node->getExp()->accept(this);
	node->getOp()->accept(this);
}

/**
 * OP ::= + | - | * | : | < | > | = | =:= | &&
 */
void ParseTreeVisitorCode::visitNode(NodeOp* node) {
	switch (node->getToken()->getType()) {
		case Token::Plus:
			code << "ADD" << endl;
			break;
		case Token::Minus:
			code << "SUB" << endl;
			break;
		case Token::Star:
			code << "MUL" << endl;
			break;
		case Token::Colon:
			code << "DIV" << endl;
			break;
		case Token::LessThan:
			code << "LES" << endl;
			break;
		case Token::GreaterThan:
			break;
		case Token::Equal:
			code << "EQU" << endl;
			break;
		case Token::ColonBetweenEqual:
			code << "EQU" << endl;
			break;
		case Token::And:
			code << "AND" << endl;
			break;
	}
}

void ParseTreeVisitorCode::visitNode(NodeExp2* node) {
}

void ParseTreeVisitorCode::visitNode(NodeIdentifier* node) {
}

void ParseTreeVisitorCode::visitNode(NodeInteger* node) {
}

void ParseTreeVisitorCode::visitNode(NodeStatement* node) {
}

void ParseTreeVisitorCode::visitNode(Node* node) {
}
