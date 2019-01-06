/*
 * NodeExp2Identifier.h
 *
 *  Created on: 08.01.2017
 *      Author: yannick
 */

#ifndef PARSER_INCLUDES_NODES_NODEEXP2IDENTIFIER_H_
#define PARSER_INCLUDES_NODES_NODEEXP2IDENTIFIER_H_

class NodeExp2Identifier: public NodeExp2 {
private:
	NodeIdentifier* identifier;
	NodeIndex* index;

public:
	~NodeExp2Identifier() {
		delete this->identifier;
		delete this->index;
	}

	void addNode(NodeIdentifier* identifier) {
		this->identifier = identifier;
	}

	void addNode(NodeIndex* index) {
		this->index = index;
	}

	void accept(ParseTreeVisitor* visitor) {
		visitor->visitNode(this);
	}

	NodeIdentifier* getIdentifier() {
		return this->identifier;
	}

	NodeIndex* getIndex() {
		return this->index;
	}
};

#endif /* PARSER_INCLUDES_NODES_NODEEXP2IDENTIFIER_H_ */
