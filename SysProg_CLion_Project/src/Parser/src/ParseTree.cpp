/*
 * ParseTree.cpp
 *
 *  Created on: 20.12.2016
 *      Author: Denis
 */

#include "../includes/ParseTree.h"


ParseTree::ParseTree() {

}

ParseTree::~ParseTree() {

}

void ParseTree::addProg(NodeProg* prog) {
	this->prog = prog;
}

NodeProg* ParseTree::getProg() {
	return this->prog;
}

