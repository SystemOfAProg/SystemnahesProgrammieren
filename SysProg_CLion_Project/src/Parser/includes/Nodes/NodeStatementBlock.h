/*
 * NodeStatementBlock.h
 *
 *  Created on: 08.01.2017
 *      Author: yannick
 */

#ifndef PARSER_INCLUDES_NODES_NODESTATEMENTBLOCK_H_
#define PARSER_INCLUDES_NODES_NODESTATEMENTBLOCK_H_

class NodeStatementBlock: public NodeStatement {
private:
	NodeStatements* statements;

public:
	~NodeStatementBlock() {
		delete this->statements;
	}

	void addNode(NodeStatements* statements) {
		this->statements = statements;
	}

	void accept(ParseTreeVisitor* visitor) {
		visitor->visitNode(this);
	}

	NodeStatements* getStatements() {
		return this->statements;
	}
};


#endif /* PARSER_INCLUDES_NODES_NODESTATEMENTBLOCK_H_ */
