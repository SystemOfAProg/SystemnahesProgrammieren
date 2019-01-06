/*
 * ParseTree.h
 *
 *  Created on: 20.12.2016
 *      Author: Denis
 */

#ifndef PARSER_INCLUDES_PARSETREE_H_
#define PARSER_INCLUDES_PARSETREE_H_

#include "Nodes/NodeProg.h"

class ParseTree {
public:
	ParseTree();
	virtual ~ParseTree();
	void addProg(NodeProg* node);
	NodeProg* getProg();

private:
	NodeProg* prog;
};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
