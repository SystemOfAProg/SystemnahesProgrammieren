#ifndef PARSER_INCLUDES_NODES_NODEEXP2_H_
#define PARSER_INCLUDES_NODES_NODEEXP2_H_


class NodeExp2: public Node {
public:
	~NodeExp2() {

	}

	void accept(ParseTreeVisitor* visitor) {
		visitor->visitNode(this);
	}
};


#endif /* PARSER_INCLUDES_NODES_NODEEXP2_H_ */
