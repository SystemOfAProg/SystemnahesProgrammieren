#ifndef PARSER_INCLUDES_NODES_NODEEPSILON_H_
#define PARSER_INCLUDES_NODES_NODEEPSILON_H_

class NodeEpsilon: public NodeDecls, public NodeArray, public NodeStatements, public NodeIndex, public NodeOpExp {
public:
	enum EpsilonType {
		epsDecls,
		epsArray,
		epsStatements,
		epsIndex,
		epsOpExp
	};

	NodeEpsilon(NodeEpsilon::EpsilonType epsType) {
		this->epsType = epsType;
	}

	virtual ~NodeEpsilon () {}

	void accept(ParseTreeVisitor* visitor) {
		visitor->visitNode(this);
	}

	void setEpsilonType(Node::NodeType type) {
		this->type = type;
	}

	Node::NodeType getEpsilonType() {
		return this->type;
	}

	NodeEpsilon::EpsilonType getEpsilonNodeType() {
		return this->epsType;
	}

private:
	Node::NodeType type;
	NodeEpsilon::EpsilonType epsType;
};


#endif /* PARSER_INCLUDES_NODES_NODEEPSILON_H_ */
