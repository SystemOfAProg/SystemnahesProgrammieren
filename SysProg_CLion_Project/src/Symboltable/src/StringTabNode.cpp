using namespace std;
#include <iostream>
#include "StringTabNode.h";

StringTabNode::StringTabNode() {
    this->init();
}

StringTabNode::~StringTabNode() {
    // Delete here everything in case heap memory is allocated with keyword "new"
}

void StringTabNode::init() {
    char* toWrite = this->vector;
    while(toWrite <= (this->vector + STRING_TAB_NODE_SIZE * sizeof(char))) {
        *toWrite = 0;
        toWrite++;
    }
    this->tabNodeSize = STRING_TAB_NODE_SIZE;
    return;
}

char* StringTabNode::getVector() {
    return this->vector;
}

StringTabNode* StringTabNode::getNext() {
    return this->next;
}

unsigned int StringTabNode::getSize() {
    return this->tabNodeSize;
}

void StringTabNode::setNext(StringTabNode* next) {
    this->next = next;
}

/**
 * Print all characters saved in this StringTabNode
 */
void StringTabNode::print() {
    char* toPrint = this->vector;
    cout << "===== Start of String Tab Node =====" << endl;
    while(toPrint < (this->vector + this->tabNodeSize * sizeof(char))) {
        std::cout << (void *)toPrint << ": " << *toPrint << endl;
        toPrint++;
    }
    cout << "====== End of String Tab Node ======" << endl;
    return;
}
