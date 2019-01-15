#include "../includes/ParseTree.h"


ParseTree::ParseTree() {

}

ParseTree::~ParseTree() {

}

void ParseTree::addProg(NodeProg* prog) {
	this->rootNode = prog;
}

NodeProg* ParseTree::getProg() {
	return this->rootNode;
}

