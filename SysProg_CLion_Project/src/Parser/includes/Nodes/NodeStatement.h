/*
 * NodeStatement.h
 *
 *  Created on: 13.01.2017
 *      Author: yannick
 */

#ifndef PARSER_INCLUDES_NODES_NODESTATEMENT_H_
#define PARSER_INCLUDES_NODES_NODESTATEMENT_H_

class NodeStatement: public Node {
public:
	~NodeStatement() {

	}

	void accept(ParseTreeVisitor* visitor) {
		visitor->visitNode(this);
	}
};


#endif /* PARSER_INCLUDES_NODES_NODESTATEMENT_H_ */
