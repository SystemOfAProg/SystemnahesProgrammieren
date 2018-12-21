using namespace std;
#include <iostream>
#include <iomanip>
#include "../includes/StringTable.h";

StringTable::StringTable() {
    this->firstNode = new StringTabNode();
    this->currentNode = this->firstNode;
    this->freePosition = (char*) this->firstNode->getVector();
    this->freeSpace = this->firstNode->getSize();
    // TODO: implement
}

StringTable::~StringTable() {
    // Delete here everything in case heap memory is allocated with keyword "new"
}

/**
 * Insert new Lexem into the StringTable and return its address in the string table
 */ 
char* StringTable::insert(char* lexem) {
    unsigned int lexemCharacterCount = this->countCharacters(lexem);
    char* temporary = this->freePosition;
    if (!this->addStringTabNodeIfNecessary(lexemCharacterCount, lexem)) {
        memcpy(this->freePosition, lexem, lexemCharacterCount+1);
        this->freePosition[lexemCharacterCount] = '\0';
        this->freePosition += lexemCharacterCount+1;
        this->freeSpace -= lexemCharacterCount+1;
        // std::cout << "> Insert new Lexem" << "\- Lexem: " << lexem << "\n - Length: " << lexemCharacterCount << "\n - Space left after adding: " << this->freeSpace << "\n - Added at: " << this->freePosition;
        return temporary;
    } else {
        return NULL;
    }
}


/**
 * Check, if in current StringTabNode exists enough space for the new lexem,
 * if not, create a new StringTabNode and connect the old and new one
 */
bool StringTable::addStringTabNodeIfNecessary(unsigned int lexemLength, char* lexem) {
    bool lexemNotAddable = false;
    if (this->currentNode->getSize() <= lexemLength) {
        std::cout << "[WARNING]: The length of the lexem, you tried to add, exceeds the maximum length of String-Table Entries of " << this->currentNode->getSize()-1 << std::endl;
        lexemNotAddable = true;
    } else if (this->freeSpace <= lexemLength) {
        StringTabNode* newNode = new StringTabNode();
        this->currentNode->setNext(newNode);
        this->currentNode = newNode;
        this->freePosition = newNode->getVector();
        this->freeSpace = newNode->getSize();
    }
    return lexemNotAddable;
}

unsigned int StringTable::countCharacters(char* lexem) {
    unsigned int size = 0;
    while(*lexem++) {
        size++;
    }
    return size;
}

void StringTable::print() {
    StringTabNode* node = this->firstNode;
    while(node != NULL) {
        node->print();
        node = node->getNext();
    }
    return;
}