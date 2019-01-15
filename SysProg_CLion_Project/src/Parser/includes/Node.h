#ifndef PARSER_INCLUDES_NODES_NODE_H_
#define PARSER_INCLUDES_NODES_NODE_H_

#include "ParseTreeVisitor.h"

/**
 * Die Klasse "Node" dient als Basisklasse aller Knoten.
 * In dieser Klasse wird die Typinformation eines Knoten gespeichert.
 * Zudem müssen abgeleitete Klassen die Methode "accept()" implementieren,
 * um dem Besucher bescheid zu geben, welche Operation er als nächstes ausführen muss.
 */
class Node {
public:

	/**
	 * Die möglichen Typinformationen die ein Knoten haben kann.
	 */
	enum NodeType {
		intType,
		intArrayType,
		arrayType,
		noType,
		errorType,
		opPlus,
		opMinus,
		opMult,
		opDiv,
		opLess,
		opGreater,
		opEqual,
		opUnEqual,
		opAnd
	};

	Node();
	virtual ~Node();
	virtual void setType(Node::NodeType type);
	virtual Node::NodeType getType();
	virtual void accept(ParseTreeVisitor* visitor) = 0;

private:
	Node::NodeType type;
};

#endif /* PARSER_INCLUDES_NODES_NODE_H_ */
