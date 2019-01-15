#ifndef PARSER_INCLUDES_NODES_NODEEXP2INTEGER_H_
#define PARSER_INCLUDES_NODES_NODEEXP2INTEGER_H_

#include "NodeInteger.h"

class NodeExp2Integer: public NodeExp2 {
private:
	NodeInteger* integer;

public:
	~NodeExp2Integer() {
		delete this->integer;
	}

	void addNode(NodeInteger* integer) {
		this->integer = integer;
	}

	void accept(ParseTreeVisitor* visitor) {
		visitor->visitNode(this);
	}

	NodeInteger* getInteger() {
		return this->integer;
	}
};

#endif /* PARSER_INCLUDES_NODES_NODEEXP2INTEGER_H_ */
