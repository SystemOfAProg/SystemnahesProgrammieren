#ifndef PARSER_INCLUDES_TYPEGENERATOR_H_
#define PARSER_INCLUDES_TYPEGENERATOR_H_

#include "ParseTreeVisitor.h"

#include "Node.h"
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

class TypeChecker: public ParseTreeVisitor {
public:
	void typeCheck(ParseTree* tree);
	void exitExecutionAndThrowError(char *errorMessage, unsigned int line, unsigned int column);
	void visitNode(Node* node) override;
	void visitNode(NodeProg* node) override;
	void visitNode(NodeArray* node) override;
	void visitNode(NodeDecl* node) override;
	void visitNode(NodeDecls* node) override;
	void visitNode(NodeEpsilon* node) override;
	void visitNode(NodeExp* node) override;
	void visitNode(NodeExp2* node) override;
	void visitNode(NodeExp2Bracket* node) override;
	void visitNode(NodeExp2Exclamation* node) override;
	void visitNode(NodeExp2Identifier* node) override;
	void visitNode(NodeExp2Integer* node) override;
	void visitNode(NodeExp2Minus* node) override;
	void visitNode(NodeIdentifier* node) override;
	void visitNode(NodeIndex* node) override;
	void visitNode(NodeInteger* node) override;
	void visitNode(NodeOp* node) override;
	void visitNode(NodeOpExp* node) override;
	void visitNode(NodeStatement* node) override;
	void visitNode(NodeStatementAssign* node) override;
	void visitNode(NodeStatementBlock* node) override;
	void visitNode(NodeStatementIf* node) override;
	void visitNode(NodeStatementRead* node) override;
	void visitNode(NodeStatementWhile* node) override;
	void visitNode(NodeStatementWrite* node) override;
	void visitNode(NodeStatements* node) override;
};


#endif /* PARSER_INCLUDES_TYPEGENERATOR_H_ */
